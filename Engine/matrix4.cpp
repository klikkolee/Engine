#include "matrix4.h"
#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <span.h>
const std::string Matrix4::UNINVERTIBLE_EXCEPTION_TEXT="matrix is not invertible";
Matrix4::Matrix4() : members{ {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} } {}
Matrix4::Matrix4(Quaternion rotation)
{
	members[0][0]=1-2*rotation.j*rotation.j-2*rotation.k*rotation.k;
	members[0][1]=2*(rotation.i*rotation.j-rotation.k*rotation.w);
	members[0][2]=2*(rotation.i*rotation.k+rotation.j*rotation.w);
	members[0][3]=0;
	members[1][0]=2*(rotation.i*rotation.j+rotation.k*rotation.w);
	members[1][1]=1-2*rotation.i*rotation.i-2*rotation.k*rotation.k;
	members[1][2]=2*(rotation.j*rotation.k-rotation.i*rotation.w);
	members[1][3]=0;
	members[2][0]=2*(rotation.i*rotation.k-rotation.j*rotation.w);
	members[2][1]=2*(rotation.i*rotation.w+rotation.j*rotation.k);
	members[2][2]=1-2*rotation.i*rotation.i-2*rotation.j*rotation.j;
	members[2][3]=0;
	members[3][0]=0;
	members[3][1]=0;
	members[3][2]=0;
	members[3][3]=1;
}

//uses elementary row operations to create
//an upper triangular matrix with identical determinant
double Matrix4::Determinant() const
{
	//based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
	return 
		members[0][3] * members[1][2] * members[2][1] * members[3][0] - members[0][2] * members[1][3] * members[2][1] * members[3][0] - members[0][3] * members[1][1] * members[2][2] * members[3][0] + members[0][1] * members[1][3] * members[2][2] * members[3][0] +
		members[0][2] * members[1][1] * members[2][3] * members[3][0] - members[0][1] * members[1][2] * members[2][3] * members[3][0] - members[0][3] * members[1][2] * members[2][0] * members[3][1] + members[0][2] * members[1][3] * members[2][0] * members[3][1] +
		members[0][3] * members[1][0] * members[2][2] * members[3][1] - members[0][0] * members[1][3] * members[2][2] * members[3][1] - members[0][2] * members[1][0] * members[2][3] * members[3][1] + members[0][0] * members[1][2] * members[2][3] * members[3][1] +
		members[0][3] * members[1][1] * members[2][0] * members[3][2] - members[0][1] * members[1][3] * members[2][0] * members[3][2] - members[0][3] * members[1][0] * members[2][1] * members[3][2] + members[0][0] * members[1][3] * members[2][1] * members[3][2] +
		members[0][1] * members[1][0] * members[2][3] * members[3][2] - members[0][0] * members[1][1] * members[2][3] * members[3][2] - members[0][2] * members[1][1] * members[2][0] * members[3][3] + members[0][1] * members[1][2] * members[2][0] * members[3][3] +
		members[0][2] * members[1][0] * members[2][1] * members[3][3] - members[0][0] * members[1][2] * members[2][1] * members[3][3] - members[0][1] * members[1][0] * members[2][2] * members[3][3] + members[0][0] * members[1][1] * members[2][2] * members[3][3];
}

Matrix4 Matrix4::Inverse() const
{
	//based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
	double invMembers[4][4];
	invMembers[0][0] = members[1][2] * members[2][3] * members[3][1] - members[1][3] * members[2][2] * members[3][1] + members[1][3] * members[2][1] * members[3][2] - members[1][1] * members[2][3] * members[3][2] - members[1][2] * members[2][1] * members[3][3] + members[1][1] * members[2][2] * members[3][3];
	invMembers[0][1] = members[0][3] * members[2][2] * members[3][1] - members[0][2] * members[2][3] * members[3][1] - members[0][3] * members[2][1] * members[3][2] + members[0][1] * members[2][3] * members[3][2] + members[0][2] * members[2][1] * members[3][3] - members[0][1] * members[2][2] * members[3][3];
	invMembers[0][2] = members[0][2] * members[1][3] * members[3][1] - members[0][3] * members[1][2] * members[3][1] + members[0][3] * members[1][1] * members[3][2] - members[0][1] * members[1][3] * members[3][2] - members[0][2] * members[1][1] * members[3][3] + members[0][1] * members[1][2] * members[3][3];
	invMembers[0][3] = members[0][3] * members[1][2] * members[2][1] - members[0][2] * members[1][3] * members[2][1] - members[0][3] * members[1][1] * members[2][2] + members[0][1] * members[1][3] * members[2][2] + members[0][2] * members[1][1] * members[2][3] - members[0][1] * members[1][2] * members[2][3];

	invMembers[1][0] = members[1][3] * members[2][2] * members[3][0] - members[1][2] * members[2][3] * members[3][0] - members[1][3] * members[2][0] * members[3][2] + members[1][0] * members[2][3] * members[3][2] + members[1][2] * members[2][0] * members[3][3] - members[1][0] * members[2][2] * members[3][3];
	invMembers[1][1] = members[0][2] * members[2][3] * members[3][0] - members[0][3] * members[2][2] * members[3][0] + members[0][3] * members[2][0] * members[3][2] - members[0][0] * members[2][3] * members[3][2] - members[0][2] * members[2][0] * members[3][3] + members[0][0] * members[2][2] * members[3][3];
	invMembers[1][2] = members[0][3] * members[1][2] * members[3][0] - members[0][2] * members[1][3] * members[3][0] - members[0][3] * members[1][0] * members[3][2] + members[0][0] * members[1][3] * members[3][2] + members[0][2] * members[1][0] * members[3][3] - members[0][0] * members[1][2] * members[3][3];
	invMembers[1][3] = members[0][2] * members[1][3] * members[2][0] - members[0][3] * members[1][2] * members[2][0] + members[0][3] * members[1][0] * members[2][2] - members[0][0] * members[1][3] * members[2][2] - members[0][2] * members[1][0] * members[2][3] + members[0][0] * members[1][2] * members[2][3];

	invMembers[2][0] = members[1][1] * members[2][3] * members[3][0] - members[1][3] * members[2][1] * members[3][0] + members[1][3] * members[2][0] * members[3][1] - members[1][0] * members[2][3] * members[3][1] - members[1][1] * members[2][0] * members[3][3] + members[1][0] * members[2][1] * members[3][3];
	invMembers[2][1] = members[0][3] * members[2][1] * members[3][0] - members[0][1] * members[2][3] * members[3][0] - members[0][3] * members[2][0] * members[3][1] + members[0][0] * members[2][3] * members[3][1] + members[0][1] * members[2][0] * members[3][3] - members[0][0] * members[2][1] * members[3][3];
	invMembers[2][2] = members[0][1] * members[1][3] * members[3][0] - members[0][3] * members[1][1] * members[3][0] + members[0][3] * members[1][0] * members[3][1] - members[0][0] * members[1][3] * members[3][1] - members[0][1] * members[1][0] * members[3][3] + members[0][0] * members[1][1] * members[3][3];
	invMembers[2][3] = members[0][3] * members[1][1] * members[2][0] - members[0][1] * members[1][3] * members[2][0] - members[0][3] * members[1][0] * members[2][1] + members[0][0] * members[1][3] * members[2][1] + members[0][1] * members[1][0] * members[2][3] - members[0][0] * members[1][1] * members[2][3];

	invMembers[3][0] = members[1][2] * members[2][1] * members[3][0] - members[1][1] * members[2][2] * members[3][0] - members[1][2] * members[2][0] * members[3][1] + members[1][0] * members[2][2] * members[3][1] + members[1][1] * members[2][0] * members[3][2] - members[1][0] * members[2][1] * members[3][2];
	invMembers[3][1] = members[0][1] * members[2][2] * members[3][0] - members[0][2] * members[2][1] * members[3][0] + members[0][2] * members[2][0] * members[3][1] - members[0][0] * members[2][2] * members[3][1] - members[0][1] * members[2][0] * members[3][2] + members[0][0] * members[2][1] * members[3][2];
	invMembers[3][2] = members[0][2] * members[1][1] * members[3][0] - members[0][1] * members[1][2] * members[3][0] - members[0][2] * members[1][0] * members[3][1] + members[0][0] * members[1][2] * members[3][1] + members[0][1] * members[1][0] * members[3][2] - members[0][0] * members[1][1] * members[3][2];
	invMembers[3][3] = members[0][1] * members[1][2] * members[2][0] - members[0][2] * members[1][1] * members[2][0] + members[0][2] * members[1][0] * members[2][1] - members[0][0] * members[1][2] * members[2][1] - members[0][1] * members[1][0] * members[2][2] + members[0][0] * members[1][1] * members[2][2];
	Matrix4 result{ invMembers };
	result /= Determinant();
	return result;
}

Matrix4 Matrix4::Transpose() const
{
	Matrix4 result=Matrix4();
	for (int i=0; i < 4; i++)
	{
		for (int j=0; j < 4; j++)
		{
			result.members[i][j]=members[j][i];
		}
	}
	return result;
}

void Matrix4::AsFloatBuffer(float(&output)[16])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			output[i * 4 + j] = float(members[i][j]);
		}
	}
}

std::string Matrix4::DebugString() const
{
	std::string result;
	for (int i=0; i<4; i++)
	{
		result.append("|");
		result.append(std::to_string(members[i][0]));
		for (int j=1; j<4; j++)
		{
			result.append(",");
			result.append(std::to_string(members[i][j]));
		}
		result.append("|\r\n");
	}
	return result;
}

double& Matrix4::operator()(int row, int column)
{
	return members[row-1][column-1];
}

Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
	Matrix4 lhs=Matrix4(*this);
	if (&rhs==this)
		*this*=Matrix4(rhs);
	else
	{
		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				members[i][j]=lhs.members[i][0]*rhs.members[0][j]+lhs.members[i][1]*rhs.members[1][j]+lhs.members[i][2]*rhs.members[2][j]+lhs.members[i][3]*rhs.members[3][j];
			}
		}
	}
	return *this;
}
Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
	for (int i=0; i < 4; i++)
	{
		for (int j=0; j < 4; j++)
		{
			members[i][j]+=rhs.members[i][j];
		}
	}
	return *this;
}
Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
	for (int i=0; i < 4; i++)
	{
		for (int j=0; j < 4; j++)
		{
			members[i][j]-=rhs.members[i][j];
		}
	}
	return *this;
}

Matrix4& Matrix4::operator*=(double scalar)
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			members[i][j]*=scalar;
		}
	}
	return *this;
}
Matrix4& Matrix4::operator/=(double scalar)
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			members[i][j]/=scalar;
		}
	}
	return *this;
}

const Vector3 Matrix4::operator*(const Vector3& rhs) const
{
	return Vector3(members[0][0]*rhs.x+members[0][1]*rhs.y+members[0][2]*rhs.z+members[0][3],members[1][0]*rhs.x+members[1][1]*rhs.y+members[1][2]*rhs.z+members[1][3],members[2][0]*rhs.x+members[2][1]*rhs.y+members[2][2]*rhs.z+members[2][3]);
}
const Vector4 Matrix4::operator*(const Vector4& rhs) const
{
	return Vector4(members[0][0]*rhs.x+members[0][1]*rhs.y+members[0][2]*rhs.z+members[0][3]*rhs.w,members[1][0]*rhs.x+members[1][1]*rhs.y+members[1][2]*rhs.z+members[1][3]*rhs.w,members[2][0]*rhs.x+members[2][1]*rhs.y+members[2][2]*rhs.z+members[2][3]*rhs.w,members[3][0]*rhs.x+members[3][1]*rhs.y+members[3][2]*rhs.z+members[3][3]*rhs.w);
}

Matrix4::Matrix4(const std::initializer_list<std::initializer_list<double>>& values)
{
	if (values.size() != 4 || values.begin()->size() != 4)
		throw std::invalid_argument("initializer list constructor for matrix given wrong dimensions");
	int rowIndex = 0;
	auto row = values.begin();
	for (; rowIndex < 4; ++rowIndex, ++row)
	{
		std::copy(row->begin(), row->begin() + 4, members[rowIndex]);
	}
}

Matrix4 Matrix4::EulerRotationRadian(double x, double y, double z)
{
	Matrix4 xRot = Matrix4({ { 1, 0, 0, 0 },            { 0, cos(x), -sin(x), 0 }, { 0, sin(x), cos(x), 0 },  { 0, 0, 0, 1 } });
	Matrix4 yRot = Matrix4({ { cos(y), 0, sin(y), 0 },  { 0, 1, 0, 0 },            { -sin(y), 0, cos(y), 0 }, { 0, 0, 0, 1 } });
	Matrix4 zRot = Matrix4({ { cos(z), -sin(z), 0, 0 }, { sin(z), cos(z), 0, 0 },  { 0, 0, 1, 0 },            { 0, 0, 0, 1 } });
	return xRot*yRot*zRot;
}

Matrix4 Matrix4::TranslationMatrix(Vector3 translation)
{
	return TranslationMatrix(translation.x,translation.y,translation.z);
}
Matrix4 Matrix4::ScaleMatrix(Vector3 scale)
{
	return ScaleMatrix(scale.x,scale.y,scale.z);
}

Matrix4 Matrix4::ProjectionMatrix(double fov, double nearClip, double farClip, double aspectRatio)
{
	double f = 1 / tan(fov/2*(M_PI/180));
	return Matrix4({ {f/aspectRatio,0,0,0}, {0,f,0,0},{0,0,-(farClip+nearClip)/(nearClip-farClip),(2*nearClip*farClip)/(nearClip-farClip)},{0,0,1,0} });

}

Matrix4 ToXZPlaneAboutZ(Vector3 direction)
{
	if (direction.x == 0 && direction.y == 0)
		return Matrix4::Identity();
	else
	{
		double xyLength = sqrt(direction.x*direction.x + direction.y*direction.y);
		return Matrix4({
			{direction.x / xyLength,direction.y / xyLength,0,0},
			{-direction.y / xyLength,direction.x / xyLength,0,0},
			{0,0,1,0},
			{0,0,0,1} });
	}
}

Matrix4 InXZToZ(Vector3 direction)
{
	if (direction == Vector3(0,0,0))
	{
		return Matrix4::Identity();
	}
	else
	{
		double totalLength = sqrt(direction.x*direction.x + direction.y*direction.y + direction.z*direction.z);
		double xyLength = sqrt(direction.x*direction.x + direction.y*direction.y);
		return Matrix4({
			{direction.z/totalLength,0,-xyLength/totalLength,0},
			{0,1,0,0},
			{xyLength/totalLength,0,direction.z/totalLength,0},
			{0,0,0,1} });
	}
}

Matrix4 Matrix4::RotationAroundAxisRadianMatrix(Vector3 axisDirection, Vector3 axisPoint, double angle)
{
	Vector3::Normalize(axisDirection);
	double u = axisDirection.x;
	double v = axisDirection.y;
	double w = axisDirection.z;
	double a = axisPoint.x;
	double b = axisPoint.y;
	double c = axisPoint.z;
	double cosine = cos(angle);
	double sine = sin(angle);
	return Matrix4({
		{ u*u + (v*v + w*w)*cosine, u*v*(1 - cosine) - w*sine, u*w*(1 - cosine) + v*sine, (a*(v*v + w*w) - u*(b*v + c*w))*(1 - cosine) + (b*w - c*v)*sine},
		{ u*v*(1 - cosine) + w*sine, v*v + (u*u + w*w)*cosine, v*w*(1 - cosine) - u*sine, (b*(u*u + w*w) - v*(a*u + c*w))*(1 - cosine) + (c*u - a*w)*sine},
		{ u*w*(1 - cosine) - v*sine, v*w*(1 - cosine) + u*sine, w*w + (u*u + v*v)*cosine, (c*(u*u + v*v) - w*(a*u + b*v))*(1 - cosine) + (a*v - b*u)*sine},
		{0,0,0,1} });
}

Matrix4 Matrix4::RotationAroundAxisDegreeMatrix(Vector3 axisDirection, Vector3 axisPoint, double angle)
{
	return RotationAroundAxisRadianMatrix(axisDirection, axisPoint, angle*M_PI / 180);
}
