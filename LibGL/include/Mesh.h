#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Vec3/Vec3.h"

namespace LowRenderer
{
	class Mesh : public Component
	{
	private:
		Resources::Model* model;
		Resources::Texture* texture = nullptr;
		std::string mPath;
		std::string tPath;
		void Start(GameObject* gameObject) override { /*IDK Man he doesn't want to compile*/std::cout << gameObject << " start\n"; }
	public:
		Mesh(const std::string modelPath, const std::string texturePath = "");
		lm::Mat4<float> modelMat;
		lm::Mat4<float> projectionMat;
		lm::Mat4<float> viewMat;
		lm::Mat4<float> mvp;

		void updateUniform(Resources::Shader* shader, Camera* cam);
		lm::mat4 calculateMVP(lm::Mat4<float> view);

		void Update(GameObject* gameObject, float delta) override;
	};
}
