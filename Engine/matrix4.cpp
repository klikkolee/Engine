#include "matrix4.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "quaternion.hpp"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
const std::string mat4::UNINVERTIBLE_EXCEPTION_TEXT="matrix is not invertible";
mat4::mat4()
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
			members[i][j]=0;
	}
}
mat4::mat4(double(&members)[4][4])
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
			this->members[i][j]=members[i][j];
	}
}
mat4::mat4(std::initializer_list<std::initializer_list<double>> members)
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
			this->members[i][j]=members.begin()[i].begin()[j];
	}
}
mat4::mat4(const quaternion& rotation)
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
double mat4::determinant()
{
	//TODO: remove assignments which algorithm will never branch on
	//TODO: simplify
	double utm[4][4];
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			utm[i][j]=members[i][j];
		}
	}
	double r1;
	double r2;
	double r3;
	double sign=1;

	if (!(utm[1][0]==0&&utm[2][0]==0&&utm[3][0]==0))
	{
		if (utm[0][0]==0)
		{
			if (utm[1][0]!=0)
			{
				for (int i=0; i<4; i++)
				{
					double temp=utm[0][i];
					utm[0][i]=utm[1][i];
					utm[1][i]=temp;
				}
				sign*=-1;
			}
			else if (utm[2][0]!=0)
			{
				for (int i=0; i<4; i++)
				{
					double temp=utm[0][i];
					utm[0][i]=utm[2][i];
					utm[2][i]=temp;
				}
				sign*=-1;
			}
			else //utm[3][0] != 0
			{
				for (int i=0; i<4; i++)
				{
					double temp=utm[0][i];
					utm[0][i]=utm[3][i];
					utm[3][i]=temp;
				}
				sign*=-1;
			}
		}
		r1=utm[1][0];
		r2=utm[2][0];
		r3=utm[3][0];
		utm[1][0]-=r1*utm[0][0]/utm[0][0];
		utm[1][1]-=r1*utm[0][1]/utm[0][0];
		utm[1][2]-=r1*utm[0][2]/utm[0][0];
		utm[1][3]-=r1*utm[0][3]/utm[0][0];

		utm[2][0]-=r2*utm[0][0]/utm[0][0];
		utm[2][1]-=r2*utm[0][1]/utm[0][0];
		utm[2][2]-=r2*utm[0][2]/utm[0][0];
		utm[2][3]-=r2*utm[0][3]/utm[0][0];

		utm[3][0]-=r3*utm[0][0]/utm[0][0];
		utm[3][1]-=r3*utm[0][1]/utm[0][0];
		utm[3][2]-=r3*utm[0][2]/utm[0][0];
		utm[3][3]-=r3*utm[0][3]/utm[0][0];
	}

	if (!(utm[2][1]==0&&utm[3][1]==0))
	{
		if (utm[1][1]==0)
		{
			if (utm[2][1]!=0)
			{
				for (int i=0; i<4; i++)
				{
					double temp=utm[1][i];
					utm[1][i]=utm[2][i];
					utm[2][i]=temp;
				}
				sign*=-1;
			}
			else //utm[3][1]!=0
			{
				for (int i=0; i<4; i++)
				{
					double temp=utm[1][i];
					utm[1][i]=utm[3][i];
					utm[3][i]=temp;
				}
				sign*=-1;
			}
		}
		r2=utm[2][1];
		r3=utm[3][1];

		utm[2][0]-=r2*utm[1][0]/utm[1][1];
		utm[2][1]-=r2*utm[1][1]/utm[1][1];
		utm[2][2]-=r2*utm[1][2]/utm[1][1];
		utm[2][3]-=r2*utm[1][3]/utm[1][1];

		utm[3][0]-=r3*utm[1][0]/utm[1][1];
		utm[3][1]-=r3*utm[1][1]/utm[1][1];
		utm[3][2]-=r3*utm[1][2]/utm[1][1];
		utm[3][3]-=r3*utm[1][3]/utm[1][1];
	}

	if (utm[3][2]!=0)
	{
		if (utm[2][2]==0)
		{
			for (int i=0; i<4; i++)
			{
				double temp=utm[2][i];
				utm[2][i]=utm[3][i];
				utm[3][i]=temp;
			}
			sign*=-1;
		}
		r3=utm[3][2];

		utm[3][0]-=r3*utm[2][0]/utm[2][2];
		utm[3][1]-=r3*utm[2][1]/utm[2][2];
		utm[3][2]-=r3*utm[2][2]/utm[2][2];
		utm[3][3]-=r3*utm[2][3]/utm[2][2];
	}

	return sign*utm[0][0]*utm[1][1]*utm[2][2]*utm[3][3];
}

//calculates inverse by appling
//elementary row operations to
//an augmented matrix
mat4 mat4::inverse() const
{
	//TODO: remove assignments which algorithm will never branch on
	//TODO: simplify
	double augMat[4][8];
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			augMat[i][j]=members[i][j];
			augMat[i][j+4]=i==j ? 1 : 0;
		}
	}
	double r0;
	double r1;
	double r2;
	double r3;
	double scale;
	if (augMat[0][0]==0 && augMat[1][0]==0 && augMat[2][0]==0 && augMat[3][0] == 0)
		throw std::invalid_argument(UNINVERTIBLE_EXCEPTION_TEXT);
	else if (augMat[0][0] == 0)
	{
		if (augMat[1][0] != 0)
		{
			for (int i=0; i<8; i++)
			{
				double temp=augMat[0][i];
				augMat[0][i]=augMat[1][i];
				augMat[1][i]=temp;
			}
		}
		else if (augMat[2][0] != 0)
		{
			for (int i=0; i<8; i++)
			{
				double temp=augMat[0][i];
				augMat[0][i]=augMat[2][i];
				augMat[2][i]=temp;
			}
		}
		else //augmat[3][0] != 0
		{
			for (int i=0; i<8; i++)
			{
				double temp=augMat[0][i];
				augMat[0][i]=augMat[3][i];
				augMat[3][i]=temp;
			}
		}
	}
	r1=augMat[1][0];
	r2=augMat[2][0];
	r3=augMat[3][0];
	scale=augMat[0][0];
	for (int i=0; i < 8; i++)
	{
		augMat[0][i]/=scale;
	}
	for (int i=0; i < 8; i++)
	{
		augMat[1][i]-=r1*augMat[0][i];
		augMat[2][i]-=r2*augMat[0][i];
		augMat[3][i]-=r3*augMat[0][i];
	}
	if (augMat[1][1]==0 && augMat[2][1]==0 && augMat[3][1] == 0)
		throw std::invalid_argument(UNINVERTIBLE_EXCEPTION_TEXT);
	else if (augMat[1][1] == 0)
	{
		if (augMat[2][1] != 0)
		{
			for (int i=0; i<8; i++)
			{
				double temp=augMat[1][i];
				augMat[1][i]=augMat[2][i];
				augMat[2][i]=temp;
			}
		}
		else //augmat[3][1] != 0
		{
			for (int i=0; i<8; i++)
			{
				double temp=augMat[1][i];
				augMat[1][i]=augMat[3][i];
				augMat[3][i]=temp;
			}
		}
	}
	r0=augMat[0][1];
	r2=augMat[2][1];
	r3=augMat[3][1];
	scale=augMat[1][1];
	for (int i=0; i < 8; i++)
	{
		augMat[1][i]/=scale;
	}

	for (int i=0; i < 8; i++)
	{
		augMat[0][i]-=r0*augMat[1][i];
		augMat[2][i]-=r2*augMat[1][i];
		augMat[3][i]-=r3*augMat[1][i];
	}
	if (augMat[2][2]==0 && augMat[3][2] == 0)
		throw std::invalid_argument(UNINVERTIBLE_EXCEPTION_TEXT);
	else if (augMat[2][2] == 0)
	{
		// augmat[3][2] != 0
		for (int i=0; i<8; i++)
		{
			double temp=augMat[2][i];
			augMat[2][i]=augMat[3][i];
			augMat[3][i]=temp;
		}
	}
	r0=augMat[0][2];
	r1=augMat[1][2];
	r3=augMat[3][2];
	scale=augMat[2][2];
	for (int i=0; i < 8; i++)
	{
		augMat[2][i]/=scale;
	}
	for (int i=0; i < 8; i++)
	{
		augMat[0][i]-=r0*augMat[2][i];
		augMat[1][i]-=r1*augMat[2][i];
		augMat[3][i]-=r3*augMat[2][i];
	}
	if (augMat[3][3] == 0)
		throw std::invalid_argument(UNINVERTIBLE_EXCEPTION_TEXT);
	r0=augMat[0][3];
	r1=augMat[1][3];
	r2=augMat[2][3];
	scale=augMat[3][3];
	for (int i=0; i < 8; i++)
	{
		augMat[3][i]/=scale;
	}
	for (int i=0; i < 8; i++)
	{
		augMat[0][i]-=r0*augMat[3][i];
		augMat[1][i]-=r1*augMat[3][i];
		augMat[2][i]-=r2*augMat[3][i];
	}

	double result[4][4];
	for (int i=0; i < 4; i++)
	{
		for (int j=0; j < 4; j++)
		{
			result[i][j]=augMat[i][j+4];
		}
	}

	return mat4(result);
}

mat4 mat4::transpose() const
{
	mat4 result=mat4();
	for (int i=0; i < 4; i++)
	{
		for (int j=0; j < 4; j++)
		{
			result.members[i][j]=members[j][i];
		}
	}
	return result;
}

std::string mat4::debugString()
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

double& mat4::operator()(int row, int column)
{
	return members[row-1][column-1];
}

mat4& mat4::operator*=(const mat4& rhs)
{
	mat4 lhs=mat4(*this);
	if (&rhs==this)
		*this*=mat4(rhs);
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
mat4& mat4::operator+=(const mat4& rhs)
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
mat4& mat4::operator-=(const mat4& rhs)
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

mat4& mat4::operator*=(double scalar)
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
mat4& mat4::operator/=(double scalar)
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

const vector3 mat4::operator*(const vector3& rhs)
{
	return vector3(members[0][0]*rhs.x+members[0][1]*rhs.y+members[0][2]*rhs.z+members[0][3],members[1][0]*rhs.x+members[1][1]*rhs.y+members[1][2]*rhs.z+members[1][3],members[2][0]*rhs.x+members[2][1]*rhs.y+members[2][2]*rhs.z+members[2][3]);
}
const vector4 mat4::operator*(const vector4& rhs)
{
	return vector4(members[0][0]*rhs.x+members[0][1]*rhs.y+members[0][2]*rhs.z+members[0][3]*rhs.w,members[1][0]*rhs.x+members[1][1]*rhs.y+members[1][2]*rhs.z+members[1][3]*rhs.w,members[2][0]*rhs.x+members[2][1]*rhs.y+members[2][2]*rhs.z+members[2][3]*rhs.w,members[3][0]*rhs.x+members[3][1]*rhs.y+members[3][2]*rhs.z+members[3][3]*rhs.w);
}

mat4 mat4::eulerRotationRadian(double x, double y, double z)
{
	mat4 xRot=mat4({ { 1, 0, 0, 0 }, { 0, cos(x), -sin(x), 0 }, { 0, sin(x), cos(x), 0 }, { 0, 0, 0, 1 } });
	mat4 yRot=mat4({ { cos(y), 0, sin(y), 0 }, { 0, 1, 0, 0 }, { -sin(y), 0, cos(y), 0 }, { 0, 0, 0, 1 } });
	mat4 zRot=mat4({ { cos(x), -sin(x), 0, 0 }, { sin(x), cos(x), 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } });
	return xRot*yRot*zRot;
}

mat4 mat4::translationMatrix(vector3 translation)
{
	return translationMatrix(translation.x,translation.y,translation.z);
}
mat4 mat4::scaleMatrix(vector3 scale)
{
	return scaleMatrix(scale.x,scale.y,scale.z);
}