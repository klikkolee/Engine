#include "transform.h"
#include "quaternion.h"
#include "vector3.h"
#include "matrix4.h"
void Transform::Rotate(Quaternion rotation)
{
	this->rotation=rotation*this->rotation;
}
Matrix4 Transform::WorldToLocalMatrix()
{
	if (parent == NULL)
		return Matrix4::TranslationMatrix(position)*Matrix4(rotation)*Matrix4::ScaleMatrix(scale);
	else
		return parent->WorldToLocalMatrix()*Matrix4::TranslationMatrix(position)*Matrix4(rotation)*Matrix4::ScaleMatrix(scale);
}
Matrix4 Transform::LocalToWorldMatrix()
{
	return WorldToLocalMatrix().Inverse();
}
void Transform::SetParent(Transform& parent)
{
	parent.children.push_back(this);
	this->parent=&parent;
}