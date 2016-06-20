#include "quaternion.hpp"
#include "vector3.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
quaternion::quaternion(const vector3& axis,double angle)
{
	double halfAngle=angle*M_PI/360;
	i=axis.x*sin(halfAngle);
	j=axis.y*sin(halfAngle);
	k=axis.z*sin(halfAngle);
	w=cos(halfAngle);
}
quaternion quaternion::eulerRotationRadian(double x,double y,double z)
{
	x/=2;
	y/=2;
	z/=2;
	double i=sin(x)*cos(y)*cos(z)-cos(x)*sin(y)*sin(z);
	double j=cos(x)*sin(y)*cos(z)+sin(x)*cos(y)*sin(z);
	double k=cos(x)*cos(y)*sin(z)-sin(x)*sin(y)*cos(z);
	double w=cos(x)*cos(y)*cos(z)+sin(x)*sin(y)*sin(z);
	return quaternion(i,j,k,w);
}
quaternion quaternion::naturalLog(const quaternion& value)
{
	return quaternion(value.i/value.magnitude()*acos(value.w),
					  value.j/value.magnitude()*acos(value.w),
					  value.k/value.magnitude()*acos(value.w),
					  log(value.magnitude()));
}
quaternion quaternion::exponential(const quaternion& value)
{
	double vectorPartMagnitude=vector3(value.i,value.j,value.k).magnitude();
	double eToTheW=exp(value.w);
	return quaternion(eToTheW*value.i/value.magnitude()*sin(vectorPartMagnitude),
					  eToTheW*value.j/value.magnitude()*sin(vectorPartMagnitude),
					  eToTheW*value.k/value.magnitude()*sin(vectorPartMagnitude),
					  eToTheW*cos(vectorPartMagnitude));
}

