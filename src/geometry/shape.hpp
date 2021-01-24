/** ---------------------------------------------------------------------------
 ** shape.hpp
 ** Abstract definition for 3D shapes. Defines common methods for setting values
 ** such as material or refractive index and leaves some to be defined by its
 ** children.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SHAPE_HPP
#define RAY_TRACER_SHAPE_HPP

#include <cmath>
#include <coloredLightRay.hpp>
#include <lightRay.hpp>
#include <material.hpp>
#include <vectorModifier.hpp>
#include <mathUtils.hpp>
#include <memory>
#include <poseTransformationMatrix.hpp>
#include <visibleNormal.hpp>

using namespace std;

class Shape
{

public:

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @return The distance closest from the lightRay's origin to any of this shape points. If the direction in the
     * lightRay is such that no intersection happens then returns FLT_MAX.
     */
    virtual float Intersect(const LightRay &lightRay) const = 0;

    /**
     * @param lightRay Contains the point from which an intersection with this shape will measured.
     * @param minT Minimum distance from the lightRay's origin to any shape so far. If this shape is closer to the origin
     *  than this value then it will be updated to that distance.
     * @param nearestShape Shape that is reportedly the closest to the lightRay's origin so far. Updated to thisShape
     *  if this shape is at a distance from the lightRay's origin smaller than minT and this shape doesn't contain any
     *  sub-shapes.
     * @param thisShape shared_ptr to this shape.
     */
    virtual void Intersect(const LightRay &lightRay, float &minT, shared_ptr<Shape> &nearestShape,
                           shared_ptr<Shape> thisShape) const = 0;

    /**
     * @param in Vector whose reflection is returned.
     * @param normal Vector used as the symmetric axis from which the reflection is calculated.
     * @return New vector reflected.
     */
    static Vect Reflect(const Vect &in, const Vect &normal)
    {
        return in- normal * in.DotProduct(normal) * 2;
    }

    /**
     * Based on http://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf.
     *
     * @param in LightRay entering this shape.
     * @param point Point at which in enters this shape.
     * @param visibleNormal Normal for this shape at point.
     * @return New lightRay refracted from in with origin point.
     */
    LightRay Refract(const LightRay &in, const Point &point, const Vect &visibleNormal) const
    {
        float n;
        // The ray of light is arriving the shape medium.
        if (visibleNormal == GetNormal(point))
            n = mN;
        // The ray of light is exiting the shape medium.
        else
            n = 1 / mN;
        // Calculate the refracted ray of light.
        float cosI = -visibleNormal.DotProduct(in.GetDirection());
        float sinT2 = n * n * (1 - cosI * cosI);
        // Critic angle: this is the angle at which the refracted lightRay goes back inside the shape.
        if (sinT2 > 1)
            return LightRay(point, Reflect(in.GetDirection(), visibleNormal));

        float cosT = sqrt(1 - sinT2);
        Vect refracted = in.GetDirection() * n + visibleNormal * (n * cosI - cosT);
        return LightRay(point, refracted);
    }

    /**
     * @param in LightRay that is directed at the shape.
     * @param point Point in which the LightRay intersects the shape.
     * @param out When the return value of this method is true this value is updated to the LightRay coming out
     *  of the shape at the given point.
     * @param isCaustic This is an output parameter. It's updated to a true value if the photon is reflected or
     *  refracted (it may origin a caustic), and false otherwise.
     * @return True if a new LightRay comes out of the intersection with this shape.
     */
    bool RussianRoulette(const ColoredLightRay &in, const Point &point, ColoredLightRay &out, bool &isCaustic) const
    {
        float random = GetRandomValue();
        // Diffuse.
        if (random < mMaterial->GetDiffuse(point).MeanRGB())
        {
            /* Transformation matrix from the local coordinates with [point] as the
             * reference point, and the normal of this shape as the z axis, to global coordinates. */
            PoseTransformationMatrix fromLocalToGlobal =
                    PoseTransformationMatrix::GetPoseTransformation(point, GetVisibleNormal(point, in));
            // Generate random angles.
            float inclination, azimuth;
            tie(inclination, azimuth) = UniformCosineSampling();
            // Direction of the ray of light expressed in local coordinates.
            Vect localRay(sin(inclination) * cos(azimuth),
                          sin(inclination) * sin(azimuth),
                          cos(inclination));
            // Transform the ray of light to global coordinates.
            out = ColoredLightRay(point, fromLocalToGlobal * localRay,
                                  in.GetColor() * mMaterial->GetDiffuse(point)
                                                / mMaterial->GetDiffuse(point).MeanRGB());
                                                // Uniform cosine PDF removed because:
                                                // (kd * PI) / ((2 * sin * cos) * (1 / 2 * PI)) =
                                                // kd (already counted) / (sin * cos).
                                                // and sin * cos are already removed from render equation.
            isCaustic = false;
            return true;
        }
        // Specular.
        else if (random < (mMaterial->GetDiffuse(point).MeanRGB() +
                           mMaterial->GetSpecular().MeanRGB()))
        {
            /* Transformation matrix from the local coordinates with [point] as the
             * reference point, and the normal of this shape as the z axis, to global coordinates. */
            PoseTransformationMatrix fromLocalToGlobal =
                    PoseTransformationMatrix::GetPoseTransformation(point, GetVisibleNormal(point, in));
            // Generate random angles.
            float inclination, azimuth;
            tie(inclination, azimuth) = PhongSpecularLobeSampling(mMaterial->GetShininess());
            // Direction of the ray of light expressed in local coordinates.
            Vect localRay(sin(inclination) * cos(azimuth),
                          sin(inclination) * sin(azimuth),
                          cos(inclination));
            out = ColoredLightRay(point, fromLocalToGlobal * localRay,
                                  in.GetColor() * mMaterial->GetSpecular()
                                                / mMaterial->GetSpecular().MeanRGB()
                                                // Phong lobe PDF. Cos^alpha is removed!
                                                * (mMaterial->GetShininess() + 2) / (mMaterial->GetShininess() + 1));
            isCaustic = true;
            return true;
        }
        // Reflective.
        else if (random < (mMaterial->GetDiffuse(point).MeanRGB() +
                           mMaterial->GetSpecular().MeanRGB() +
                           mMaterial->GetReflectance().MeanRGB()))
        {
            Vect reflectedRay = Reflect(in.GetDirection(), GetVisibleNormal(point, in));
            out = ColoredLightRay(point, reflectedRay,
                                  in.GetColor() * mMaterial->GetReflectance()
                                                / mMaterial->GetReflectance().MeanRGB());
            isCaustic = true;
            return true;
        }
        // Refractive.
        else if (random < (mMaterial->GetDiffuse(point).MeanRGB() +
                           mMaterial->GetSpecular().MeanRGB() +
                           mMaterial->GetReflectance().MeanRGB() +
                           mMaterial->GetTransmittance().MeanRGB()))
        {
            LightRay refractedRay = Refract(in, point, GetVisibleNormal(point, in));
            out = ColoredLightRay(point, refractedRay.GetDirection(),
                                  in.GetColor() * mMaterial->GetTransmittance()
                                                / mMaterial->GetTransmittance().MeanRGB());
            isCaustic = true;
            return true;
        }
        // Absorb.
        else return false;
    }

    /**
     * @param point Point to determine if it's inside this shape.
     * @return true if the point is inside this shape, false otherwise.
     */
    virtual bool IsInside(const Point &point) const = 0;

    /**
     * @param point Point of this shape which normal vector will be returned.
     * @return Vector normal to this shape at point.
     */
    virtual Vect GetNormal(const Point &point) const = 0;

    /**
     * @param point Point of this shape which normal vector will be returned.
     * @param seenFrom LightRay from which this shape is seen.
     * @return Vector normal to this shape at point in a direction opposite from seenFrom. For instance, if this shape
     *  is a rectangle we could be seeing it from the two sides of it and their normals are opposite.
     */
    Vect GetVisibleNormal(const Point &point, const LightRay &seenFrom) const
    {
        if (mNormalModifier != nullptr)
            return mNormalModifier->Modify(VisibleNormal(GetNormal(point), seenFrom.GetDirection()), point);
        else
            return VisibleNormal(GetNormal(point), seenFrom.GetDirection());
    }

    /**
     * @return Pointer to the material in this shape.
     */
    shared_ptr<Material> GetMaterial() const
    {
        return mMaterial;
    }

    /**
     * Sets the material in this shape. If this shape contains any sub-shapes they should also have their materials set
     * to material by overriding this method.
     *
     * @param material Material for this shape.
     */
    virtual void SetMaterial(const shared_ptr<Material> material)
    {
        mMaterial = material;
    }

    /**
     * Creates a new shared_ptr to the material of class M and sets it to this class.
     *
     * @tparam M Class of the material.
     * @param material Material for this shape.
     */
    template <class M>
    void SetMaterial(const M material)
    {
        mMaterial = make_shared<M>(material);
    }

    /**
     * Sets the refractive index of this shape. If this shape contains any sub-shapes they should also have their
     * materials set to material by overriding this method.
     *
     * @param refractiveIndex Value to set the refractive index of this shape.
     */
    virtual void SetRefractiveIndex(const float refractiveIndex)
    {
        mN = refractiveIndex;
    }

    /**
     * @return Emitted light as a color
     */
    Color GetEmittedLight()
    {
        return mEmitted * mPowerEmitted;
    }

    /**
     * Sets the emitted color value and marks this shape as a light source.
     *
     * @param emitted .
     * @param power .
     */
    void SetEmittedLight(const Color &emitted, const float power)
    {
        mEmitted = emitted;
        mPowerEmitted = power;
        SetMaterial(NONE);
    }

    /**
     * Sets the normal modifier for this shape. This is an experimental feature...
     *
     * @param vmod Normal modifier for this shape.
     */
    virtual void SetNormalModifier(shared_ptr<VectorModifier> vmod)
    {
        mNormalModifier = vmod;
    }

private:

    /** Pointer to the material in this shape . */
    shared_ptr<Material> mMaterial = LAMBERTIAN;

    /** This shape's refractive index. */
    refractiveIndex mN = AIR_RI;

    /** This shape's normal vector modifier. Again, this is an experimental feature.*/
    shared_ptr<VectorModifier> mNormalModifier = nullptr;

    /** Color emitted by this shape. */
    Color mEmitted = BLACK;

    /** Power of the color emmited. */
    float mPowerEmitted = 0.0f;
};

#endif // RAY_TRACER_SHAPE_HPP