#pragma once
#include "Camera.h"
#include "Shader.h"
#include "Light.h"

#include <vector>
//#include <irrKlang.h>

namespace Resources {
	class Application;
}

class Singleton
{
private:
	Singleton() {
		resources = new ResourceManager();
	};
	~Singleton() {
		delete resources;
	};
	GameObject* currentCam = nullptr;
	Resources::Shader* shader = nullptr;
	ResourceManager* resources = nullptr;
	lm::mat4 projection;
public:
	int gmCount = 0;
	float mouseOffSetX = 0, mouseOffSetY = 0;
	bool W = false, A = false, S = false, D = false, LMB = false, RMB = false, SPACE = false, E = false;
	bool LCTRL = false, CTRL_S = false, CTRL_O = false;
	float delta = 0;
	float unscaledDelta = 0;
	float timescale = 1;
	GameObject* editorCam = nullptr;
	GameObject* gameCam = nullptr;
	Resources::Application* app = nullptr;
	//irrklang::ISoundEngine* soundEngine = nullptr;
	//std::vector<irrklang::ISound*> soundsVec;

	static Singleton& getInstance()
	{
		static Singleton instance;
		return instance;
	}

	GameObject* findObjectWithName(std::string str);

	void setProjectionMatrix(float Width, float  Height)
	{
		projection = lm::mat4::perspectiveProjection(70, (float)Width / (float)Height, 0.1f, 100.0f);
	}

	lm::mat4 getProjectionMatrix()
	{
		return this->projection;
	}

	void setCam(GameObject* c) {
		currentCam = c;
	}
	GameObject* getCam() {
		return currentCam;
	};

	float getTimeScale() {
		return timescale;
	}
	void setTimeScale(const float& newScale) {
		timescale = newScale;
	}
	void setTimeScale(const bool& newScale) {
		if (newScale) {
			timescale = 1;
		}
		else {
			timescale = 0;
		}
	}

	void playSound(int n, bool loop) {
		//switch (n) {
		//case 1: soundsVec.push_back(soundEngine->play2D("game/sounds/music.mp3", loop)); //music
		//	break;
		//case 2: soundsVec.push_back(soundEngine->play2D("game/sounds/portal_shoot_player.mp3", loop)); //player shoot portal
		//	break;
		//case 3: soundsVec.push_back(soundEngine->play2D("game/sounds/player_teleport.mp3", loop)); //player teleport
		//	break;
		//case 4: soundsVec.push_back(soundEngine->play2D("game/sounds/player_hit.mp3", loop)); //player hit
		//	break;
		//case 5: soundsVec.push_back(soundEngine->play2D("game/sounds/button.mp3", loop)); //button activate
		//	break;
		//case 6: soundsVec.push_back(soundEngine->play2D("game/sounds/grab_object.mp3", loop)); //player grab object
		//	break;
		//case 7: soundsVec.push_back(soundEngine->play2D("game/sounds/turret_down.mp3", loop)); //turret destroyed
		//	break;
		//}
	}

	void stopAllSounds() {
		/*for (int i = 0; i < soundsVec.size(); i++)
		{
			std::cout << "ok" << std::endl;
		}
		soundsVec.clear();*/
	}

	ResourceManager* getResources() {
		return resources;
	};

	void setShader(Resources::Shader* s) {
		shader = s;
	}
	Resources::Shader* getShader() {
		return shader;
	};
};

#define SINGLETON Singleton::getInstance()
