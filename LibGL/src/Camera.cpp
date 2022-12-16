#include "../include/Camera.h"
#include "../include/Singleton.h"

void Camera::Start(GameObject* gameObject)
{
	/*IDK Man he doesn't want to compile*/
	std::cout << gameObject << " start\n";
}

Camera::Camera(GameObject* obj)
{
	name = "Camera";
	this->obj = obj;
}

void Camera::Update(GameObject* gameObject, float delta)
{
	CreateViewMatrix();
}

lm::mat4 Camera::CreateViewMatrix()
{
	lm::mat4 tmp;
	this->viewMatrix = tmp.lookAt(obj->worldTransform.GetPosition(), obj->worldTransform.GetPosition() + obj->GetFront(), obj->GetUp());
	return this->viewMatrix;
}

const lm::mat4& Camera::GetViewMatrix() const
{
	return this->viewMatrix;
}

RotateWithMouse::RotateWithMouse(float s, bool editor)
{
	name = "rotateWithMouse";
	sensitivity = s;
	isEditor = editor;
};

void RotateWithMouse::Start(GameObject* gameObject)
{
	std::cout << gameObject << " start\n";
}

void RotateWithMouse::Update(GameObject* gameObject, float delta)
{
	if (!SINGLETON.RMB && isEditor)
		return;

	const auto Ry = static_cast<float>(-SINGLETON.mouseOffSetX * this->sensitivity * SINGLETON.timescale);
	const auto Rz = static_cast<float>(-SINGLETON.mouseOffSetY * this->sensitivity * SINGLETON.timescale);

	gameObject->localTransform.AddRotation(lm::vec3(0, Ry, Rz));

	if (gameObject->localTransform.GetRotation().Z() > 80.f)
	{
		gameObject->localTransform.SetRotation(lm::vec3(gameObject->localTransform.GetRotation().X(),
			gameObject->localTransform.GetRotation().Y(), 80.f));
	}

	else if (gameObject->localTransform.GetRotation().Z() < -80.f)
	{
		gameObject->localTransform.SetRotation(lm::vec3(gameObject->localTransform.GetRotation().X(),
			gameObject->localTransform.GetRotation().Y(), -80.f));
	}
};

FreeMovement::FreeMovement(const float s)
{
	name = "freeMovement";
	speed = s;
}

void FreeMovement::Start(GameObject* gameObject)
{
	Component::Start(gameObject);
}

void FreeMovement::Update(GameObject* gameObject, float delta)
{
	if (SINGLETON.W)
		gameObject->localTransform.Translate(gameObject->GetFront() * SINGLETON.delta * this->speed);

	if (SINGLETON.S)
		gameObject->localTransform.Translate(-gameObject->GetFront() * SINGLETON.delta * this->speed);

	if (SINGLETON.A)
		gameObject->localTransform.Translate(-gameObject->GetRight() * SINGLETON.delta * this->speed);

	if (SINGLETON.D)
		gameObject->localTransform.Translate(gameObject->GetRight() * SINGLETON.delta * this->speed);
}