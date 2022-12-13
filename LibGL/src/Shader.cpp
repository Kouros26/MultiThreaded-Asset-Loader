#include "../include/Shader.h"

Resources::Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	init(vertexFile, fragmentFile);
}

void Resources::Shader::init(const char* vertexFile, const char* fragmentFile)
{
	int vertexShader = 0;
	int FragmentShader = 0;
	vertexShader = load_shader(GL_VERTEX_SHADER, vertexFile);
	FragmentShader = load_shader(GL_FRAGMENT_SHADER, fragmentFile);

	this->Link(vertexShader, FragmentShader);
}

Resources::Shader::~Shader()
{
	glDeleteProgram(this->id);
}

std::string Resources::Shader::loadSourceShader(const char* filename)
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

int Resources::Shader::load_shader(GLenum type, const char* filename)
{
	char log[512];
	int succes;

	int shader = glCreateShader(type);
	std::string tem_src = this->loadSourceShader(filename);
	const char* src = tem_src.c_str();

	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(shader, 512, NULL, log);
		DEBUG_LOG("ERROR::SHADER COULD NOT COMPILE SHADER");
		std::cout << log << '\n';
	}

	return shader;
}

void Resources::Shader::Link(int vertexShader, int fragmentShader)
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

void Resources::Shader::use()
{
	glUseProgram(this->id);
}

void Resources::Shader::unUse()
{
	glUseProgram(0);
}

void Resources::Shader::setVec3f(lm::Vec3<float> value, const char* name)
{
	glUniform3fv(glGetUniformLocation(this->id, name), 1, &value[0]);
}
void Resources::Shader::setVec3f(const char* name, lm::Vec3<float> value)
{
	glUniform3fv(glGetUniformLocation(this->id, name), 1, &value[0]);
}

void Resources::Shader::setMat4f(lm::Mat4<float> value, const char* name)
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, &value[0][0]);
}
void Resources::Shader::setMat3f(lm::Mat3<float> value, const char* name)
{
	glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, &value[0]);
}

void Resources::Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
}

void Resources::Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}

void Resources::Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}