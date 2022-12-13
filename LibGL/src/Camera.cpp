#include "../include/Camera.h"
#include "../include/Singleton.h"

void Camera::Update(GameObject* gameObject, float delta)
{
	createViewMatrix();
}

const lm::mat4 Camera::createViewMatrix()
{
	lm::mat4 tmp;
	this->viewMatrix = tmp.lookAt(obj->worldTransform.getPosition(), obj->worldTransform.getPosition() + obj->getFront(), obj->getUp());
	return this->viewMatrix;
}

const lm::mat4& Camera::getViewMatrix() const
{
	return this->viewMatrix;
}

void freeMovement::Update(GameObject* gameObject, float delta) {
	if (SINGLETON.W)
		gameObject->localTransform.translate(gameObject->getFront() * SINGLETON.delta * this->speed);

	if (SINGLETON.S)
		gameObject->localTransform.translate(-gameObject->getFront() * SINGLETON.delta * this->speed);

	if (SINGLETON.A)
		gameObject->localTransform.translate(-gameObject->getRight() * SINGLETON.delta * this->speed);

	if (SINGLETON.D)
		gameObject->localTransform.translate(gameObject->getRight() * SINGLETON.delta * this->speed);
}

void rotateWithMouse::Update(GameObject* gameObject, float delta) {
	if (!SINGLETON.RMB && isEditor)
		return;

	float Ry = static_cast<float>(-SINGLETON.mouseOffSetX * this->sensitivity * SINGLETON.timescale);
	float Rz = static_cast<float>(-SINGLETON.mouseOffSetY * this->sensitivity * SINGLETON.timescale);

	gameObject->localTransform.addRotation(lm::vec3(0, Ry, Rz));

	if (gameObject->localTransform.getRotation().Z() > 80.f)
	{
		gameObject->localTransform.setRotation(lm::vec3(gameObject->localTransform.getRotation().X(), gameObject->localTransform.getRotation().Y(), 80.f));
	}
	else if (gameObject->localTransform.getRotation().Z() < -80.f)
	{
		gameObject->localTransform.setRotation(lm::vec3(gameObject->localTransform.getRotation().X(), gameObject->localTransform.getRotation().Y(), -80.f));
	}
};