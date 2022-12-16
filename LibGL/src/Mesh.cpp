#include "Mesh.h"

#include <glad/glad.h>

#include "Singleton.h"

lm::mat4 LowRenderer::Mesh::CalculateMVP(lm::Mat4<float> view)
{
	this->projectionMat = SINGLETON.GetProjectionMatrix();
	this->viewMat = view;
	this->mvp = projectionMat * viewMat * modelMat;

	return this->mvp;
}

void LowRenderer::Mesh::Update(GameObject* gameObject, float delta)
{
	this->modelMat = gameObject->Matrix;

	if (model != nullptr) {
		if (texture != nullptr)
			texture->Bind();

		UpdateUniform(SINGLETON.GetShader(), SINGLETON.GetCam()->GetComponent<Camera>("Camera"));
		model->draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void LowRenderer::Mesh::Start(GameObject* gameObject)
{
	std::cout << gameObject << " start\n";
}

LowRenderer::Mesh::Mesh(const std::string modelPath, const std::string texturePath)
{
	name = "Mesh";
	mPath = modelPath;
	tPath = texturePath;

	model = SINGLETON.GetResources()->Create<Model>(modelPath.c_str());

	if (!texturePath.empty()) {
		texture = SINGLETON.GetResources()->Create<Texture>(texturePath.c_str());
	}
}

void LowRenderer::Mesh::UpdateUniform(Resources::Shader* shader, Camera* cam)
{
	SINGLETON.GetShader()->SetMat4f(this->CalculateMVP(cam->CreateViewMatrix()), "MVP");
	lm::mat4 tmp2 = this->modelMat;
	shader->SetMat4f(tmp2, "model");
	lm::mat3 tmp = this->modelMat;
	(tmp.inverse()).transpose();
	shader->SetMat3f(tmp, "normalMatrix");
}