/* ---------------------------------------------------------------------------
 ** point.cpp
 ** TODO: Add doc.
 **
 ** Author: Miguel Jorge Galindo Ramos, NIA: 679954
 **         Santiago Gil Begué, NIA: 683482
 ** -------------------------------------------------------------------------*/

#include <point.hpp>

Point::Point(const float x, const float y, const float z)
{
    mX = x;
    mY = y;
    mZ = z;
}

float Point::GetX() const
{
    return mX;
}

float Point::GetY() const
{
    return mY;
}

float Point::GetZ() const
{
    return mZ;
}

Point Point::operator+(const Point& p) const
{
    float x = mX + p.mX;
    float y = mY + p.mY;
    float z = mZ + p.mZ;
    return Point(x, y, z);
}

Vect Point::operator-(const Point& p) const
{
    float x = mX - p.mX;
    float y = mY - p.mY;
    float z = mZ - p.mZ;
    return Vect(x, y, z);
}

float Point::operator*(const Point& p) const
{
    return mX * p.mX + mY * p.mY + mZ * p.mZ;
}

Point Point::operator+(const Vect& v) const
{
    float x = mX + v.GetX();
    float y = mY + v.GetY();
    float z = mZ + v.GetZ();
    return Point(x, y, z);
}

Point Point::operator-(const Vect& v) const
{
    float x = mX - v.GetX();
    float y = mY - v.GetY();
    float z = mZ - v.GetZ();
    return Point(x, y, z);
}

void Point::operator+=(const Vect& v)
{
    mX += v.GetX();
    mY += v.GetY();
    mZ += v.GetZ();
}

void Point::operator-=(const Vect& v)
{
    mX -= v.GetX();
    mY -= v.GetY();
    mZ -= v.GetZ();
}

bool Point::operator==(const Point& v) const
{
    return mX == v.GetX() & mY == v.GetY() & mZ == v.GetZ();
}

bool Point::operator!=(const Point& v) const
{
    return !(*this == v);
}

std::ostream& operator<< (std::ostream &out, const Point &p)
{
    out << "Point(" << p.mX << ", " << p.mY << ", " << p.mZ << ")";
    return out;
}