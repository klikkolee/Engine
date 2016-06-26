#ifndef ENGINE_VECTOR2_H
#define ENGINE_VECTOR2_H
class Vector2 final
{
	double x;
	double y;
public:
	Vector2();
	inline Vector2(int x, int y) : x(x), y(y) {}
	inline static double Dot(const Vector2& lhs, const Vector2& rhs);
	inline const Vector2 operator*(double rhs) const { return Vector2(*this) *= rhs; }
	inline const friend Vector2 operator*(double lhs, const Vector2& rhs) { return Vector2(rhs) *= lhs; }
	inline Vector2& operator*=(double rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
};
#endif //!ENGINE_VECTOR2_H

