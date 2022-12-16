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

		Texture(char const* const& filename);

		virtual void Init() override;

		void Bind() const;

	private:
		unsigned char* data;
		int x = 512;
		int y = 512;
		int n = 3;
	};
}
