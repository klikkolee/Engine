#ifndef TRANSFORM_H
#define TRANDFORM_H
#include "quaternion.hpp"
#include "vector3.hpp"
#include "matrix4.hpp"
#include <vector>
class transform final
{
	transform* parent;
	std::vector<transform*> children;
	quaternion rotation;
	vector3 position;
	vector3 scale;
public:
	transform() : rotation(),position(),scale() {}
	transform(quaternion rotation,vector3 position,vector3 scale) : rotation(rotation),position(position),scale(scale) {}

	mat4 worldToLocalMatrix();
	mat4 localToWorldMatrix();

	void rotate(quaternion rotation);
	void rotate(double x,double y,double z) { rotate(quaternion::eulerRotation(x,y,z)); }
	void translate(vector3 translation) { position+=translation; }
	void translate(double x,double y,double z) { translate(vector3(x,y,z)); }
	void setParent(transform& parent);
	vector3& getPosition() { return position; }
	vector3& getScale() { return scale; }
	quaternion& getRotation() { return rotation; }
	transform& getParent() { return *parent; }
	vector3 forward() { return localToWorldMatrix()*vector3(1,0,0); }
	vector3 right() { return localToWorldMatrix()*vector3(0,1,0); }
	vector3 up() { return localToWorldMatrix()*vector3(0,0,1); }
};
#endif