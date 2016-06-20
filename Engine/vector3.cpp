#include "vector3.hpp"
#include "vector4.hpp"
#include <math.h>
vector3::vector3()
{
	x,y,z=0;
}
vector3::vector3(double x,double y,double z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}
vector3::vector3(const vector4& other)
{
	x=other.x;
	y=other.y;
	z=other.z;
}

double vector3::squaredMagnitude()
{
	return x*x+y*y+z*z;
}

double vector3::magnitude()
{
	return sqrt(squaredMagnitude());
}

vector3 vector3::unit()
{
	return vector3(*this)/=this->magnitude();
}

