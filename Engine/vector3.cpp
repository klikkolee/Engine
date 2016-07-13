#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"
#include <math.h>
Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(double x,double y,double z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}
Vector3::Vector3(const Quaternion & other) : x(other.i), y(other.j), z(other.k)
{
}
Vector3::Vector3(const Vector4& other)
{
	x=other.x;
	y=other.y;
	z=other.z;
}

double Vector3::SquaredMagnitude()
{
	return x*x+y*y+z*z;
}

double Vector3::Magnitude()
{
	return sqrt(SquaredMagnitude());
}

Vector3 Vector3::Unit()
{
	return Vector3(*this)/=this->Magnitude();
}

