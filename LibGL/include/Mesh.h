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

		void Start(GameObject* gameObject) override;

	public:

		Mesh(const std::string modelPath, const std::string texturePath = "");
		Mesh(Model* model, Texture* texture = nullptr);
		lm::Mat4<float> modelMat;
		lm::Mat4<float> projectionMat;
		lm::Mat4<float> viewMat;
		lm::Mat4<float> mvp;

		void UpdateUniform(Resources::Shader* shader, Camera* cam);
		lm::mat4 CalculateMVP(lm::Mat4<float> view);

		void Update(GameObject* gameObject, float delta) override;
	};
}
