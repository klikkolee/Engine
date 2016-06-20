#ifndef MATRIX_H
#define MATRIX_H
#define _USE_MATH_DEFINES
#include <initializer_list>
#include <math.h>
#include <string>

class vector3;
class vector4;
class quaternion;
class mat4 final
{
	double members[4][4];
	mat4(double (&members)[4][4]);
public:
	static const std::string UNINVERTIBLE_EXCEPTION_TEXT;
	typedef enum RotationOrder
	{
		xyz,xzy,yxz,yzx,zxy,zyx
	};
	mat4();
	mat4(std::initializer_list<std::initializer_list<double>> members);
	explicit mat4(const quaternion& rotation);

	static mat4 Zero() { return mat4({ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }); }
	static mat4 Identity() { return mat4({ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } }); }
	//zyx rotation order
	static mat4 eulerRotationRadian(double x, double y, double z);
	//zyx rotation order
	static mat4 eulerRotationDegree(double x, double y, double z) { return eulerRotationRadian(x*M_PI/180, y*M_PI/180, z*M_PI/180); }
	inline static mat4 translationMatrix(double x,double y,double z) { return mat4({ { 1,0,0,x },{ 0,1,0,y },{ 0,0,1,z },{ 0,0,0,1 } }); }
	static mat4 translationMatrix(vector3 translation);
	static mat4 scaleMatrix(double x,double y,double z) { return mat4({ { x,0,0,0 },{ 0,y,0,0 },{ 0,0,z,0 },{ 0,0,0,1 } }); }
	static mat4 scaleMatrix(vector3 scale);

	double determinant();
	mat4 inverse() const;
	mat4 transpose() const;

	std::string debugString();

	inline const mat4 operator*(const mat4& other) const { return mat4(*this) *= other; }
	inline const mat4 operator*(double scalar) const { return mat4(*this) *= scalar; }
	inline const mat4 operator/(double scalar) const { return mat4(*this) /= scalar; }
	inline const mat4 operator+(const mat4& other) const { return mat4(*this) += other; }
	inline const mat4 operator-(const mat4& other) const { return mat4(*this) -= other; }

	mat4& operator*=(const mat4& other);
	mat4& operator*=(double scalar);
	mat4& operator/=(double scalar);
	mat4& operator+=(const mat4& other);
	mat4& operator-=(const mat4& other);

	const vector3 operator*(const vector3& rhs);
	const vector4 operator*(const vector4& rhs);

	double& operator()(int row,int column);
};

#endif