#define BT_EULER_DEFAULT_ZYX
#include "../include/Transfrom.h"
#include "../include/Camera.h"

void Transfrom::setPosition(lm::vec3 pos)
{
	position = pos;
	Matrix = calcMatrix();
}

void Transfrom::setScale(lm::vec3 scl)
{
	scale = scl;
	Matrix = calcMatrix();
}

void Transfrom::setRotation(lm::vec3 rot)
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

lm::vec3 Transfrom::getPosition()
{
	return position;
}

lm::vec3 Transfrom::getScale()
{
	return scale;
}

lm::vec3 Transfrom::getRotation()
{
	return rotation;
}

void Transfrom::translate(lm::vec3 trans)
{
	position += trans;
	Matrix = calcMatrix();
}

void Transfrom::addScale(lm::vec3 scl)
{
	scale += scl;
	Matrix = calcMatrix();
}

void Transfrom::addRotation(lm::vec3 rot)
{
	rotation += rot;
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

void Transfrom::addPosition(lm::vec3 pos)
{
	position += pos;
	Matrix = calcMatrix();
}

lm::mat4 Transfrom::calcMatrix()
{
	return lm::mat4::createTransformMatrix(rotation, position, scale);
}