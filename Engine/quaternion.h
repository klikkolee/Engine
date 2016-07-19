#ifndef ENGINE_QUATERNION_H
#define ENGINE_QUATERNION_H
#define _USE_MATH_DEFINES
#include <math.h>
#include "vector3.h"
class Matrix4;
class Quaternion final
{
	friend class Matrix4;
	friend class Vector3;
	friend class Transform;
	friend const Quaternion operator*(const Vector3& lhs, const Quaternion& rhs);
	double i,j,k,w;
	inline Quaternion(double i,double j,double k,double w) : i(i),j(j),k(k),w(w) {}
	explicit Quaternion(const Vector3& other);
	inline const Quaternion operator*(double rhs) const { return Quaternion(*this)*=rhs; }
	//inline friend Quaternion operator*(double lhs,const Quaternion& rhs) { return rhs*lhs; }
	inline Quaternion& operator*=(double rhs)
	{
		w*=rhs;
		i*=rhs;
		j*=rhs;
		k*=rhs;
		return *this;
	}
	inline Quaternion& operator/=(double rhs)
	{
		w /= rhs;
		i /= rhs;
		j /= rhs;
		k /= rhs;
		return *this;
	}
	//order: zyx
	static Quaternion EulerRotationRadian(double x,double y,double z);
	static Quaternion naturalLog(const Quaternion& value);
	static Quaternion exponential(const Quaternion& value);
	inline static Quaternion power(const Quaternion& base,double exponent) { return exponential(naturalLog(base)*exponent); }
public:
	inline Quaternion() : Quaternion(0,0,0,1) {};
	explicit Quaternion(Vector3 axis,double angle);
	
	inline const Quaternion operator*(const Quaternion& rhs) const { return Quaternion(*this)*=rhs; }
	inline const Quaternion operator*(const Vector3& rhs) const { return Quaternion(*this)*=rhs; }

	inline Quaternion& operator*=(const Quaternion& rhs)
	{
		double i = this->w*rhs.i + this->i*rhs.w + this->j*rhs.k - this->k*rhs.j;
		double j = this->w*rhs.j - this->i*rhs.k + this->j*rhs.w + this->k*rhs.i;
		double k = this->w*rhs.k + this->i*rhs.j - this->j*rhs.i + this->k*rhs.w;
		double w = this->w*rhs.w - this->i*rhs.i - this->j*rhs.j - this->k*rhs.k;
		this->i=i;
		this->j=j;
		this->k=k;
		this->w=w;
		return *this;
	}
	inline Quaternion& operator*=(const Vector3& rhs) { return ((*this)*=(Quaternion)rhs); }

	inline Quaternion Conjugate() const { return Quaternion(-i,-j,-k,w); }
	inline double Magnitude() const { return sqrt(SquaredMagnitude()); }
	inline double SquaredMagnitude() const { return i*i+j*j+k*k+w*w; }
	inline Vector3 Axis() const { return Vector3(i,j,k)/Magnitude(); }
	inline double Angle() const { return 2*acos(w); }
	//order: zyx
	inline static Quaternion EulerRotation(double x,double y,double z) { return EulerRotationRadian(x*M_PI/180,y*M_PI/180,z*M_PI/180); }
	inline static Quaternion Identity() { return Quaternion(0,0,0,1); }
	inline static Quaternion Slerp(const Quaternion& q0,const Quaternion& q1,double t) { return q0*power(q0.Conjugate()*q1,t); }
	static Quaternion RotationFromAToB(Vector3 a, Vector3 b);
};

inline const Quaternion operator*(const Vector3& lhs, const Quaternion& rhs) { return Quaternion(lhs)*=rhs; }

#endif //!ENGINE_QUATERNION_H