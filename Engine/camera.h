#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H
#include "vector3.h"
#include "matrix4.h"
#include "component.h"

class Camera : public Component
{
public:
	Vector3 translation;
	double xRot = 0;
	double yRot = 0;
	double zRot = 0;

	Vector3 Forward()
	{
		return Matrix4::EulerRotationRadian(0, yRot, 0)*Matrix4::EulerRotationRadian(xRot, 0, 0)*Vector3(0, 0, 1);
	}
	Vector3 Up()
	{
		return Matrix4::EulerRotationRadian(0, yRot, 0)*Matrix4::EulerRotationRadian(xRot, 0, 0)*Vector3(0, 1, 0);
	}
	Vector3 Right()
	{
		return Matrix4::EulerRotationRadian(0, yRot, zRot)*Vector3(1, 0, 0);
	}
	Camera() : translation() {}
	virtual void Accept(SceneGraphVisitor&) override;
};
#endif // !ENGINE_CAMERA_H