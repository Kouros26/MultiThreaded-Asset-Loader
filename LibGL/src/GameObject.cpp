#include "../include/GameObject.h"
#include "../include/Singleton.h"
#include "../include/Camera.h"
#include "Vec2/Vec2.h"

GameObject::GameObject(std::string name)
{
	this->name = name;
	id = SINGLETON.gmCount;
	SINGLETON.gmCount++;
}

GameObject::~GameObject()
{
	//clear components
	std::map<std::string, Component*>::iterator it;
	std::vector<std::string> keys;
	for (it = components.begin(); it != components.end(); it++)
	{
		keys.push_back(it->first);
	}
	for (int i = 0; i < keys.size(); i++)
	{
		it = components.find(keys[i]);
		if (it != components.end()) {
			delete it->second;
		}
	}
}

void GameObject::Start()
{
	std::map<std::string, Component*>::iterator it;
	std::vector<std::string> keys;
	for (it = components.begin(); it != components.end(); it++)
	{
		keys.push_back(it->first);
	}

	for (auto& key : keys)
	{
		it = components.find(key);
		if (it != components.end()) {
			it->second->Start(this);
		}
	}
}

void GameObject::Update()
{
	UpdateMatrix();
	UpdateComponent();
}

void GameObject::UpdateGraphMat()
{
	Matrix = localTransform.Matrix;

	localTransform.SetPosition(lm::vec3(Matrix[3][0], Matrix[3][1], Matrix[3][2]));
	float Sx = lm::vec3(Matrix[0][0], Matrix[0][1], Matrix[0][2]).length();
	float Sy = lm::vec3(Matrix[1][0], Matrix[1][1], Matrix[1][2]).length();
	float Sz = lm::vec3(Matrix[2][0], Matrix[2][1], Matrix[2][2]).length();
	localTransform.SetScale(lm::vec3(Sx, Sy, Sz));

	float a = Matrix[1][2] / Sy;
	float b = Matrix[2][2] / Sz;
	float Rx = lm::radiansToDegrees(atan2(a, b));
	float Ry = lm::radiansToDegrees(atan2(-Matrix[0][2] / Sx, sqrt(a * a + b * b)));
	float Rz = lm::radiansToDegrees(atan2(Matrix[0][1] / Sx, Matrix[0][0] / Sx));

	localTransform.SetRotation(lm::vec3(Rx, Ry, Rz));
}

void GameObject::UpdateMatrix()
{
	if (isStatic)
	{
		return;
	}

	if (parent != nullptr) {
		Matrix = parent->Matrix * localTransform.Matrix;

		worldTransform.SetPosition(lm::vec3(Matrix[3][0], Matrix[3][1], Matrix[3][2]));
		lm::vec3 pScale = parent->worldTransform.GetScale();
		float Sx = pScale.X() * localTransform.GetScale().X();
		float Sy = pScale.Y() * localTransform.GetScale().Y();
		float Sz = pScale.Z() * localTransform.GetScale().Z();
		worldTransform.SetScale(lm::vec3(Sx, Sy, Sz));

		lm::Mat4 rotationMatrix(
			lm::vec4(Matrix[0][0] / Sx, Matrix[0][1] / Sx, Matrix[0][2] / Sx, 0),
			lm::vec4(Matrix[1][0] / Sy, Matrix[1][1] / Sy, Matrix[1][2] / Sy, 0),
			lm::vec4(Matrix[2][0] / Sz, Matrix[2][1] / Sz, Matrix[2][2] / Sz, 0),
			lm::vec4(0, 0, 0, 1)
		);

		float a = rotationMatrix[1][2];
		float b = rotationMatrix[2][2];
		float Rx = lm::radiansToDegrees(atan2(a, b));
		float Ry = lm::radiansToDegrees(atan2(-rotationMatrix[0][2], sqrt(a * a + b * b)));
		float Rz = lm::radiansToDegrees(atan2(rotationMatrix[0][1], rotationMatrix[0][0]));

		worldTransform.SetRotation(lm::vec3(Rx, Ry, Rz));
	}
	else
	{
		worldTransform = localTransform;
		Matrix = worldTransform.CalcMatrix();
	}
}

void GameObject::UpdateComponent()
{
	std::map<std::string, Component*>::iterator it;
	std::vector<std::string> keys;
	for (it = components.begin(); it != components.end(); it++)
	{
		keys.push_back(it->first);
	}
	for (int i = 0; i < keys.size(); i++)
	{
		it = components.find(keys[i]);
		if (it != components.end()) {
			it->second->Update(this, SINGLETON.delta);
		}
	}
}

void GameObject::SetName(const std::string& newName)
{
	this->name = newName;
}

std::string GameObject::GetName()
{
	return name;
}

void GameObject::UpdateRender()
{
	UpdateMatrix();
	std::map<std::string, Component*>::iterator it;
	std::vector<std::string> keys;
	for (it = components.begin(); it != components.end(); it++)
	{
		keys.push_back(it->first);
	}

	for (auto& key : keys)
	{
		if (key == "Mesh" || key == "dirLight" || key == "pointLight" || key == "spotLight") {
			it = components.find(key);
			if (it != components.end()) {
				it->second->Update(this, SINGLETON.delta);
			}
		}
	}
}

lm::vec3 GameObject::GetFront() //ok
{
	lm::vec3 front;
	front.X() = static_cast<float>(cos(lm::degreesToRadians(-localTransform.GetRotation().Y())) * cos(lm::degreesToRadians(localTransform.GetRotation().Z())));
	front.Y() = static_cast<float>(sin(lm::degreesToRadians(localTransform.GetRotation().Z())));
	front.Z() = static_cast<float>(sin(lm::degreesToRadians(-localTransform.GetRotation().Y())) * cos(lm::degreesToRadians(localTransform.GetRotation().Z())));

	front = front.normalized();
	return front;
}

lm::vec3 GameObject::GetRight()
{
	return (GetFront().crossProduct(lm::vec3(0, 1, 0))).normalized();
}

lm::vec3 GameObject::GetUp()
{
	return (GetRight().crossProduct(GetFront())).normalized();
}

void GameObject::AddComponent(Component* comp) //ok
{
	if (components.find(comp->name) != components.end()) {
		components.find(comp->name)->second = comp;
		return;
	}
	components.insert(std::make_pair(comp->name, comp));
}

void GameObject::RemoveComponent(std::string name) //ok
{
	if (components.find(name) != components.end()) {
		delete components.find(name)->second;
		components.erase(name);
	}
}

void GameObject::SetParent(GameObject* p) //ok
{
	GameObject* next = p;
	while (next != nullptr)
	{
		if (next == this) {
			return;
		}
		next = next->parent;
	}

	if (p == nullptr) {
		if (parent != nullptr) {
			localTransform = worldTransform;
		}
		parent = p;
		return;
	}

	p->UpdateMatrix();
	localTransform.AddRotation(-p->worldTransform.GetRotation());
	localTransform.SetScale(lm::vec3(localTransform.GetScale()[0] / p->worldTransform.GetScale()[0],
											 localTransform.GetScale()[1] / p->worldTransform.GetScale()[1], 
											 localTransform.GetScale()[2] / p->worldTransform.GetScale()[2]));
	localTransform.Translate(-p->worldTransform.GetPosition());

	parent = p;
}

void Component::Start(GameObject* gameObject)
{
	std::cout << gameObject << " start\n";
}