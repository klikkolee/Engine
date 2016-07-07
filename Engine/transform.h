#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H
#include "quaternion.h"
#include "vector3.h"
#include "matrix4.h"
#include <vector>
class Transform final
{
	Transform* parent;
	std::vector<Transform*> children;
	Quaternion rotation;
	Vector3 position;
	Vector3 scale;
public:
	Transform() : parent(nullptr),children(),rotation(),position(),scale() {}
	Transform(Quaternion rotation,Vector3 position,Vector3 scale) : parent(nullptr),children(),rotation(rotation),position(position),scale(scale) {}

	Matrix4 WorldToLocalMatrix();
	Matrix4 LocalToWorldMatrix();

	void Rotate(Quaternion rotation);
	void Rotate(double x,double y,double z) { Rotate(Quaternion::EulerRotation(x,y,z)); }
	void Translate(Vector3 translation) { position+=translation; }
	void Translate(double x,double y,double z) { Translate(Vector3(x,y,z)); }
	void SetParent(Transform& parent);
	Vector3& GetPosition() { return position; }
	Vector3& GetScale() { return scale; }
	Quaternion& GetRotation() { return rotation; }
	Transform& GetParent() { return *parent; }
	Vector3 Forward() { return LocalToWorldMatrix()*Vector3(1,0,0); }
	Vector3 Right() { return LocalToWorldMatrix()*Vector3(0,1,0); }
	Vector3 Up() { return LocalToWorldMatrix()*Vector3(0,0,1); }
};
#endif //!ENGINE_TRANSFORM_H