/** ---------------------------------------------------------------------------
 ** color.hpp
 ** Container for an RGB color value. It's stored in 3 floats to allow for values
 ** over 255 which will need to be clamped when showed.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#ifndef RAY_TRACER_COLOR_HPP
#define RAY_TRACER_COLOR_HPP

#include <algorithm>
#include <climits>
#include <cmath>

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

    /**
     * @return Unclamped Red value in this color.
     */
    constexpr float GetR() const
    {
        return mR;
    }

    /**
     * @return Unclamped Green value in this color.
     */
    constexpr float GetG() const
    {
        return mG;
    }

    /**
     * @return Unclamped Green value in this color.
     */
    constexpr float GetB() const
    {
        return mB;
    }

    /**
     * @param color Color which values will be summed to this one's.
     * @return New color sum of this and the other color's RGB values.
     */
    Color operator+(const Color &color) const
    {
        return Color(mR + color.mR,
                     mG + color.mG,
                     mB + color.mB);
    }

    /**
     * @param color Color which values will be summed to this one's.
     */
    void operator+=(const Color &color)
    {
        mR += color.mR;
        mG += color.mG;
        mB += color.mB;
    }

    /**
     * @param color Color by which this color's values will be multiplied.
     * @return New color product of this and the other color's RGB values.
     */
    Color operator*(const Color &color) const
    {
        return Color(mR * color.mR,
                     mG * color.mG,
                     mB * color.mB);
    }

    /**
     * @param k Value by which this color's RGB values will be multiplied. k must be greater
     * or equal to 0 (negative colors are evil).
     * @return New color product of this one's RGB values and k.
     */
    Color operator*(const float k) const
    {
        return Color(mR*k, mG*k, mB*k);
    }

    /**
     * @param k Value by which this color's RGB values will be multiplied. k must be greater
     * or equal to 0 (negative colors are evil).
     */
    void operator*=(const float k)
    {
        mR *= k;
        mG *= k;
        mB *= k;
    }

    /**
     * @param Value by which this color's RGB values will be divided. k must be greater
     * or equal to 0 (negative colors are evil).
     * @return New color result of dividing the RGB values in this color by k.
     */
    Color operator/(const float k) const
    {
        return Color(mR/k, mG/k, mB/k);
    }

    /**
     * @param color Value with which this color's RGB values will be compared.
     * @return True if this Color is equal to color.
     */
    bool operator==(const Color &color) const
    {
        return (color.mR == mR) && (color.mG == mG) && (color.mB == mB);
    }

    /**
     * @param color Value with which this color's RGB values will be compared.
     * @return False if this Color is equal to color.
     */
    bool operator!=(const Color &color) const
    {
        return ! (*this == color);
    }

    Color Clamp() const
    {
        return Color(
                std::max(0.0f, std::min(mR, 1.0f)),
                std::max(0.0f, std::min(mG, 1.0f)),
                std::max(0.0f, std::min(mB, 1.0f)));
    }

    Color GammaCorrect() const
    {
        static const float gamma = 2.2f;
        return Color(pow(mR, gamma), pow(mG, gamma), pow(mB, gamma));
    }

private:

    /** This color's RGB values. */
    float mR;
    float mG;
    float mB;
};

/** Some color definitions to make life easier when making simple scenes. */
static constexpr Color WHITE    (0.85f, 0.85f, 0.85f);
static constexpr Color GRAY     (0.5f, 0.5f, 0.5f);
static constexpr Color BLACK    (0.0f, 0.0f, 0.0f);
static constexpr Color RED      (0.85f, 0.0f, 0.0f);
static constexpr Color GREEN    (0.0f, 0.85f, 0.0f);
static constexpr Color BLUE     (0.0f, 0.0f, 0.85f);
static constexpr Color YELLOW   (0.85f, 0.85f, 0.0f);
static constexpr Color PURPLE   (0.85f, 0.0f, 0.85f);
static constexpr Color SKY_BLUE (0.0f, 0.85f, 0.85f);

#endif // RAY_TRACER_COLOR_HPP