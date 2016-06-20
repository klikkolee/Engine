#ifndef QUATERNION_H
#define QUATERNION_H
#define _USE_MATH_DEFINES
#include <math.h>
#include "vector3.hpp"
class mat4;
class quaternion final
{
	friend class mat4;
	double i,j,k,w;
	inline quaternion(double i,double j,double k,double w) : i(i),j(j),k(k),w(w) {}
	inline const quaternion operator*(double rhs) const { return quaternion(*this)*=rhs; }
	//inline friend quaternion operator*(double lhs,const quaternion& rhs) { return rhs*lhs; }
	inline quaternion& operator*=(double rhs)
	{
		w*=rhs;
		i*=rhs;
		j*=rhs;
		k*=rhs;
		return *this;
	}
	//order: zyx
	static quaternion eulerRotationRadian(double x,double y,double z);
	static quaternion naturalLog(const quaternion& value);
	static quaternion exponential(const quaternion& value);
	inline static quaternion power(const quaternion& base,double exponent) { return exponential(naturalLog(base)*exponent); }
public:
	inline quaternion() : quaternion(0,0,0,1) {};
	explicit quaternion(const vector3& axis,double angle);
	explicit quaternion(const vector3& other);
	
	inline const quaternion operator*(const quaternion& rhs) const { return quaternion(*this)*=rhs; }
	inline const quaternion operator*(const vector3& rhs) const { return quaternion(*this)*=rhs; }

	inline quaternion& operator*=(const quaternion& rhs)
	{
		double i=this->w*rhs.i-this->i*rhs.w-this->j*rhs.k-this->k*rhs.j;
		double j=this->w*rhs.j-this->i*rhs.k-this->j*rhs.w-this->k*rhs.i;
		double k=this->w*rhs.k-this->i*rhs.j-this->j*rhs.i-this->k*rhs.w;
		double w=this->w*rhs.w-this->i*rhs.i-this->j*rhs.j-this->k*rhs.k;
		this->i=i;
		this->j=j;
		this->k=k;
		this->w=w;
		return *this;
	}
	inline quaternion& operator*=(const vector3& rhs) { return ((*this)*=(quaternion)rhs); }

	inline quaternion conjugate() const { return quaternion(-i,-j,-k,w); }
	inline double magnitude() const { return sqrt(squaredMagnitude()); }
	inline double squaredMagnitude() const { return i*i+j*j+k*k+w*w; }
	inline vector3 axis() const { return vector3(i,j,k)/magnitude(); }
	inline double angle() const { return 2*acos(w); }
	//order: zyx
	inline static quaternion eulerRotation(double x,double y,double z) { return eulerRotationRadian(x*M_PI/180,y*M_PI/180,z*M_PI/180); }
	inline static quaternion identity() { return quaternion(0,0,0,1); }
	inline static quaternion slerp(const quaternion& q0,const quaternion& q1,double t) { return q0*power(q0.conjugate()*q1,t); }
};

inline const quaternion operator*(const vector3& lhs, const quaternion& rhs) { return quaternion(lhs)*=rhs; }

#endif