/* ---------------------------------------------------------------------------
 ** point.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include "point.hpp"

// TODO: Add doc.
/* */
static const float H = 1;

Point::Point(const float x, const float y, const float z)
{
    this->mX = x;
    this->mY = y;
    this->mZ = z;
}

float Point::GetX()
{
    return this->mX;
}

float Point::GetY()
{
    return this->mY;
}

float Point::GetZ()
{
    return this->mZ;
}

Point Point::operator+(const Point& p)
{
    const float x = this->mX + p.mX;
    const float y = this->mY + p.mY;
    const float z = this->mZ + p.mZ;
    return Point(x, y, z);
}

Vect Point::operator-(const Point& p)
{
    const float x = this->mX - p.mX;
    const float y = this->mY - p.mY;
    const float z = this->mZ - p.mZ;
    return Vect(x, y, z);
}

Point Point::operator*(const float k)
{
    const float x = this->mX * k;
    const float y = this->mY * k;
    const float z = this->mZ * k;
    return Point(x, y, z);
}