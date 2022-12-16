#define BT_EULER_DEFAULT_ZYX
#include "../include/Transfrom.h"
#include "../include/Camera.h"

void Transfrom::SetPosition(const lm::vec3& pos)
{
	position = pos;
	Matrix = calcMatrix();
}

void Transfrom::SetScale(const lm::vec3& scl)
{
	scale = scl;
	Matrix = calcMatrix();
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
	Matrix = calcMatrix();
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
	Matrix = calcMatrix();
}

void Transfrom::AddScale(const lm::vec3& scl)
{
	scale += scl;
	Matrix = calcMatrix();
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
	Matrix = calcMatrix();
}

void Transfrom::AddPosition(lm::vec3& pos)
{
	position += pos;
	Matrix = calcMatrix();
}

lm::mat4 Transfrom::calcMatrix() const
{
	return lm::mat4::createTransformMatrix(rotation, position, scale);
}