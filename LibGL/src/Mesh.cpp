#include "Mesh.h"

#include <glad/glad.h>

#include "Singleton.h"

lm::mat4 LowRenderer::Mesh::calculateMVP(lm::Mat4<float> view)
{
	this->projectionMat = SINGLETON.getProjectionMatrix();
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

		updateUniform(SINGLETON.getShader(), SINGLETON.getCam()->getComponent<Camera>("Camera"));
		model->Draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

LowRenderer::Mesh::Mesh(const std::string modelPath, const std::string texturePath)
{
	name = "Mesh";
	mPath = modelPath;
	tPath = texturePath;

	SINGLETON.getResources()->Create<Model>(modelPath.c_str());
	model = SINGLETON.getResources()->Get<Model>(modelPath.c_str());

	if (!texturePath.empty()) {
		SINGLETON.getResources()->Create<Texture>(texturePath.c_str());
		texture = SINGLETON.getResources()->Get<Texture>(texturePath.c_str());
	}
}

LowRenderer::Mesh::Mesh(Model* model, Texture* texture)
{
	name = "Mesh";
	this->model = model;
	this->texture = texture;
}

void LowRenderer::Mesh::updateUniform(Resources::Shader* shader, Camera* cam)
{
	SINGLETON.getShader()->setMat4f(this->calculateMVP(cam->CreateViewMatrix()), "MVP");
	lm::mat4 tmp2 = this->modelMat;
	shader->setMat4f(tmp2, "model");
	lm::mat3 tmp = this->modelMat;
	(tmp.inverse()).transpose();
	shader->setMat3f(tmp, "normalMatrix");
}