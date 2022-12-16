#include "Model.h"

#include <glad/glad.h>

#include "Core/Debug/Log.h"

#define _CRT_SECURE_NO_WARNINGS

#pragma region USING NAMESPACE
using namespace Core::Debug;
#pragma endregion

Model::Model(const char* filename)
{
	onlyVertices = false;
	LoadObj(filename);
}

void Model::Init()
{
	vbo.InitVbo(this);
	vao.InitVao();
}

bool Model::LoadObj(const char* filename)
{
	Log log;
	log.Openfile("LogFile.txt");

	FILE* file = nullptr;
	fopen_s(&file, filename, "r");

	if (!file)
	{
		log.Print("Model.cpp | Impossible to open the file !\n");
		DEBUG_LOG("Model.cpp | Impossible to open the file !\n");
		return false;
	}

	std::vector<lm::vec3> tempVertices;
	std::vector<lm::vec3> tempNormals;
	std::vector <lm::vec2> tempUvs;

	while (true)
	{
		char lineHeader[128];

		if (int const res = fscanf(file, "%s", lineHeader); res == EOF)
		{
			log.Print("Model.cpp | LoadOBJ : Reach end of OBJ file\n");
			break;
		}

		if (strcmp(lineHeader, "v") == 0)
		{
			lm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);
			tempVertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "#") == 0)
		{
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			lm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv[0], &uv[1]);
			tempUvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			lm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2]);
			tempNormals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			long long temp_position_buffer[9]{ 0 };

			if (tempUvs.empty() && tempNormals.empty())
			{
				onlyVertices = true;
				fscanf_s(file, "%lld %lld %lld\n",
					&temp_position_buffer[0],
					&temp_position_buffer[3],
					&temp_position_buffer[6]);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[0] - 1], 0.f, 0.f);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[3] - 1], 0.f, 0.f);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[6] - 1], 0.f, 0.f);
			}

			if (tempUvs.empty() && onlyVertices == false)
			{
				long long tempNormalBuffer[9]{ 0 };
				fscanf_s(file, "%lld//%lld %lld//%lld %lld//%lld\n",
					&temp_position_buffer[0], &tempNormalBuffer[2],
					&temp_position_buffer[3], &tempNormalBuffer[5],
					&temp_position_buffer[6], &tempNormalBuffer[8]);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[0] - 1], 0.f, tempNormals[tempNormalBuffer[2] - 1]);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[3] - 1], 0.f, tempNormals[tempNormalBuffer[5] - 1]);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[6] - 1], 0.f, tempNormals[tempNormalBuffer[8] - 1]);
			}
			if (tempNormals.empty() && onlyVertices == false)
			{
				long long tempUvBuffer[9]{ 0 };
				fscanf_s(file, "%lld/%lld/ %lld/%lld/ %lld/%lld/\n",
					&temp_position_buffer[0], &tempUvBuffer[1],
					&temp_position_buffer[3], &tempUvBuffer[4],
					&temp_position_buffer[6], &tempUvBuffer[7]);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[0] - 1], tempUvs[tempUvBuffer[1] - 1], 0);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[3] - 1], tempUvs[tempUvBuffer[4] - 1], 0);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[6] - 1], tempUvs[tempUvBuffer[7] - 1], 0);
			}
			if (!tempUvs.empty() && !tempNormals.empty() && onlyVertices == false)
			{
				long long temp_uv_buffer[9]{ 0 };
				long long temp_normal_buffer[9]{ 0 };
				fscanf_s(file, "%lld/%lld/%lld %lld/%lld/%lld %lld/%lld/%lld\n",
					&temp_position_buffer[0], &temp_uv_buffer[1], &temp_normal_buffer[2],
					&temp_position_buffer[3], &temp_uv_buffer[4], &temp_normal_buffer[5],
					&temp_position_buffer[6], &temp_uv_buffer[7], &temp_normal_buffer[8]);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[0] - 1], tempUvs[temp_uv_buffer[1] - 1], tempNormals[temp_normal_buffer[2] - 1]);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[3] - 1], tempUvs[temp_uv_buffer[4] - 1], tempNormals[temp_normal_buffer[5] - 1]);
				vertexBuffer.emplace_back(tempVertices[temp_position_buffer[6] - 1], tempUvs[temp_uv_buffer[7] - 1], tempNormals[temp_normal_buffer[8] - 1]);
			}
		}
	}

	return true;
}

void Model::BindingVao()
{
	vao.Bind();
}

void Model::Draw()
{
	vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexBuffer.size()));
}

void Model::Buffer::InitVbo(Model* model)
{
	glGenBuffers(1, &idVbo);
	glBindBuffer(GL_ARRAY_BUFFER, idVbo);
	glBufferData(GL_ARRAY_BUFFER, model->vertexBuffer.size() * sizeof(Vertex), model->vertexBuffer.data(), GL_STATIC_DRAW);
}

void Model::VertexAttributes::InitVao()
{
	glGenVertexArrays(1, &idVao);
	glBindVertexArray(idVao);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, position)));
	glEnableVertexAttribArray(0);

	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureUv));
	glEnableVertexAttribArray(1);

	// normal  attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::VertexAttributes::Bind()
{
	if (idVao == GL_FALSE)
	{
		glGenVertexArrays(1, &idVao);
	}
	glBindVertexArray(idVao);
}

Model::Buffer::~Buffer()
{
	glDeleteBuffers(1, &idVbo);
}

Model::VertexAttributes::~VertexAttributes()
{
	glDeleteVertexArrays(1, &idVao);
}