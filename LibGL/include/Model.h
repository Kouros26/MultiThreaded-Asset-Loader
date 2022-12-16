#pragma once

#include <utility>
#include <vector>
#include "RessourceManager.h"
#include "Texture.h"
#include "Vec2/Vec2.h"
#include "Vec3/Vec3.h"

#include "Shader.h"

#pragma region USING NAMESPACE
using namespace lm;
using namespace Resources;
#pragma endregion

namespace Resources
{
	class Model : public IResource
	{
	private:

		struct Vertex
		{
			vec3 position;
			vec2 textureUv;
			vec3 normal;

			Vertex(vec3 position, vec2 textureUv, vec3 normal)
				: position(std::move(position)), textureUv(std::move(textureUv)), normal(std::move(normal))
			{};
		};

		class Buffer
		{
		public:
			GLuint idVbo = GL_FALSE;
			~Buffer();

			void InitVbo(Model* model);
		};

		class VertexAttributes
		{
			GLuint idVao = GL_FALSE;
		public:
			~VertexAttributes();

			void InitVao();
			void Bind();
		};

		std::vector<Vertex> vertexBuffer;
		std::vector<uint32_t> indexBuffer;

	public:
		Buffer vbo;
		VertexAttributes vao;

		bool onlyVertices;

		Model(const char* filename);
		virtual void Init() override;

		bool LoadObj(const char* filename);
		void BindingVao();
		void Draw();
	};
}
