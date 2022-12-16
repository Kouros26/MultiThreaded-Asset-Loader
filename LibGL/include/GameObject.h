#pragma once
#include <map>
#include "Transfrom.h"
#include "Mat4/mat4.h"
#include "Vec3/vec3.h"

class Component;

class GameObject
{
public:

	int id;
	Transfrom localTransform;
	Transfrom worldTransform;
	GameObject* parent = nullptr;
	lm::mat4 Matrix;
	std::map<std::string, Component*> components;
	bool isStatic = false;

	std::string name;

	GameObject(std::string name);
	~GameObject();

	void Start();
	void Update();
	void UpdateMatrix();
	void UpdateComponent();
	void UpdateRender();

	void UpdateGraphMat();
	void SetName(const std::string& newName);
	std::string GetName();
	lm::vec3 GetFront();
	lm::vec3 GetRight();
	lm::vec3 GetUp();
	void AddComponent(Component* comp);

	template<typename T>
	T* GetComponent(std::string key)
	{
		auto it = components.find(key);
		if (it == components.end())
		{
			return nullptr;
		}

		return static_cast <T*>(it->second);
	}

	void RemoveComponent(std::string name);
	void SetParent(GameObject* p = nullptr);
};

class Component
{
public:

	std::string name = std::string("");

	virtual void Update(GameObject* gameObject, float delta) = 0;

	virtual void Start(GameObject* gameObject);

	virtual ~Component() = default;
};
