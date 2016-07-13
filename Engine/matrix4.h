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
	double members[4][4]; //row major order
public:
	static const std::string UNINVERTIBLE_EXCEPTION_TEXT;
	enum RotationOrder
	{
		xyz,xzy,yxz,yzx,zxy,zyx
	};
	Matrix4();
	Matrix4(const Quaternion& rotation);
	explicit Matrix4(const double(&members)[4][4]) : members{}
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->members[i][j] = members[i][j];
			}
		}
	}
	explicit Matrix4(const std::initializer_list<std::initializer_list<double>>& values);

	static Matrix4 Zero() { return Matrix4({ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }); }
	static Matrix4 Identity() { return Matrix4({ { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } }); }
	//zyx rotation order
	static Matrix4 EulerRotationRadian(double x, double y, double z);
	//zyx rotation order
	static Matrix4 EulerRotationDegree(double x, double y, double z) { return EulerRotationRadian(x*M_PI/180, y*M_PI/180, z*M_PI/180); }
	inline static Matrix4 TranslationMatrix(double x, double y, double z) { return Matrix4({ { 1,0,0,x },{ 0,1,0,y },{ 0,0,1,z },{ 0,0,0,1 } }); }
	static Matrix4 TranslationMatrix(Vector3 translation);
	static Matrix4 ScaleMatrix(double x, double y, double z) { return Matrix4({ { x,0,0,0 },{ 0,y,0,0 },{ 0,0,z,0 },{ 0,0,0,1}  }); }
	static Matrix4 ScaleMatrix(Vector3 scale);
	static Matrix4 ProjectionMatrix(double fov, double nearClip, double farClip, double aspectRatio);
	static Matrix4 RotationAroundAxisRadianMatrix(Vector3 axisDirection, Vector3 axisPoint, double angle);
	static Matrix4 RotationAroundAxisDegreeMatrix(Vector3 axisDirection, Vector3 axisPoint, double angle);

	double Determinant() const;
	Matrix4 Inverse() const;
	Matrix4 Transpose() const;
	void AsFloatBuffer(float(&output)[16]);

	std::string DebugString() const;

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

	const Vector3 operator*(const Vector3& rhs) const;
	const Vector4 operator*(const Vector4& rhs) const;

	double& operator()(int row,int column);
};

#endif