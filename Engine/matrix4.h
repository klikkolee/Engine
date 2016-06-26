#ifndef ENGINE_MATRIX_H
#define ENGINE_MATRIX_H
#define _USE_MATH_DEFINES
#include <initializer_list>
#include <math.h>
#include <string>
#include <array>

class Vector3;
class Vector4;
class Quaternion;
class Matrix4 final
{
	std::array<std::array<double,4>,4> members;
	Matrix4(std::array<std::array<double, 4>, 4>);
public:
	static const std::string UNINVERTIBLE_EXCEPTION_TEXT;
	enum RotationOrder
	{
		xyz,xzy,yxz,yzx,zxy,zyx
	};
	Matrix4();
	explicit Matrix4(const Quaternion& rotation);

	static Matrix4 Zero() { return Matrix4({{ {{ 0, 0, 0, 0 }}, {{ 0, 0, 0, 0 }}, {{ 0, 0, 0, 0 }}, {{ 0, 0, 0, 0 }} }}); }
	static Matrix4 Identity() { return Matrix4({{ {{ 1, 0, 0, 0 }}, {{ 0, 1, 0, 0 }}, {{ 0, 0, 1, 0 }}, {{ 0, 0, 0, 1 }} }}); }
	//zyx rotation order
	static Matrix4 eulerRotationRadian(double x, double y, double z);
	//zyx rotation order
	static Matrix4 eulerRotationDegree(double x, double y, double z) { return eulerRotationRadian(x*M_PI/180, y*M_PI/180, z*M_PI/180); }
	inline static Matrix4 translationMatrix(double x, double y, double z) { return Matrix4({{ {{ 1,0,0,x }},{{ 0,1,0,y }},{{ 0,0,1,z }},{{ 0,0,0,1 }} }}); }
	static Matrix4 translationMatrix(Vector3 translation);
	static Matrix4 scaleMatrix(double x, double y, double z) { return Matrix4({{ {{ x,0,0,0 }},{{ 0,y,0,0 }},{{ 0,0,z,0 }},{{ 0,0,0,1} } }}); }
	static Matrix4 scaleMatrix(Vector3 scale);

	double Determinant();
	Matrix4 Inverse() const;
	Matrix4 Transpose() const;

	std::string DebugString();

	inline const Matrix4 operator*(const Matrix4& other) const { return Matrix4(*this) *= other; }
	inline const Matrix4 operator*(double scalar) const { return Matrix4(*this) *= scalar; }
	inline const Matrix4 operator/(double scalar) const { return Matrix4(*this) /= scalar; }
	inline const Matrix4 operator+(const Matrix4& other) const { return Matrix4(*this) += other; }
	inline const Matrix4 operator-(const Matrix4& other) const { return Matrix4(*this) -= other; }

	Matrix4& operator*=(const Matrix4& other);
	Matrix4& operator*=(double scalar);
	Matrix4& operator/=(double scalar);
	Matrix4& operator+=(const Matrix4& other);
	Matrix4& operator-=(const Matrix4& other);

	const Vector3 operator*(const Vector3& rhs);
	const Vector4 operator*(const Vector4& rhs);

	double& operator()(int row,int column);
};

#endif