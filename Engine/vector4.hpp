#ifndef ENGINE_VECTOR4_H
#define ENGINE_VECTOR4_H
class Vector3;
class Vector4 final
{
public:
	double x,y,z,w;
	Vector4();
	Vector4(const Vector4& other)=default;
	Vector4(double x,double y,double z,double w);
	Vector4(double x,double y,double z) : Vector4(x,y,z,1) {}
	Vector4(const Vector3& other,int w = 1);

	inline const Vector4 operator+(const Vector4& rhs) const { return Vector4(*this)+=rhs; }
	inline const Vector4 operator-(const Vector4& rhs) const { return Vector4(*this)-=rhs; }
	Vector4& operator+=(const Vector4& rhs);
	Vector4& operator-=(const Vector4& rhs);

	static double Dot(const Vector4& lhs,const Vector4& rhs);

	
};
#endif //ENGINE_VECTOR4_H