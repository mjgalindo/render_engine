/** ---------------------------------------------------------------------------
 ** vectorModifier.hpp
 ** Parent class for vector modifiers. This will allow for a greater variety of
 ** patterned materials.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_NORMALMODIFIER_HPP
#define RAY_TRACER_NORMALMODIFIER_HPP

#include <memory>
#include <point.hpp>
#include <vect.hpp>

class VectorModifier
{

public:

    /**
    * @param vect Vector to modify.
    * @param point Point at which the modification will be calculated.
    * @return The input vector, this class just defines the method, it does nothing.
    */
    virtual Vect Modify(const Vect &vect, const Point &point) const
    {
        return vect;
    }
};

#endif // RAY_TRACER_NORMALMODIFIER_HPP