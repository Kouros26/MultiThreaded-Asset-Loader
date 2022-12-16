#pragma once
#include "Core/Debug/Assertion.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Debug/Log.h"

#include "Mat4/Mat4.h"
#include "Vec3/Vec3.h"

#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "RessourceManager.h"
#include "Mesh.h"
#include "Light.h"
#include "Texture.h"

#include "GameObject.h"
#include "Singleton.h"

#include <cstdio>

#include <cstdio>
#include <ostream>
#include <iostream>

namespace Resources
{
	class Application
	{
	private:
		//var
		GLFWwindow* window;
		lm::Mat4<float> projectionMat;
		const int SCR_WIDTH;
		const int SCR_HEIGHT;

		/*UIManager* UIManager;*/

		//Delta Time
		float currentTime;
		float lastTime;

		// Editor
		int selectedItem;
		int newGameObject;
		bool addComponentButton;
		bool renameGameObject;

		//Mouse Input
		double lastMouseX;
		double lastMouseY;
		double mouseX;
		double mouseY;
		double mouseOffSetX;
		double	mouseOffSetY;
		bool firstMouse;

		//private function
		void InitWindow(const char* title);
		static void InitGlad();
		static void InitOpenGLOption();
		static void InitCam();
		void InitLight();
		void InitGameObject();

		static void InitMusic();

		void UpdateLights() const;
		void UpdateGameObject() const;

		void GameLoop();

	public:
		//constructor / destructor
		Application(
			char const* title,
			const int SCR_WIDTH,
			const int SCR_HEIGHT);

		//public function
		void Run();
		void UpdateDelta();
		void UpdateMouseInput();

		// Get
		GLFWwindow* GetWindow() const;

		// Set
		void SetCursor(bool cursor) const;

		void UpdateInput();
		void ProcessInput(GLFWwindow* window);

		//gameObject
		std::vector<GameObject*> gameObjects;
		std::vector<GameObject*> gameObjectsCopy;

		//clear color
		lm::vec4 clear_color;

		//editor

		bool editor = true;
		bool showDebugDrawer = true;
		bool showImgui = true;

		//static function
		static void Framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void APIENTRY GlDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	};
}
