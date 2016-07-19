#include "transform.h"
#include "quaternion.h"
#include "vector3.h"
#include "matrix4.h"
#include <algorithm>
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
void Transform::SetParent(Transform* parent)
{
	if (this->parent)
	{
		auto thisComponent = std::find_if(this->parent->children.begin(), this->parent->children.end(), [this](const auto& ptr) {return ptr.get() == this; });
		parent->children.push_back(*thisComponent);
		this->parent->children.erase(thisComponent);
	}
	else
	{
		parent->children.push_back(shared_from_this());
	}
		this->parent = parent;
}