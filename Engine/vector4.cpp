#include "vector4.h"
#include "vector3.h"
Vector4::Vector4() : x(0),y(0),z(0),w(0) {}
Vector4::Vector4(double x,double y,double z, double w)
{
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}
Vector4::Vector4(const Vector3& other,int w)
{
	x=other.x;
	y=other.y;
	z=other.z;
	this->w=w;
}

inline Vector4& Vector4::operator+=(const Vector4& rhs)
{
	x+=rhs.x;
	y+=rhs.y;
	z+=rhs.z;
	w+=rhs.w;
	return *this;
}
inline Vector4& Vector4::operator-=(const Vector4& rhs)
{
	x-=rhs.x;
	y-=rhs.y;
	z-=rhs.z;
	return *this;
}
inline double Vector4::Dot(const Vector4& lhs,const Vector4& rhs)
{
	return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z+lhs.w*rhs.w;
}

