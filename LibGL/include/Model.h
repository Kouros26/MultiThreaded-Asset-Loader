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
			vec2 texture_uv;
			vec3 normal;

			Vertex(vec3 position, vec2 texture_uv, vec3 normal)
			: position(std::move(position)), texture_uv(std::move(texture_uv)), normal(std::move(normal))
			{}
		};

		class Buffer
		{
		public:
			GLuint id_vbo = GL_FALSE;
			~Buffer();

			void init_vbo(Model* model);
		};

		class vertex_attributes
		{
			GLuint id_vao_ = GL_FALSE;
		public:
			~vertex_attributes();

			void init_vao();
			void bind();
		};

		std::vector<Vertex> vertex_buffer_;
		std::vector<uint32_t> index_buffer_;

	public:
		Buffer vbo;
		vertex_attributes vao;

		bool only_vertices;

		Model(const char* filename);
		virtual void Init() override;

		bool load_obj(const char* filename);
		void binding_vao();
		void draw();
	};
}
