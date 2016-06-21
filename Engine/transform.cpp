#include "transform.hpp"
#include "quaternion.hpp"
#include "vector3.hpp"
#include "matrix4.hpp"
void Transform::Rotate(Quaternion rotation)
{
	this->rotation=rotation*this->rotation;
}
Matrix4 Transform::WorldToLocalMatrix()
{
	if (parent == NULL)
		return Matrix4::translationMatrix(position)*Matrix4(rotation)*Matrix4::scaleMatrix(scale);
	else
		return parent->WorldToLocalMatrix()*Matrix4::translationMatrix(position)*Matrix4(rotation)*Matrix4::scaleMatrix(scale);
}
Matrix4 Transform::LocalToWorldMatrix()
{
	return WorldToLocalMatrix().Inverse();
}
void Transform::SetParent(Transform& parent)
{
	parent.children.push_back(this);
	Transform* p=&parent;
	this->parent=&parent;
}