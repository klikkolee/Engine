#ifndef ENGINE_VECTOR3_H
#define ENGINE_VECTOR3_H
class Vector4;
class Quaternion;
class Vector3 final
{
public:
	double x,y,z;
	Vector3();
	Vector3(double x, double y, double z);
	Vector3(const Quaternion& other);
	explicit Vector3(const Vector4& other);

	inline const Vector3 operator+(const Vector3& rhs) const { return Vector3(*this)+=rhs; }
	inline const Vector3 operator-(const Vector3& rhs) const { return Vector3(*this)-=rhs; }
	inline const Vector3 operator*(double rhs) const { return Vector3(*this)*=rhs; }
	inline const Vector3 operator/(double rhs) const { return Vector3(*this)/=rhs; }
	inline Vector3& operator+=(const Vector3& rhs)
	{
		x+=rhs.x;
		y+=rhs.y;
		z+=rhs.z;
		return *this;
	}
	inline Vector3& operator-=(const Vector3& rhs)
	{
		x-=rhs.x;
		y-=rhs.y;
		z-=rhs.z;
		return *this;
	}
	inline Vector3& operator*=(double rhs)
	{
		x*=rhs;
		y*=rhs;
		z*=rhs;
		return *this;
	}
	inline Vector3& operator/=(double rhs)
	{
		x/=rhs;
		y/=rhs;
		z/=rhs;
		return *this;
	}

	inline const Vector3 operator-() { return Vector3{ -x,-y,-z }; }

	inline bool operator==(const Vector3& other) { return (x == other.x && y == other.y && z == other.z); }

	//normalized copy
	Vector3 Unit();
	double Magnitude();
	double SquaredMagnitude();

	static inline Vector3 Cross(const Vector3& lhs,const Vector3& rhs) { return Vector3(lhs.y*rhs.z-lhs.z*rhs.y,lhs.z*rhs.x-lhs.x*rhs.z,lhs.x*rhs.y-lhs.y*rhs.x); }
	static inline double Dot(const Vector3& lhs,const Vector3& rhs) { return lhs.x*rhs.x+lhs.y*rhs.y+lhs.z*rhs.z; }
	//permanently normalizes vector
	static inline Vector3& Normalize(Vector3& vector) 
	{
		vector/=vector.Magnitude();
		return vector;
	}

};
#endif //!ENGINE_VECTOR3_H