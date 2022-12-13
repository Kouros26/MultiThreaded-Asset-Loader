#pragma once
#include "Transfrom.h"
#include "Mat4/mat4.h"
#include "Vec3/vec3.h"
#include <map>

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

	void updateGraphMat();
	void setName(const std::string& newName);
	std::string getName();
	lm::vec3 getFront();
	lm::vec3 getRight();
	lm::vec3 getUp();
	void addComponent(Component* comp);
	template<typename T>
	T* getComponent(std::string key)
	{
		auto it = components.find(key);
		if (it == components.end())
		{
			return nullptr;
		}

		return static_cast <T*>(it->second);
	}
	void removeComponent(std::string name);
	void setParent(GameObject* p = nullptr);
};

class Component
{
public:

	std::string name = std::string("");

	virtual void Update(GameObject* gameObject, float delta) = 0;

	virtual void Start(GameObject* gameObject) = 0;

	virtual ~Component() = default;
};
