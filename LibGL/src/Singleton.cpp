#include "Application.h"

Singleton::Singleton()
{
	resources = new ResourceManager();
}

Singleton::~Singleton()
{
	delete resources;
}

Singleton& Singleton::GetInstance()
{
	static Singleton instance;
	return instance;
}

GameObject* Singleton::FindObjectWithName(std::string str) const
{
	for (const auto& gameObject : app->gameObjects)
	{
		if (gameObject->name == str) {
			return gameObject;
		}
	}
	return nullptr;
}

void Singleton::SetProjectionMatrix(float width, float height)
{
	projection = lm::mat4::perspectiveProjection(70, (float)width / (float)height, 0.1f, 100.0f);
}

lm::mat4 Singleton::GetProjectionMatrix()
{
	return this->projection;
}

void Singleton::SetCam(GameObject* c)
{
	currentCam = c;
}

void Singleton::SetTimeScale(const float& newScale)
{
	timescale = newScale;
}

void Singleton::SetTimeScale(const bool& newScale)
{
	if (newScale) {
		timescale = 1;
	}
	else {
		timescale = 0;
	}
}

void Singleton::SetShader(Resources::Shader* s)
{
	shader = s;
}

void Singleton::StartSound(bool loop)
{
	soundsVec.push_back(soundEngine->play2D("LibGL/assets/Sounds/music.mp3", loop)); //music
}

void Singleton::StopAllSounds()
{
	for (int i = 0; i < soundsVec.size(); i++)
	{
		std::cout << "ok" << std::endl;
	}
	soundsVec.clear();
}

ResourceManager* Singleton::GetResources() const
{
	return resources;
}

Resources::Shader* Singleton::GetShader() const
{
	return shader;
};

GameObject* Singleton::GetCam() const
{
	return currentCam;
}

float Singleton::GetTimeScale() const
{
	return timescale;
}