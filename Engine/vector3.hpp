#ifndef VECTOR3_H
#define VECTOR3_H
class vector4;
class vector3 final
{
public:
	double x,y,z;
	vector3();
	vector3(const vector3& other)=default;
	vector3(double x, double y, double z);
	explicit vector3(const vector4& other);

	inline const vector3 operator+(const vector3& rhs) const { return vector3(*this)+=rhs; }
	inline const vector3 operator-(const vector3& rhs) const { return vector3(*this)-=rhs; }
	inline const vector3 operator*(double rhs) const { return vector3(*this)*=rhs; }
	inline const vector3 operator/(double rhs) const { return vector3(*this)/=rhs; }
	inline vector3& vector3::operator+=(const vector3& rhs)
	{
		x+=rhs.x;
		y+=rhs.y;
		z+=rhs.z;
		return *this;
	}
	inline vector3& vector3::operator-=(const vector3& rhs)
	{
		x-=rhs.x;
		y-=rhs.y;
		z-=rhs.z;
		return *this;
	}
	inline vector3& operator*=(double rhs)
	{
		x*=rhs;
		y*=rhs;
		z*=rhs;
		return *this;
	}
	inline vector3& operator/=(double rhs)
	{
		x/=rhs;
		y/=rhs;
		z/=rhs;
		return *this;
	}

	//normalized copy
	vector3 unit();
	double magnitude();
	double squaredMagnitude();

	static inline vector3 vector3::cross(const vector3& lhs,const vector3& rhs) { return vector3(lhs.y*rhs.z-lhs.z*rhs.y,lhs.z*rhs.x-lhs.x*rhs.z,lhs.x*rhs.y-lhs.y*rhs.x); }
	static inline double vector3::dot(const vector3& lhs,const vector3& rhs) { return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z; }
	//permanently normalizes vector
	static inline vector3& normalize(vector3& vector) 
	{
		vector/=vector.magnitude();
		return vector;
	}

};
#endif