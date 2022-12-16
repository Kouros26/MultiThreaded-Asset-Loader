#pragma once
#include "Camera.h"
#include "Shader.h"
#include "Light.h"

#include <vector>
#include <irrKlang.h>

namespace Resources {
	class Application;
}

class Singleton
{
private:

	Singleton();
	~Singleton();

	GameObject* currentCam = nullptr;
	Resources::Shader* shader = nullptr;
	ResourceManager* resources = nullptr;
	lm::mat4 projection;

public:

	int gmCount = 0;
	double mouseOffSetX = 0, mouseOffSetY = 0;
	bool W = false, A = false, S = false, D = false, LMB = false, RMB = false, SPACE = false, E = false;
	bool LCTRL = false, CTRL_S = false, CTRL_O = false;
	float delta = 0;
	float unscaledDelta = 0;
	float timescale = 1;
	GameObject* editorCam = nullptr;
	GameObject* gameCam = nullptr;
	Resources::Application* app = nullptr;
	irrklang::ISoundEngine* soundEngine = nullptr;
	std::vector<irrklang::ISound*> soundsVec;

	static Singleton& GetInstance();

	[[nodiscard]] GameObject* FindObjectWithName(std::string str) const;

	lm::mat4 GetProjectionMatrix();
	GameObject* GetCam() const;
	float GetTimeScale() const;
	ResourceManager* GetResources() const;
	Resources::Shader* GetShader() const;
	
	void SetProjectionMatrix(float width, float  height);
	void SetCam(GameObject* c);
	void SetTimeScale(const float& newScale);
	void SetTimeScale(const bool& newScale);
	void SetShader(Resources::Shader* s);

	void StartSound(bool loop);
	void StopAllSounds();
};

#define SINGLETON Singleton::GetInstance()
