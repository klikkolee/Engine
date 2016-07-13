#include "quaternion.h"
#include "vector3.h"
#define _USE_MATH_DEFINES
#include <math.h>
Quaternion::Quaternion( Vector3 axis,double angle)
{
	Vector3::Normalize(axis);
	double halfAngle=angle*M_PI/360;
	i=axis.x*sin(halfAngle);
	j=axis.y*sin(halfAngle);
	k=axis.z*sin(halfAngle);
	w=cos(halfAngle);
}
Quaternion::Quaternion(const Vector3& other) : i(other.x), j(other.y), k(other.z), w(0) {}
Quaternion Quaternion::EulerRotationRadian(double x,double y,double z)
{
	x/=2;
	y/=2;
	z/=2;
	double i=sin(x)*cos(y)*cos(z)-cos(x)*sin(y)*sin(z);
	double j=cos(x)*sin(y)*cos(z)+sin(x)*cos(y)*sin(z);
	double k=cos(x)*cos(y)*sin(z)-sin(x)*sin(y)*cos(z);
	double w=cos(x)*cos(y)*cos(z)+sin(x)*sin(y)*sin(z);
	return Quaternion(i,j,k,w);
}
Quaternion Quaternion::RotationFromAToB(Vector3 a, Vector3 b)
{
	return Vector3::Cross(a,b).Magnitude() == 0 ? Quaternion::Identity(): Quaternion(Vector3::Cross(a,b),acos(Vector3::Dot(a,b)));
}
Quaternion Quaternion::naturalLog(const Quaternion& value)
{
	return Quaternion(value.i/value.Magnitude()*acos(value.w),
					  value.j/value.Magnitude()*acos(value.w),
					  value.k/value.Magnitude()*acos(value.w),
					  log(value.Magnitude()));
}
Quaternion Quaternion::exponential(const Quaternion& value)
{
	double vectorPartMagnitude=Vector3(value.i,value.j,value.k).Magnitude();
	double eToTheW=exp(value.w);
	return Quaternion(eToTheW*value.i/value.Magnitude()*sin(vectorPartMagnitude),
					  eToTheW*value.j/value.Magnitude()*sin(vectorPartMagnitude),
					  eToTheW*value.k/value.Magnitude()*sin(vectorPartMagnitude),
					  eToTheW*cos(vectorPartMagnitude));
}

