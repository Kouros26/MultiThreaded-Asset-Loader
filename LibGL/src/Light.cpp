#include "Light.h"
#include "Singleton.h"
#include "Vec2/Vec2.h"

void SpotLight::sendToShader(Resources::Shader* shader, int i)
{
	std::string str = "spotLights[" + std::to_string(i) + "]";
	std::string temp = str;

	shader->setVec3f((str.append(".position")).c_str(), worldTransform.getPosition());
	str = temp;
	shader->setVec3f((str.append(".direction")).c_str(), getFront());
	str = temp;
	shader->setVec3f((str.append(".color")).c_str(), this->lightColor);
	str = temp;
	shader->setFloat((str.append(".ambient")), this->ambient);
	str = temp;
	shader->setFloat((str.append(".diffuse")), this->diffuse);
	str = temp;
	shader->setFloat((str.append(".specular")), this->specular);
	str = temp;
	shader->setFloat(str.append(".constant"), this->constant);
	str = temp;
	shader->setFloat(str.append(".linear"), this->linear);
	str = temp;
	shader->setFloat(str.append(".quadratic"), this->quadratic);
	str = temp;
	shader->setFloat((str.append(".cutOff")), static_cast<float>(cos(lm::degreesToRadians(this->cutOff))));
	str = temp;
	shader->setFloat((str.append(".outerCutOff")), static_cast<float>(cos(lm::degreesToRadians(this->outerCutOff))));
}

SpotLight::SpotLight(lm::vec3 lightColor, float diff, float amb, float spec, float constant, float linear, float quadratic, float cutOff, float outerCutOff, std::string name)
	:Light(diff, amb, spec, lightColor)
{
	this->name = name.empty() ? "spotLight" : name;

	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}

PointLight::PointLight(lm::vec3 lightColor, float diff, float amb, float spec, float constant, float linear, float quadratic, std::string name)
	:Light(diff, amb, spec, lightColor)
{
	this->name = name.empty() ? "pointLight" : name;

	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

void PointLight::sendToShader(Resources::Shader* shader, int i)
{
	// point light 1
	std::string str = "pointLights[" + std::to_string(i) + "]";
	std::string temp = str;
	shader->setVec3f((str.append(".position")).c_str(), worldTransform.getPosition());
	str = temp;
	shader->setVec3f((str.append(".color")).c_str(), this->lightColor);
	str = temp;
	shader->setFloat((str.append(".ambient")).c_str(), this->ambient);
	str = temp;
	shader->setFloat((str.append(".diffuse")).c_str(), this->diffuse);
	str = temp;
	shader->setFloat((str.append(".specular")).c_str(), this->specular);
	str = temp;
	shader->setFloat(str.append(".constant"), this->constant);
	str = temp;
	shader->setFloat(str.append(".linear"), this->linear);
	str = temp;
	shader->setFloat(str.append(".quadratic"), this->quadratic);
}

DirectionLight::DirectionLight(lm::vec3 lightColor, float diff, float amb, float spec, std::string name)
	:Light(diff, amb, spec, lightColor)
{
	this->name = name.empty() ? "dirLight" : name;
}

void DirectionLight::sendToShader(Resources::Shader* shader, int i)
{
	std::string str = "dirLights[" + std::to_string(i) + "]";
	std::string temp = str;
	shader->setVec3f((str.append(".direction").c_str()), getFront());
	str = temp;
	shader->setVec3f((str.append(".color").c_str()), this->lightColor);
	str = temp;
	shader->setFloat((str.append(".ambient").c_str()), this->ambient);
	str = temp;
	shader->setFloat((str.append(".diffuse").c_str()), this->diffuse);
	str = temp;
	shader->setFloat((str.append(".specular").c_str()), this->specular);
	str = temp;
}

Light::Light(float diffuse, float ambient, float specular, lm::vec3 lightColor)
	:GameObject("Light"), diffuse(diffuse),
	ambient(ambient), specular(specular), lightColor(lightColor)
{
}