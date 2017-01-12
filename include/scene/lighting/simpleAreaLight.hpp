/** ---------------------------------------------------------------------------
 ** simpleAreaLight.hpp
 ** Defines a simple area light source made out of many point lights.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_SIMPLEAREALIGHT_HPP
#define RAY_TRACER_SIMPLEAREALIGHT_HPP

#include <lightSource.hpp>
#include <pointLight.hpp>

class SimpleAreaLight : public LightSource{
public:
    SimpleAreaLight(Point corner, Vect dir1, unsigned int dir1Lights, Vect dir2, unsigned int dir2Lights, float power,
            Color baseColor);

    /**
     * @throws Return the average color from all the point lights in this area light.
     */
    Color GetColor(const Point &point) const;

    /**
     * @return List of the lights contained within this lightSource.
     */
    vector<Point> GetLights() const;

private:
    vector<Point> mPoints;
};

#endif //RAY_TRACER_SIMPLEAREALIGHT_HPP
