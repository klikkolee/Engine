#ifndef ENGINE_TRANSFORM_H
#define ENGINE_TRANSFORM_H
#include "quaternion.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include <vector>
#include <memory>
class GameObject;
class Transform final : public std::enable_shared_from_this<Transform>
{
	friend class GameObject;
	Transform* parent;
	GameObject* parentObject;
	std::vector<std::shared_ptr<Transform>> children;
	Quaternion rotation;
	Vector3 position;
	Vector3 scale;
public:
	inline Transform() : parent(nullptr),children(),rotation(),position(),scale(1,1,1) {}
	inline Transform(Quaternion rotation,Vector3 position,Vector3 scale) : parent(nullptr),children(),rotation(rotation),position(position),scale(scale) {}

	Matrix4 WorldToLocalMatrix();
	Matrix4 LocalToWorldMatrix();

	void Rotate(Quaternion rotation);
	inline void Rotate(double x,double y,double z) { Rotate(Quaternion::EulerRotation(x,y,z)); }
	inline void Translate(Vector3 translation) { position+=translation; }
	inline void Translate(double x,double y,double z) { Translate(Vector3(x,y,z)); }
	void SetParent(Transform* parent);
	inline Vector3& GetPosition() { return position; }
	inline Vector3& GetScale() { return scale; }
	inline Quaternion& GetRotation() { return rotation; }
	inline Transform& GetParent() { return *parent; }
	inline Vector3 Forward() { return Vector3(WorldToLocalMatrix()*Vector4(0,0,1,0)); }
	inline Vector3 Right() { return Vector3(WorldToLocalMatrix()*Vector4(1,0,0,0)); }
	inline Vector3 Up() { return Vector3(WorldToLocalMatrix()*Vector4(0,1,0,0)); }
};
#endif //!ENGINE_TRANSFORM_H