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
		model->draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

LowRenderer::Mesh::Mesh(std::string modelPath, std::string texturePath)
{
	name = "Mesh";
	mPath = modelPath;
	tPath = texturePath;

	if (SINGLETON.getResources()->Get<Model>(modelPath) != nullptr) {
		this->model = SINGLETON.getResources()->Get<Model>(modelPath);
	}
	else
	{
		this->model = SINGLETON.getResources()->CreateRessource<Model>(modelPath.c_str());
	}

	if (texturePath != "") {
		if (SINGLETON.getResources()->Get<Texture>(texturePath) != nullptr) {
			this->texture = SINGLETON.getResources()->Get<Texture>(texturePath);
		}
		else
		{
			this->texture = SINGLETON.getResources()->CreateRessource<Texture>(texturePath.c_str());
		}
	}
}

void LowRenderer::Mesh::updateUniform(Resources::Shader* shader, Camera* cam)
{
	SINGLETON.getShader()->setMat4f(this->calculateMVP(cam->createViewMatrix()), "MVP");
	lm::mat4 tmp2 = this->modelMat;
	shader->setMat4f(tmp2, "model");
	lm::mat3 tmp = this->modelMat;
	(tmp.inverse()).transpose();
	shader->setMat3f(tmp, "normalMatrix");
}