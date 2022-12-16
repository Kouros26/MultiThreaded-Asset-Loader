#define BT_EULER_DEFAULT_ZYX
#include "../include/Transfrom.h"
#include "../include/Camera.h"

void Transfrom::SetPosition(const lm::vec3& pos)
{
	position = pos;
	Matrix = CalcMatrix();
}

void Transfrom::SetScale(const lm::vec3& scl)
{
	scale = scl;
	Matrix = CalcMatrix();
}

void Transfrom::SetRotation(const lm::vec3& rot)
{
	rotation = rot;
	while (rotation.X() > 360) {
		rotation.X() -= 360;
	}
	while (rotation.X() < -360) {
		rotation.X() += 360;
	}
	while (rotation.Y() > 360) {
		rotation.Y() -= 360;
	}
	while (rotation.Y() < -360) {
		rotation.Y() += 360;
	}
	while (rotation.Z() > 360) {
		rotation.Z() -= 360;
	}
	while (rotation.Z() < -360) {
		rotation.Z() += 360;
	}
	Matrix = CalcMatrix();
}

lm::vec3 Transfrom::GetPosition()
{
	return position;
}

lm::vec3 Transfrom::GetScale()
{
	return scale;
}

lm::vec3 Transfrom::GetRotation()
{
	return rotation;
}

void Transfrom::Translate(const lm::vec3& trans)
{
	position += trans;
	Matrix = CalcMatrix();
}

void Transfrom::AddScale(const lm::vec3& scl)
{
	scale += scl;
	Matrix = CalcMatrix();
}

void Transfrom::AddRotation(const lm::vec3& rot)
{
	rotation += rot;
	while (rotation.X() > 360) 
	{
		rotation.X() -= 360;
	}
	while (rotation.X() < -360) 
	{
		rotation.X() += 360;
	}
	while (rotation.Y() > 360) 
	{
		rotation.Y() -= 360;
	}
	while (rotation.Y() < -360) 
	{
		rotation.Y() += 360;
	}
	while (rotation.Z() > 360) 
	{
		rotation.Z() -= 360;
	}
	while (rotation.Z() < -360) 
	{
		rotation.Z() += 360;
	}
	Matrix = CalcMatrix();
}

void Transfrom::AddPosition(const lm::vec3& pos)
{
	position += pos;
	Matrix = CalcMatrix();
}

lm::mat4 Transfrom::CalcMatrix() const
{
	return lm::mat4::createTransformMatrix(rotation, position, scale);
}