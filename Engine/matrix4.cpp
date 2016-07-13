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
Matrix4::Matrix4(const Quaternion& rotation)
{
	members[0][0]=1-2*rotation.j*rotation.j-2*rotation.k*rotation.k;
	members[0][1]=2*(rotation.i*rotation.j-rotation.k*rotation.w);
	members[0][2]=2*(rotation.i*rotation.k+rotation.j*rotation.w);
	members[0][3]=0;
	members[1][0]=2*(rotation.i*rotation.j+rotation.k*rotation.w);
	members[1][1]=1-2*rotation.j*rotation.j-2*rotation.k*rotation.k;
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
	//TODO: remove assignments which algorithm will never branch on
	//TODO: simplify

	double utm[4][4]{};
	auto utmView = gsl::span<double, 4, 4>(utm);
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			utmView[i][j]=members[i][j];
		}
	}
	
	double r1 = 1;
	double r2 = 1;
	double r3 = 1;
	double sign=1;

	if (!(utmView[1][0]==0&&utmView[2][0]==0&&utmView[3][0]==0))
	{
		if (utmView[0][0]==0)
		{
			if (utmView[1][0]!=0)
			{
				for (int i=0; i<4; i++)
				{
					double temp=utmView[0][i];
					utmView[0][i]=utmView[1][i];
					utmView[1][i]=temp;
				}
				sign*=-1;
			}
			else if (utmView[2][0]!=0)
			{
				for (int i=0; i<4; i++)
				{
					double temp=utmView[0][i];
					utmView[0][i]=utmView[2][i];
					utmView[2][i]=temp;
				}
				sign*=-1;
			}
			else //utm[3][0] != 0
			{
				for (int i=0; i<4; i++)
				{
					double temp=utmView[0][i];
					utmView[0][i]=utmView[3][i];
					utmView[3][i]=temp;
				}
				sign*=-1;
			}
		}
		r1=utmView[1][0];
		r2=utmView[2][0];
		r3=utmView[3][0];
		utmView[1][0]-=r1*utmView[0][0]/utmView[0][0];
		utmView[1][1]-=r1*utmView[0][1]/utmView[0][0];
		utmView[1][2]-=r1*utmView[0][2]/utmView[0][0];
		utmView[1][3]-=r1*utmView[0][3]/utmView[0][0];

		utmView[2][0]-=r2*utmView[0][0]/utmView[0][0];
		utmView[2][1]-=r2*utmView[0][1]/utmView[0][0];
		utmView[2][2]-=r2*utmView[0][2]/utmView[0][0];
		utmView[2][3]-=r2*utmView[0][3]/utmView[0][0];

		utmView[3][0]-=r3*utmView[0][0]/utmView[0][0];
		utmView[3][1]-=r3*utmView[0][1]/utmView[0][0];
		utmView[3][2]-=r3*utmView[0][2]/utmView[0][0];
		utmView[3][3]-=r3*utmView[0][3]/utmView[0][0];
	}

	if (!(utmView[2][1]==0&&utmView[3][1]==0))
	{
		if (utmView[1][1]==0)
		{
			if (utmView[2][1]!=0)
			{
				for (int i=0; i<4; i++)
				{
					double temp=utmView[1][i];
					utmView[1][i]=utmView[2][i];
					utmView[2][i]=temp;
				}
				sign*=-1;
			}
			else //utm[3][1]!=0
			{
				for (int i=0; i<4; i++)
				{
					double temp=utmView[1][i];
					utmView[1][i]=utmView[3][i];
					utmView[3][i]=temp;
				}
				sign*=-1;
			}
		}
		r2=utmView[2][1];
		r3=utmView[3][1];

		utmView[2][0]-=r2*utmView[1][0]/utmView[1][1];
		utmView[2][1]-=r2*utmView[1][1]/utmView[1][1];
		utmView[2][2]-=r2*utmView[1][2]/utmView[1][1];
		utmView[2][3]-=r2*utmView[1][3]/utmView[1][1];

		utmView[3][0]-=r3*utmView[1][0]/utmView[1][1];
		utmView[3][1]-=r3*utmView[1][1]/utmView[1][1];
		utmView[3][2]-=r3*utmView[1][2]/utmView[1][1];
		utmView[3][3]-=r3*utmView[1][3]/utmView[1][1];
	}

	if (utmView[3][2]!=0)
	{
		if (utmView[2][2]==0)
		{
			for (int i=0; i<4; i++)
			{
				double temp=utmView[2][i];
				utmView[2][i]=utmView[3][i];
				utmView[3][i]=temp;
			}
			sign*=-1;
		}
		r3=utmView[3][2];

		utmView[3][0]-=r3*utmView[2][0]/utmView[2][2];
		utmView[3][1]-=r3*utmView[2][1]/utmView[2][2];
		utmView[3][2]-=r3*utmView[2][2]/utmView[2][2];
		utmView[3][3]-=r3*utmView[2][3]/utmView[2][2];
	}

	return sign*utmView[0][0]*utmView[1][1]*utmView[2][2]*utmView[3][3];
}

//calculates inverse by appling
//elementary row operations to
//an augmented matrix
Matrix4 Matrix4::Inverse() const
{
	//TODO: remove assignments which algorithm will never branch on
	//TODO: simplify

	double augMat[4][4]{};
	auto augMatView = gsl::span<double, 4, 4>(augMat);
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			augMatView[i][j]=members[i][j];
			augMatView[i][j+4]=i==j ? 1 : 0;
		}
	}
	double r0 = 1;
	double r1 = 1;
	double r2 = 1;
	double r3 = 1;
	double scale = 1;
	if (augMatView[0][0]==0 && augMatView[1][0]==0 && augMatView[2][0]==0 && augMatView[3][0] == 0)
		throw std::invalid_argument(UNINVERTIBLE_EXCEPTION_TEXT);
	else if (augMatView[0][0] == 0)
	{
		if (augMatView[1][0] != 0)
		{
			for (int i=0; i<8; i++)
			{
				double temp=augMatView[0][i];
				augMatView[0][i]=augMatView[1][i];
				augMatView[1][i]=temp;
			}
		}
		else if (augMatView[2][0] != 0)
		{
			for (int i=0; i<8; i++)
			{
				double temp=augMatView[0][i];
				augMatView[0][i]=augMatView[2][i];
				augMatView[2][i]=temp;
			}
		}
		else //augmat[3][0] != 0
		{
			for (int i=0; i<8; i++)
			{
				double temp=augMatView[0][i];
				augMatView[0][i]=augMatView[3][i];
				augMatView[3][i]=temp;
			}
		}
	}
	r1=augMatView[1][0];
	r2=augMatView[2][0];
	r3=augMatView[3][0];
	scale=augMatView[0][0];
	for (int i=0; i < 8; i++)
	{
		augMatView[0][i]/=scale;
	}
	for (int i=0; i < 8; i++)
	{
		augMatView[1][i]-=r1*augMatView[0][i];
		augMatView[2][i]-=r2*augMatView[0][i];
		augMatView[3][i]-=r3*augMatView[0][i];
	}
	if (augMatView[1][1]==0 && augMatView[2][1]==0 && augMatView[3][1] == 0)
		throw std::invalid_argument(UNINVERTIBLE_EXCEPTION_TEXT);
	else if (augMatView[1][1] == 0)
	{
		if (augMatView[2][1] != 0)
		{
			for (int i=0; i<8; i++)
			{
				double temp=augMatView[1][i];
				augMatView[1][i]=augMatView[2][i];
				augMatView[2][i]=temp;
			}
		}
		else //augmat[3][1] != 0
		{
			for (int i=0; i<8; i++)
			{
				double temp=augMatView[1][i];
				augMatView[1][i]=augMatView[3][i];
				augMatView[3][i]=temp;
			}
		}
	}
	r0=augMatView[0][1];
	r2=augMatView[2][1];
	r3=augMatView[3][1];
	scale=augMatView[1][1];
	for (int i=0; i < 8; i++)
	{
		augMatView[1][i]/=scale;
	}

	for (int i=0; i < 8; i++)
	{
		augMatView[0][i]-=r0*augMatView[1][i];
		augMatView[2][i]-=r2*augMatView[1][i];
		augMatView[3][i]-=r3*augMatView[1][i];
	}
	if (augMatView[2][2]==0 && augMatView[3][2] == 0)
		throw std::invalid_argument(UNINVERTIBLE_EXCEPTION_TEXT);
	else if (augMatView[2][2] == 0)
	{
		// augmat[3][2] != 0
		for (int i=0; i<8; i++)
		{
			double temp=augMatView[2][i];
			augMatView[2][i]=augMatView[3][i];
			augMatView[3][i]=temp;
		}
	}
	r0=augMatView[0][2];
	r1=augMatView[1][2];
	r3=augMatView[3][2];
	scale=augMatView[2][2];
	for (int i=0; i < 8; i++)
	{
		augMatView[2][i]/=scale;
	}
	for (int i=0; i < 8; i++)
	{
		augMatView[0][i]-=r0*augMatView[2][i];
		augMatView[1][i]-=r1*augMatView[2][i];
		augMatView[3][i]-=r3*augMatView[2][i];
	}
	if (augMatView[3][3] == 0)
		throw std::invalid_argument(UNINVERTIBLE_EXCEPTION_TEXT);
	r0=augMatView[0][3];
	r1=augMatView[1][3];
	r2=augMatView[2][3];
	scale=augMatView[3][3];
	for (int i=0; i < 8; i++)
	{
		augMatView[3][i]/=scale;
	}
	for (int i=0; i < 8; i++)
	{
		augMatView[0][i]-=r0*augMatView[3][i];
		augMatView[1][i]-=r1*augMatView[3][i];
		augMatView[2][i]-=r2*augMatView[3][i];
	}

	double result[4][4]{};
	for (int i=0; i < 4; i++)
	{
		for (int j=0; j < 4; j++)
		{
			result[i][j]=augMatView[i][j+4];
		}
	}

	return Matrix4(result);
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
			output[i * 4 + j] = members[i][j];
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
