#include "Quat.h"
#include "Vec3.h"

const float Quat::msEpsilon = 1e-03;
const Quat Quat::ZERO(0, 0, 0, 0);
const Quat Quat::IDENTITY(1, 0, 0, 0);


void Quat::FromRotationMatrix(const Ogre::Matrix3& kRot)
{
	float fTrace = kRot[0][0] + kRot[1][1] + kRot[2][2];
	float fRoot;

	if (fTrace > 0.0)
	{
		fRoot = Ogre::Math::Sqrt(fTrace + 1.0f);
		w = 0.5f * fRoot;
		fRoot = 0.5f / fRoot;
		x = (kRot[2][1] - kRot[1][2]) * fRoot;
		y = (kRot[0][2] - kRot[2][0]) * fRoot;
		z = (kRot[1][0] - kRot[0][1]) * fRoot;
	}
	else
	{
		static size_t s_iNext[3] = { 1, 2, 0 };
		size_t i = 0;
		if (kRot[1][1] > kRot[0][0])
			i = 1;
		if (kRot[2][2] > kRot[i][i])
			i = 2;
		size_t j = s_iNext[i];
		size_t k = s_iNext[j];

		fRoot = Ogre::Math::Sqrt(kRot[i][i] - kRot[j][j] - kRot[k][k] + 1.0f);
		float* apkQuat[3] = { &x, &y, &z };
		*apkQuat[i] = 0.5f * fRoot;
		fRoot = 0.5f / fRoot;
		w = (kRot[k][j] - kRot[j][k]) * fRoot;
		*apkQuat[j] = (kRot[j][i] + kRot[i][j]) * fRoot;
		*apkQuat[k] = (kRot[k][i] + kRot[i][k]) * fRoot;
	}
}

void Quat::ToRotationMatrix(Ogre::Matrix3& kRot) const
{
	float fTx = x + x;
	float fTy = y + y;
	float fTz = z + z;
	float fTwx = fTx * w;
	float fTwy = fTy * w;
	float fTwz = fTz * w;
	float fTxx = fTx * x;
	float fTxy = fTy * x;
	float fTxz = fTz * x;
	float fTyy = fTy * y;
	float fTyz = fTz * y;
	float fTzz = fTz * z;

	kRot[0][0] = 1.0f - (fTyy + fTzz);
	kRot[0][1] = fTxy - fTwz;
	kRot[0][2] = fTxz + fTwy;
	kRot[1][0] = fTxy + fTwz;
	kRot[1][1] = 1.0f - (fTxx + fTzz);
	kRot[1][2] = fTyz - fTwx;
	kRot[2][0] = fTxz - fTwy;
	kRot[2][1] = fTyz + fTwx;
	kRot[2][2] = 1.0f - (fTxx + fTyy);
}

void Quat::FromAngleAxis(const Ogre::Radian& rfAngle, const Vec3& rkAxis)
{
	Ogre::Radian fHalfAngle(0.5 * rfAngle);
	float fSin = Ogre::Math::Sin(fHalfAngle);
	w = Ogre::Math::Cos(fHalfAngle);
	x = fSin * rkAxis.x;
	y = fSin * rkAxis.y;
	z = fSin * rkAxis.z;
}

void Quat::ToAngleAxis(Ogre::Radian& rfAngle, Vec3& rkAxis) const
{
	float fSqrLength = x * x + y * y + z * z;
	if (fSqrLength > 0.0)
	{
		rfAngle = 2.0 * Ogre::Math::ACos(w);
		float fInvLength = Ogre::Math::InvSqrt(fSqrLength);
		rkAxis.x = x * fInvLength;
		rkAxis.y = y * fInvLength;
		rkAxis.z = z * fInvLength;
	}
	else
	{
		rfAngle = Ogre::Radian(0.0);
		rkAxis.x = 1.0;
		rkAxis.y = 0.0;
		rkAxis.z = 0.0;
	}
}

void Quat::FromAxes(const Vec3* akAxis)
{
	Ogre::Matrix3 kRot;
	for (size_t iCol = 0; iCol < 3; iCol++)
	{
		kRot[0][iCol] = akAxis[iCol].x;
		kRot[1][iCol] = akAxis[iCol].y;
		kRot[2][iCol] = akAxis[iCol].z;
	}
	FromRotationMatrix(kRot);
}

void Quat::FromAxes(const Vec3& xaxis, const Vec3& yaxis, const Vec3& zaxis)
{
	Ogre::Matrix3 kRot;
	kRot.FromAxes(Ogre::Vector3(xaxis.x, xaxis.y, xaxis.z), 
		Ogre::Vector3(yaxis.x, yaxis.y, yaxis.z),
		Ogre::Vector3(zaxis.x, zaxis.y, zaxis.z));
	FromRotationMatrix(kRot);
}

void Quat::ToAxes(Vec3* akAxis) const
{
	Ogre::Matrix3 kRot;
	ToRotationMatrix(kRot);
	for (size_t iCol = 0; iCol < 3; iCol++)
	{
		akAxis[iCol].x = kRot[0][iCol];
		akAxis[iCol].y = kRot[1][iCol];
		akAxis[iCol].z = kRot[2][iCol];
	}
}

Vec3 Quat::xAxis(void) const
{
	float fTy = 2.0f * y;
	float fTz = 2.0f * z;
	float fTwy = fTy * w;
	float fTwz = fTz * w;
	float fTxy = fTy * x;
	float fTxz = fTz * x;
	float fTyy = fTy * y;
	float fTzz = fTz * z;

	return Vec3(1.0f - (fTyy + fTzz), fTxy + fTwz, fTxz - fTwy);
}

Vec3 Quat::yAxis(void) const
{
	float fTx = 2.0f * x;
	float fTy = 2.0f * y;
	float fTz = 2.0f * z;
	float fTwx = fTx * w;
	float fTwz = fTz * w;
	float fTxx = fTx * x;
	float fTxy = fTy * x;
	float fTyz = fTz * y;
	float fTzz = fTz * z;

	return Vec3(fTxy - fTwz, 1.0f - (fTxx + fTzz), fTyz + fTwx);
}

Vec3 Quat::zAxis(void) const
{
	float fTx = 2.0f * x;
	float fTy = 2.0f * y;
	float fTz = 2.0f * z;
	float fTwx = fTx * w;
	float fTwy = fTy * w;
	float fTxx = fTx * x;
	float fTxz = fTz * x;
	float fTyy = fTy * y;
	float fTyz = fTz * y;

	return Vec3(fTxz + fTwy, fTyz - fTwx, 1.0f - (fTxx + fTyy));
}

void Quat::ToAxes(Vec3& xaxis, Vec3& yaxis, Vec3& zaxis) const
{
	Ogre::Matrix3 kRot;

	ToRotationMatrix(kRot);

	xaxis.x = kRot[0][0];
	xaxis.y = kRot[1][0];
	xaxis.z = kRot[2][0];

	yaxis.x = kRot[0][1];
	yaxis.y = kRot[1][1];
	yaxis.z = kRot[2][1];

	zaxis.x = kRot[0][2];
	zaxis.y = kRot[1][2];
	zaxis.z = kRot[2][2];
}


Quat Quat::operator+(const Quat& rkQ) const
{
	return Quat(w + rkQ.w, x + rkQ.x, y + rkQ.y, z + rkQ.z);
}

Quat Quat::operator-(const Quat& rkQ) const
{
	return Quat(w - rkQ.w, x - rkQ.x, y - rkQ.y, z - rkQ.z);
}

Quat Quat::operator*(const Quat& rkQ) const
{
	return Quat
	(
		w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
		w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
		w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
		w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
	);
}


Quat Quat::inverse() const
{
	float fNorm = w * w + x * x + y * y + z * z;
	if (fNorm > 0.0)
	{
		float fInvNorm = 1.0f / fNorm;
		return Quat(w * fInvNorm, -x * fInvNorm, -y * fInvNorm, -z * fInvNorm);
	}
	else
	{
		return ZERO;
	}
}

Quat Quat::unitInverse() const
{
	return Quat(w, -x, -y, -z);
}

Quat Quat::exp() const
{
	Ogre::Radian fAngle(Ogre::Math::Sqrt(x * x + y * y + z * z));
	float fSin = Ogre::Math::Sin(fAngle);
	float fExpW = Ogre::Math::Exp(w);

	Quat kResult;
	kResult.w = fExpW * Ogre::Math::Cos(fAngle);

	if (Ogre::Math::Abs(fAngle.valueRadians()) >= msEpsilon)
	{
		float fCoeff = fExpW * (fSin / (fAngle.valueRadians()));
		kResult.x = fCoeff * x;
		kResult.y = fCoeff * y;
		kResult.z = fCoeff * z;
	}
	else
	{
		kResult.x = fExpW * x;
		kResult.y = fExpW * y;
		kResult.z = fExpW * z;
	}

	return kResult;
}

Quat Quat::log() const
{
	Quat kResult;
	kResult.w = 0.0;

	if (Ogre::Math::Abs(w) < 1.0)
	{
		float fNormV = Ogre::Math::Sqrt(x * x + y * y + z * z);
		Ogre::Radian fAngle(Ogre::Math::ATan2(fNormV, w));

		float fSin = Ogre::Math::Sin(fAngle);
		if (Ogre::Math::Abs(fSin) >= msEpsilon)
		{
			float fCoeff = fAngle.valueRadians() / fSin;
			kResult.x = fCoeff * x;
			kResult.y = fCoeff * y;
			kResult.z = fCoeff * z;
			return kResult;
		}
	}

	kResult.x = x;
	kResult.y = y;
	kResult.z = z;

	return kResult;
}


Vec3 Quat::operator* (const Vec3& v) const
{
	Vec3 uv, uuv;
	Vec3 qvec(x, y, z);
	uv = qvec.crossProduct(v);
	uuv = qvec.crossProduct(uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;

}

Quat Quat::Slerp(float fT, const Quat& rkP,	const Quat& rkQ, bool shortestPath)
{
	float fCos = rkP.dot(rkQ);
	Quat rkT;

	// Do we need to invert rotation?
	if (fCos < 0.0f && shortestPath)
	{
		fCos = -fCos;
		rkT = -rkQ;
	}
	else
	{
		rkT = rkQ;
	}

	if (Ogre::Math::Abs(fCos) < 1 - msEpsilon)
	{
		// Standard case (slerp)
		float fSin = Ogre::Math::Sqrt(1 - Ogre::Math::Sqr(fCos));
		Ogre::Radian fAngle = Ogre::Math::ATan2(fSin, fCos);
		float fInvSin = 1.0f / fSin;
		float fCoeff0 = Ogre::Math::Sin((1.0f - fT) * fAngle) * fInvSin;
		float fCoeff1 = Ogre::Math::Sin(fT * fAngle) * fInvSin;
		return fCoeff0 * rkP + fCoeff1 * rkT;
	}
	else
	{
		// There are two situations:
		// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
		//    interpolation safely.
		// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
		//    are an infinite number of possibilities interpolation. but we haven't
		//    have method to fix this case, so just use linear interpolation here.
		Quat t = (1.0f - fT) * rkP + fT * rkT;
		// taking the complement requires renormalisation
		t.normalise();
		return t;
	}
}

Quat Quat::SlerpExtraSpins(float fT, const Quat& rkP, const Quat& rkQ, int iExtraSpins)
{
	float fCos = rkP.dot(rkQ);
	Ogre::Radian fAngle(Ogre::Math::ACos(fCos));

	if (Ogre::Math::Abs(fAngle.valueRadians()) < msEpsilon)
		return rkP;

	float fSin = Ogre::Math::Sin(fAngle);
	Ogre::Radian fPhase(Ogre::Math::PI * iExtraSpins * fT);
	float fInvSin = 1.0f / fSin;
	float fCoeff0 = Ogre::Math::Sin((1.0f - fT) * fAngle - fPhase) * fInvSin;
	float fCoeff1 = Ogre::Math::Sin(fT * fAngle + fPhase) * fInvSin;
	return fCoeff0 * rkP + fCoeff1 * rkQ;
}

void Quat::Intermediate(const Quat& rkQ0, const Quat& rkQ1, const Quat& rkQ2, Quat& rkA, Quat& rkB)
{
	Quat kQ0inv = rkQ0.unitInverse();
	Quat kQ1inv = rkQ1.unitInverse();
	Quat rkP0 = kQ0inv * rkQ1;
	Quat rkP1 = kQ1inv * rkQ2;
	Quat kArg = 0.25 * (rkP0.log() - rkP1.log());
	Quat kMinusArg = -kArg;

	rkA = rkQ1 * kArg.exp();
	rkB = rkQ1 * kMinusArg.exp();
}

Quat Quat::Squad(float fT, const Quat& rkP, const Quat& rkA, const Quat& rkB, const Quat& rkQ, bool shortestPath)
{
	float fSlerpT = 2.0f * fT * (1.0f - fT);
	Quat kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
	Quat kSlerpQ = Slerp(fT, rkA, rkB);
	return Slerp(fSlerpT, kSlerpP, kSlerpQ);
}

Quat Quat::nlerp(float fT, const Quat& rkP, const Quat& rkQ, bool shortestPath)
{
	Quat result;
	float fCos = rkP.dot(rkQ);
	if (fCos < 0.0f && shortestPath)
	{
		result = rkP + fT * ((-rkQ) - rkP);
	}
	else
	{
		result = rkP + fT * (rkQ - rkP);
	}
	result.normalise();
	return result;
}