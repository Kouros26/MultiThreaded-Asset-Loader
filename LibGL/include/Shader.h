#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "RessourceManager.h"
#include "Core/Debug/Log.h"
#include "Vec3/Vec3.h"
#include "Mat4/Mat4.h"

#include "Mat3/Mat3.h"

namespace Resources
{
	class Shader : public IResource
	{
	private:
		//private var
		int id = 0;

		std::string vertexShader;
		std::string fragmentShader;

		//private func
		std::string LoadSourceShader(const char* filename) const;
		int Load_shader(GLenum type, const char* file) const;
		void Link(int vertexShader, int fragmentShader);

	public:
		//Constructor / destructor
		Shader() {};
		Shader(const char* vertexShader, const  char* fragmentShader);
		~Shader();
		//public func
		virtual void Init() override;

		void SetMat4f(const lm::Mat4<float> value, const char* name) const;
		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec3f(const lm::Vec3<float> value, const char* name) const;
		void SetVec3f(const char* name, const lm::Vec3<float> value) const;
		void SetMat3f(lm::Mat3<float> value, const char* name) const;
		void Use() const;
		static void UnUse();
	};
}
