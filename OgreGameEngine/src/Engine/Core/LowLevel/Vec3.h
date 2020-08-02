#ifndef __Vec3_H__
#define __Vec3_H__

#include "Quat.h"

class Vec3
{
public:
    float x;
    float y;
    float z;

    // Constructors
    inline Vec3() : x(0), y(0), z(0) {}
    inline Vec3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}
    inline Vec3(float v[3]) : x(v[0]), y(v[1]), z(v[2]) {}
    inline Vec3(int v[3]) : x((float)v[0]), y((float)v[1]), z((float)v[2]) {}
    inline Vec3(const float* const v) : x(v[0]), y(v[1]), z(v[2]) {}
    
    inline Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
    inline Vec3(const Ogre::Vector3& v) : x(v.x), y(v.y), z(v.z) {}

    inline Vec3& operator=(const Vec3& v)
    {
        x = v.x; y = v.y;  z = v.z;
        return *this;
    }
    inline Vec3& operator=(const Ogre::Vector3& v)
    {
        x = v.x; y = v.y;  z = v.z;
        return *this;
    }


    // Comparators
    inline bool operator==(const Vec3& v) const
    {
        return (x == v.x && y == v.y && z == v.z);
    }
    inline bool operator!=(const Vec3& v) const
    {
        return (x != v.x || y != v.y || z != v.z);
    }
    inline bool operator < (const Vec3& v) const
    {
        return (x < v.x&& y < v.y&& z < v.z);
    }
    inline bool operator > (const Vec3& v) const
    {
        return (x > v.x && y > v.y && z > v.z);
    }

    
    // Arithmetic
    inline Vec3 operator+(const Vec3& v) const 
    {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }
    inline Vec3 operator-(const Vec3& v) const
    {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }
    inline Vec3 operator*(float f) const
    {
        return Vec3(x * f, y * f, z * f);
    }
    inline Vec3 operator*(const Vec3& v) const
    {
        return Vec3(x * v.x, y * v.y, z * v.z);
    }
    inline Vec3 operator/(float f) const
    {
        f = 1.0f / f;
        return Vec3(x * f, y * f, z * f);
    }
    inline Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }
   
    inline friend Vec3 operator*(float f, const Vec3& v)
    {
        return Vec3(f * v.x, f * v.y, f * v.z);
    }

    inline Vec3& operator+=(const Vec3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;

        return *this;
    }
    inline Vec3& operator-=(const Vec3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return *this;
    }
    inline Vec3& operator*=(float f)
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }
    inline Vec3& operator/=(float f)
    {
        f = 1.0f / f;

        x *= f;
        y *= f;
        z *= f;

        return *this;
    }


    // Geometry
    inline float length() const
    {
        return (float)sqrt(x * x + y * y + z * z);
    }
    inline float squaredLength() const
    {
        return x * x + y * y + z * z;
    }
    inline Vec3& normalise()
    {
        float f = length();

        // Will also work for zero-sized vectors, but will change nothing
        if (f > 1e-06f)
        {
            f = 1.0f / f;
            x *= f;
            y *= f;
            z *= f;
        }

        return *this;
    }
    
    inline float dotProduct(const Vec3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }
    inline Vec3 crossProduct(const Vec3& v) const
    {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
    
    inline Vec3 midPoint(const Vec3& v) const
    {
        return Vec3((x + v.x) * 0.5f, (y + v.y) * 0.5f, (z + v.z) * 0.5f);
    }
    inline Vec3 perpendicular()
    {
        static float fSquareZero = 1e-06f * 1e-06f;
        Vec3 perp = this->crossProduct(Vec3::UNIT_X);
        if (perp.squaredLength() < fSquareZero) perp = this->crossProduct(Vec3::UNIT_Y);
        return perp;
    }
    inline Quat getRotationTo(const Vec3& dest, const Vec3& fallbackAxis = Vec3::ZERO) const
    {
        float a = Ogre::Math::Sqrt(((const Vec3*)this)->squaredLength() * dest.squaredLength());
        float b = a + dest.dotProduct(*this);

        if (Ogre::Math::RealEqual(b, 2 * a) || a == 0) return Quat::IDENTITY;

        Vec3 axis;

        if (b < (float)1e-06 * a)
        {
            b = (float)0.0;
            axis = fallbackAxis != Vec3::ZERO ? fallbackAxis
                : Ogre::Math::Abs(x) > Ogre::Math::Abs(z) ? Vec3(-y, x, (float)0.0)
                : Vec3((float)0.0, -z, y);
        }
        else
        {
            axis = this->crossProduct(dest);
        }

        Quat q(b, axis.x, axis.y, axis.z);
        q.normalise();
        return q;
    }
    float distance(const Vec3& rhs) const
    {
        return (*this - rhs).length();
    }
    
    inline void makeFloor(const Vec3& v)
    {
        if (v.x < x) x = v.x;
        if (v.y < y) y = v.y;
        if (v.z < z) z = v.z;
    }
    inline void makeCeil(const Vec3& v)
    {
        if (v.x > x) x = v.x;
        if (v.y > y) y = v.y;
        if (v.z > z) z = v.z;
    }

    static const Vec3 ZERO;
    static const Vec3 UNIT_X;
    static const Vec3 UNIT_Y;
    static const Vec3 UNIT_Z;
    static const Vec3 NEGATIVE_UNIT_X;
    static const Vec3 NEGATIVE_UNIT_Y;
    static const Vec3 NEGATIVE_UNIT_Z;
    static const Vec3 UNIT_SCALE;
};

#endif // !__Vec3_H__
