#ifndef VECTOR4_H
#define VECTOR4_H
class vector3;
class vector4 final
{
public:
	double x,y,z,w;
	vector4();
	vector4(const vector4& other)=default;
	vector4(double x,double y,double z,double w);
	vector4(double x,double y,double z) : vector4(x,y,z,1) {}
	vector4(const vector3& other,int w = 1);

	inline const vector4 operator+(const vector4& rhs) const { return vector4(*this)+=rhs; }
	inline const vector4 operator-(const vector4& rhs) const { return vector4(*this)-=rhs; }
	vector4& operator+=(const vector4& rhs);
	vector4& operator-=(const vector4& rhs);

	static double dot(const vector4& lhs,const vector4& rhs);

	
};
#endif