#pragma once
#include "GameObject.h"
#include "Mat4/Mat4.h"
#include "Vec3/Vec3.h"

class Camera : public Component
{
private:

	lm::Mat4<float> viewMatrix;
	GameObject* obj;

public:

	Camera(GameObject* obj);

	void Start(GameObject* gameObject) override;

	void Update(GameObject* gameObject, float delta) override;
	lm::mat4 CreateViewMatrix();

	[[nodiscard]] const lm::mat4& GetViewMatrix() const;
};

class RotateWithMouse : public Component
{
public:

	RotateWithMouse(float s, bool editor);

	void Start(GameObject* gameObject) override;

	void Update(GameObject* gameObject, float delta) override;

private:

	float sensitivity = 0;
	bool isEditor = false;
};

class FreeMovement : public Component {
public:

	explicit FreeMovement(float s);

	void Start(GameObject* gameObject) override;

	void Update(GameObject* gameObject, float delta) override;

private:
	float speed = 0;
};
