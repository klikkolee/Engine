#include "transform.hpp"
#include "quaternion.hpp"
#include "vector3.hpp"
#include "matrix4.hpp"
void transform::rotate(quaternion rotation)
{
	this->rotation=rotation*this->rotation;
}
mat4 transform::worldToLocalMatrix()
{
	if (parent == NULL)
		return mat4::translationMatrix(position)*mat4(rotation)*mat4::scaleMatrix(scale);
	else
		return parent->worldToLocalMatrix()*mat4::translationMatrix(position)*mat4(rotation)*mat4::scaleMatrix(scale);
}
mat4 transform::localToWorldMatrix()
{
	return worldToLocalMatrix().inverse();
}
void transform::setParent(transform& parent)
{
	parent.children.push_back(this);
	transform* p=&parent;
	this->parent=&parent;
}