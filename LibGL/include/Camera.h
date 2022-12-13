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
	void Start(GameObject* gameObject) override { /*IDK Man he doesn't want to compile*/std::cout << gameObject << " start\n"; }
	Camera(GameObject* obj) {
		name = "Camera";
		this->obj = obj;
	};

	void Update(GameObject* gameObject, float delta) override;
	const lm::mat4 createViewMatrix();
	//get view matrix
	const lm::mat4& getViewMatrix() const;
};

class rotateWithMouse : public Component
{
public:
	void Start(GameObject* gameObject) override { /*IDK Man he doesn't want to compile*/std::cout << gameObject << " start\n"; }
	rotateWithMouse(float s, bool editor) {
		name = "rotateWithMouse";
		sensitivity = s;
		isEditor = editor;
	};

	void Update(GameObject* gameObject, float delta) override;

private:
	float sensitivity = 0;
	bool isEditor = false;
};

class freeMovement : public Component {
public:
	void Start(GameObject* gameObject) override { /*IDK Man he doesn't want to compile*/std::cout << gameObject << " start\n"; }
	freeMovement(float s) {
		name = "freeMovement";
		speed = s;
	}

	void Update(GameObject* gameObject, float delta) override;

private:
	float speed = 0;
};
