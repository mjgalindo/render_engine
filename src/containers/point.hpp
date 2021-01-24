/** ---------------------------------------------------------------------------
 ** point.hpp
 ** Contains a 3D point and defines operations with vectors. Every 3D shape needs
 ** a point in one way or another making this class a vital component of the ray
 ** tracer.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_POINT_H
#define RAY_TRACER_POINT_H

#include <array>
#include "dimensions.hpp"
#include "vect.hpp"

class Point
{

public:

    /** Value that defines a container of three floats as a point. */
    static constexpr float H = 1;

    /** When comparing float values we want to consider that
     * two values that differ by this threshold are equal. */
    static constexpr float TH = 0.000005;

    /**
     * @return New point at [0, 0, 0].
     */
    Point();

    /**
     * @param x Value for x.
     * @param y Value for y.
     * @param z Value for z.
     * @return New point at [x, y, z].
     */
    Point(const float x, const float y, const float z);

    /**
     * @param to Point which distance with respect to this one will be returned.
     * @return Absolute distance from this point to the point [to].
     */
    float Distance(const Point &to) const;

    /**
     * @param to Point to compare in wich dimension this point is further.
     * @return the dimension in which this point and [to] are furthest.
     */
    Dimension LongestDimension(const Point &to) const;

    /**
     * @return Value for x.
     */
    float GetX() const;

    /**
     * @return Value for y.
     */
    float GetY() const;

    /**
     * @return Value for z.
     */
    float GetZ() const;

    /**
     * Sets [x] as the new point's X.
     *
     * @param x Value of the new point's X.
     */
    void SetX(const float x);

    /**
     * Sets [y] as the new point's Y.
     *
     * @param y Value of the new point's Y.
     */
    void SetY(const float y);

    /**
     * Sets [z] as the new point's Z.
     *
     * @param z Value of the new point's Z.
     */
    void SetZ(const float z);

    /**
     * Sets [value] as the new point's dimension [dimension].
     *
     * @param dimension Dimension to be set.
     * @param value New value for the dimension [dimension].
     */
    void SetDimension(const Dimension &dimension, const float value);

    /**
     * @param p Point which values will be added to this one's.
     * @return New point sum of this and p.
     */
    Point operator+(const Point& p) const;

    /**
     * @param p Point which values will be subtracted to this one's.
     * @return New point from this minus p.
     */
    Vect operator-(const Point& p) const;

    /**
     * @param p Point by which this Point will be multiplied.
     * @return Product of this point and p.
     */
    float operator*(const Point& p) const;

    /**
     * @param v Vector by which this point will be moved.
     * @return New point result of moving this one in the direction and magnitude v.
     */
    Point operator+(const Vect& v) const;

    /**
     * @param v Vector by which this point will be moved.
     */
    void operator+=(const Vect& v);

    /**
     * @param v Vector by which this point will be moved.
     * @return New point result of moving this one in the opposite direction of v and magnitude v.
     */
    Point operator-(const Vect& v) const;

    /**
     * @param v Vector opposite to that by which this point will be moved.
     */
    void operator-=(const Vect& v);

    /**
     * @param p Point to compare with this one.
     * @return True if this Point is the same as p.
     */
    bool operator==(const Point& p) const;

    /**
     * @param p Point to compare with this one.
     * @return True if this POint is different from p.
     */
    bool operator!=(const Point& p) const;

    /**
     * @param p Point to compare with this one.
     * @return True if all the values in p are greater or equal to the values in this Point.
     */
    bool operator<=(const Point& p) const;

    /**
     * @param p Point to compare with this one.
     * @return True if all the values in p are smaller or equal to the values in this Point.
     */
    bool operator>=(const Point& p) const;

    /**
    * @param p Point to compare with this one.
    * @return True if all the values in p are smaller or equal to the values in this Point.
    */
    float operator[](const Dimension d) const;

    /**
     * Pretty print.
     *
     * @param out Stream that will receive the point p as a string.
     * @param p Point to send to the stream as a string.
     * @return Stream with a string version of p.
     */
    friend std::ostream& operator<<(std::ostream &out, const Point &p);

protected:

    /** This array is the actual container for the floats in a Point. */
    std::array<float, 3> mContainer;

    /** Values in this Point. */
    #define mX mContainer[X]
    #define mY mContainer[Y]
    #define mZ mContainer[Z]
};

#endif // RAY_TRACER_POINT_H