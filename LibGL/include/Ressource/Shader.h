#pragma once
#include <glad/glad.h>
#include <string>

#include "IResource.h"
#include "../../LibMaths/Mat4/Mat4.h"
#include "../../LibMaths/Vec3/Vec3.h"
#include "../../LibMaths/Vec2/Vec2.h"


#include "Ressource/ResourcesManager.h"

class Shader : public IResource
{
public:
    // constructor generates the shader on the fly
    Shader(const char* name, const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    // activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, lm::vec2& value) const;
	void setVec3(const std::string& name, lm::vec3& value) const;
	void setVec4(const std::string& name, lm::vec4& value) const;
	void setMat4(const std::string& name, lm::mat4& mat) const;

	unsigned int& GetShaderProgram();

private:
    unsigned int ID;
    std::string name;
    std::string vertexPath;
    std::string fragmentPath;
    std::string geometryPath;
    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(GLuint shader, std::string type);
};