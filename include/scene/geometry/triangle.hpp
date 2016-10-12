/* ---------------------------------------------------------------------------
** triangle.hpp
** TODO: Add doc.
**
** Author: Miguel Jorge Galindo Ramos, NIA: 679954
**         Santiago Gil Begué, NIA: 683482
** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_TRIANGLE_HPP
#define RAY_TRACER_TRIANGLE_HPP

#include <shape.hpp>
#include <vertex.hpp>

class Triangle : public Shape {

public:

    // TODO: Add doc.
    /**
     * Constructs a Triangle.
     *
     * @param a .
     * @param b .
     * @param c .
     * @return .
     */
    Triangle(const Vertex &a, const Vertex &b, const Vertex &c);

    // TODO: Add doc.
    /**
     * .
     *
     * @param lightRay .
     * @return .
     */
    float Intersect(const LightRay &lightRay) const;

    // TODO: Add doc.
    /**
     * .
     *
     * @param point .
     * @return .
     */
    Vect GetNormal(const Point &point) const;

private:

    // TODO: Add doc.
    /* . */
    Vertex mA, mB, mC;

    /* Cached values. */

    // TODO: Add doc.
    /* . */
    Vect v0, v1;
    float d00, d01, d11, denominator;
    Plane plane;
};

#endif // RAY_TRACER_TRIANGLE_HPP