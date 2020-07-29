#ifndef __QUAT_H__
#define __QUAT_H__

#include "Vec3.h"

#define Q(q) Ogre::Quaternion(q.w, q.x, q.y, q.z)

class Quat
{
public:
    float w;
    float x;
    float y;
    float z;

    // Constructors
    inline Quat() : w(1), x(0), y(0), z(0) {}
    inline Quat(float fW, float fX, float fY, float fZ) : w(fW), x(fX), y(fY), z(fZ) {}
    inline Quat(float* valptr) { memcpy(&w, valptr, sizeof(float) * 4); }

    inline Quat(const Quat& rhs) : w(rhs.w), x(rhs.x), y(rhs.y), z(rhs.z) {}
    inline Quat(const Ogre::Quaternion& q) : w(q.w), x(q.x), y(q.y), z(q.z) {}
    
    inline Quat(const Ogre::Matrix3& rot) { this->FromRotationMatrix(rot); }
    inline Quat(const Ogre::Radian& rfAngle, const Vec3& rkAxis) { this->FromAngleAxis(rfAngle, rkAxis); }
    inline Quat(const Vec3& xaxis, const Vec3& yaxis, const Vec3& zaxis) { this->FromAxes(xaxis, yaxis, zaxis); }
    inline Quat(const Vec3* akAxis) { this->FromAxes(akAxis); }


    // Constructor helpers
    void FromRotationMatrix(const Ogre::Matrix3& kRot);
    void ToRotationMatrix(Ogre::Matrix3& kRot) const;
    
    void FromAngleAxis(const Ogre::Radian& rfAngle, const Vec3& rkAxis);
    void ToAngleAxis(Ogre::Radian& rfAngle, Vec3& rkAxis) const;
    inline void ToAngleAxis(Ogre::Degree& dAngle, Vec3& rkAxis) const;

    void FromAxes(const Vec3* akAxis);
    void FromAxes(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis);
    void ToAxes(Vec3* akAxis) const;
    void ToAxes(Vec3& xAxis, Vec3& yAxis, Vec3& zAxis) const;

    Vec3 xAxis() const;
    Vec3 yAxis() const;
    Vec3 zAxis() const;

    inline bool isNaN() const
    {
        return Ogre::Math::isNaN(x) || Ogre::Math::isNaN(y) || Ogre::Math::isNaN(z) || Ogre::Math::isNaN(w);
    }


    // Operators
    inline Quat& operator=(const Quat& rkQ)
    {
        w = rkQ.w;
        x = rkQ.x;
        y = rkQ.y;
        z = rkQ.z;
        return *this;
    }
    Quat operator+(const Quat& rkQ) const;
    Quat operator-(const Quat& rkQ) const;
    Quat operator*(const Quat& rkQ) const;
    Quat operator*(float s) const
    {
        return Quat(s * w, s * x, s * y, s * z);
    }
    friend Quat operator*(float s, const Quat& q)
    {
        return q * s;
    }
    Quat operator-() const { return Quat(-w, -x, -y, -z); }
    inline bool operator==(const Quat& rhs) const
    {
        return (rhs.x == x) && (rhs.y == y) &&
            (rhs.z == z) && (rhs.w == w);
    }
    inline bool operator!=(const Quat& rhs) const
    {
        return !operator==(rhs);
    }
    inline friend std::ostream& operator<<(std::ostream& o, const Quat& q)
    {
        o << "Quat(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
        return o;
    }


    // Quaternion operations 
    float dot(const Quat& rkQ) const { return w * rkQ.w + x * rkQ.x + y * rkQ.y + z * rkQ.z; }
    float length() const { return Ogre::Math::Sqrt(w * w + x * x + y * y + z * z); }
    float normalise() 
    {
        float len = length();
        *this = 1.0f / len * *this;
        return len;
    }
    Quat inverse() const;
    Quat unitInverse() const;
    Quat exp() const;
    Quat log() const;

    // Rotations and Interpolation
    Vec3 operator*(const Vec3& rkVector) const;
    
    bool equals(const Quat& rhs, const Ogre::Radian& tolerance) const
    {
        float d = dot(rhs);
        Ogre::Radian angle = Ogre::Math::ACos(2.0f * d * d - 1.0f);
        return Ogre::Math::Abs(angle.valueRadians()) <= tolerance.valueRadians();
    }
    inline bool orientationEquals(const Quat& other, float tolerance = 1e-3f) const
    {
        float d = this->dot(other);
        return 1 - d * d < tolerance;
    }
    static Quat Slerp(float fT, const Quat& rkP, const Quat& rkQ, bool shortestPath = false);
    static Quat SlerpExtraSpins(float fT, const Quat& rkP, const Quat& rkQ, int iExtraSpins);
    static void Intermediate(const Quat& rkQ0, const Quat& rkQ1, const Quat& rkQ2, Quat& rka, Quat& rkB);
    static Quat Squad(float fT, const Quat& rkP, const Quat& rkA, const Quat& rkB, const Quat& rkQ, bool shortestPath = false);
    static Quat nlerp(float fT, const Quat& rkP, const Quat& rkQ, bool shortestPath = false);

    // special values
    static const Quat ZERO;
    static const Quat IDENTITY;
    static const float msEpsilon;
};

#endif // !__QUAT_H__
