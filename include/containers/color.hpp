/* ---------------------------------------------------------------------------
 ** color.hpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_COLOR_HPP
#define RAY_TRACER_COLOR_HPP

#include <algorithm>
#include <climits>

using namespace std;

class Color
{

public:

    /**
     * Constructor with no color (black).
     *
     * @return a black Color.
     */
    constexpr Color()
    : mR(0), mG(0), mB(0)
    {}

    // TODO: Add doc.
    /**
     * .
     *
     * @param r value for red.
     * @param g value for green.
     * @param b value for blue.
     * @return .
     */
    constexpr Color(const float r, const float g, const float b)
    : mR(r), mG(g), mB(b)
    {}

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    constexpr float GetR() const
    {
        return mR;
    }

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    constexpr float GetG() const
    {
        return mG;
    }

    // TODO: Add doc.
    /**
     * .
     *
     * @return .
     */
    constexpr float GetB() const
    {
        return mB;
    }

    // TODO: Add doc. k must be >= 0
    /**
     * Overloads + operator to .
     *
     * @param color .
     * @return .
     */
    Color operator+(const Color &color) const
    {
        return Color(min(mR + color.mR, UCHAR_MAX),
                     min(mG + color.mG, UCHAR_MAX),
                     min(mB + color.mB, UCHAR_MAX))
        ;
    }

    // TODO: Add doc. k must be >= 0
    /**
     * Overloads += operator to add the RGB values
     * of the new color to this one's.
     *
     * @param color .
     */
    void operator+=(const Color &color)
    {
        mR = min(mR + color.mR, UCHAR_MAX);
        mG = min(mG + color.mG, UCHAR_MAX);
        mB = min(mB + color.mB, UCHAR_MAX);
    }

    // TODO: Add doc. k must be >= 0
    /**
     * Overloads * operator to return a Color result
     * of multiplying all values in this Color by k.
     *
     * @param k .
     * @return New color result of multiplying the
     *         RGB values in this color by k.
     */
    Color operator*(const float k) const
    {
        return Color(min(mR*k, UCHAR_MAX),
                     min(mG*k, UCHAR_MAX),
                     min(mB*k, UCHAR_MAX));
    }

    // TODO: Add doc. k must be >= 0
    /**
     * Overloads *= operator to multiply all
     * values of this color by k.
     *
     * @param k .
     */
    void operator*=(const float k)
    {
        mR = min(mR*k, UCHAR_MAX);
        mG = min(mG*k, UCHAR_MAX);
        mB = min(mB*k, UCHAR_MAX);
    }

    // TODO: Add doc. k must be > 0
    /**
     * .
     *
     * @param k .
     * @return .
     */
    Color operator/(const float k) const
    {
        return Color(mR / k,
                     mG / k,
                     mB / k);
    }

private:

    // TODO: Add doc.
    /* . */
    float mR;
    float mG;
    float mB;
};

static constexpr Color WHITE    (255, 255, 255);
static constexpr Color BLACK    (0, 0, 0);
static constexpr Color RED      (255, 0, 0);
static constexpr Color GREEN    (0, 255, 0);
static constexpr Color BLUE     (0, 0, 255);

#endif // RAY_TRACER_COLOR_HPP