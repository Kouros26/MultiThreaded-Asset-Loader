#pragma once
#include "glad/glad.h"

#include <stb_image.h>
#include "RessourceManager.h"

namespace Resources
{
	class Texture : public IResource
	{
	public:
		GLuint index;

		Texture() {
			index = GL_FALSE;
		};
		Texture(char const* const& filename);

		void loadTexture(char const* const& filename);

		void Bind();
	};
}
