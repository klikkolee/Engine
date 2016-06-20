#include "vector4.hpp"
#include "vector3.hpp"
vector4::vector4()
{
	x,y,z,w=0;
}
vector4::vector4(double x,double y,double z, double w)
{
	this->x=x;
	this->y=y;
	this->z=z;
	this->w=w;
}
vector4::vector4(const vector3& other,int w)
{
	x=other.x;
	y=other.y;
	z=other.z;
	this->w=w;
}

inline vector4& vector4::operator+=(const vector4& rhs)
{
	x+=rhs.x;
	y+=rhs.y;
	z+=rhs.z;
	w+=rhs.w;
	return *this;
}
inline vector4& vector4::operator-=(const vector4& rhs)
{
	x-=rhs.x;
	y-=rhs.y;
	z-=rhs.z;
	return *this;
}
inline double vector4::dot(const vector4& lhs,const vector4& rhs)
{
	return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z+lhs.w*rhs.w;
}

