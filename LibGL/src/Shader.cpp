#include "Shader.h"

Resources::Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	vertexShader = LoadSourceShader(vertexFile);
	fragmentShader = LoadSourceShader(fragmentFile);
}

void Resources::Shader::Init()
{
	int vertexShaderId = 0;
	int FragmentShaderId = 0;
	vertexShaderId = Load_shader(GL_VERTEX_SHADER, vertexShader.c_str());
	FragmentShaderId = Load_shader(GL_FRAGMENT_SHADER, fragmentShader.c_str());

	this->Link(vertexShaderId, FragmentShaderId);
}

Resources::Shader::~Shader()
{
	glDeleteProgram(this->id);
}

std::string Resources::Shader::LoadSourceShader(const char* filename) const
{
	std::string temp = "";
	std::string src = "";

	std::ifstream in_file(filename);

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
		{
			src += temp + "\n";
		}
	}
	else
	{
		DEBUG_LOG("ERROR::SHADER COULD NOT OPEN FILE");
	}

	in_file.close();

	return src;
}

int Resources::Shader::Load_shader(GLenum type, const char* file) const
{
	char log[512];
	int success;

	int shader = glCreateShader(type);

	glShaderSource(shader, 1, &file, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, log);
		DEBUG_LOG("ERROR::SHADER COULD NOT COMPILE SHADER");
		std::cout << log << '\n';
	}

	return shader;
}

void Resources::Shader::Link(const int vertexShader, int fragmentShader)
{
	char log[512];
	int succes;

	this->id = glCreateProgram();

	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);

	glLinkProgram(this->id);

	glGetProgramiv(this->id, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		DEBUG_LOG("ERROR::SHADER COULD NOT LINK THE PROGRAM");
		std::cout << log << '\n';
	}

	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Resources::Shader::Use() const
{
	glUseProgram(this->id);
}

void Resources::Shader::UnUse()
{
	glUseProgram(0);
}

void Resources::Shader::SetVec3f(lm::Vec3<float> value, const char* name) const
{
	glUniform3fv(glGetUniformLocation(this->id, name), 1, &value[0]);
}
void Resources::Shader::SetVec3f(const char* name, lm::Vec3<float> value) const
{
	glUniform3fv(glGetUniformLocation(this->id, name), 1, &value[0]);
}

void Resources::Shader::SetMat4f(lm::Mat4<float> value, const char* name) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, &value[0][0]);
}
void Resources::Shader::SetMat3f(lm::Mat3<float> value, const char* name) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, &value[0]);
}

void Resources::Shader::SetBool(const std::string& name, const bool value) const
{
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), static_cast<int>(value));
}

void Resources::Shader::SetInt(const std::string& name, const int value) const
{
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void Resources::Shader::SetFloat(const std::string& name, const float value) const
{
	glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}