#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

#include <iostream>
#include <glad/glad.h>

Resources::Texture::Texture(char const* const& filename)
{
	loadTexture(filename);
}

void Resources::Texture::loadTexture(char const* const& filename)
{
	glGenTextures(1, &index);
	glBindTexture(GL_TEXTURE_2D, index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int x = 512;
	int y = 512;
	int n = 3;
	unsigned char* data = stbi_load(filename, &x, &y, &n, 0);

	if (data != nullptr) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "error loading texture " << filename << std::endl;
	}
}

void Resources::Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, index);
}