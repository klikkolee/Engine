#include "transform.h"
#include "quaternion.h"
#include "vector3.h"
#include "matrix4.h"
#include "game_object.h"
#include <algorithm>
void Transform::Rotate(Quaternion rotation)
{
	this->rotation=rotation*this->rotation;
}
void Transform::AddChild(GraphNode & child)
{
	children.push_back(child.shared_from_this());
}
Matrix4 Transform::WorldToLocalMatrix()
{
	auto parentPtr = parent.lock();
	if (parentPtr == nullptr)
		return Matrix4::TranslationMatrix(position)*Matrix4(rotation)*Matrix4::ScaleMatrix(scale);
	else 
		return parentPtr->WorldToLocalMatrix()*Matrix4::TranslationMatrix(position)*Matrix4(rotation)*Matrix4::ScaleMatrix(scale);
}
Matrix4 Transform::LocalToWorldMatrix()
{
	return WorldToLocalMatrix().Inverse();
}