#pragma once
#include "Camera.h"
#include "Shader.h"
#include "Vec4/Vec4.h"
#include "GameObject.h"

class Light : public GameObject
{
public:
	Light(float diffuse, float ambient, float specular, lm::vec3 lightColor);

	float diffuse;
	float ambient;
	float specular;

	lm::vec3 lightColor;

	virtual void SendToShader(Resources::Shader* shader, int i) = 0;
};

class PointLight : public Light
{
public:
	float constant;
	float linear;
	float quadratic;

	PointLight(lm::vec3 lightColor, float diff, float amb, float spec, float constant = 1.f, float linear = 0.045f, float quadratic = 0.0075f, std::string name = "");

	void SendToShader(Resources::Shader* shader, int i) override;
};

class DirectionLight : public Light
{
public:
	DirectionLight(lm::vec3 lightColor, float diff, float amb, float spec, std::string name = "");

	void SendToShader(Resources::Shader* shader, int i) override;
};

class SpotLight : public Light
{
public:
	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;

	SpotLight(lm::vec3 lightColor, float diff, float amb, float spec, float constant = 1.f, float linear = 0.045f, float quadratic = 0.0075f, float cutOff = 12.5f, float outerCutOff = 15.0f, std::string name = "");

	void SendToShader(Resources::Shader* shader, int i) override;
};
