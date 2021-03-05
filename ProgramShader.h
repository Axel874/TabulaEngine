#pragma once
class ProgramShader {
public:
	ProgramShader(const std::string& shaderSourceFolder);
	~ProgramShader();

	void setInt(const std::string& name, const int& value);
	void setFloat(const std::string& name, const float& value);
	void setBool(const std::string& name, const bool& value);
	void setUint(const std::string& name, const unsigned int& value);
	void setMatrix4fv(const std::string& name, const glm::mat4& value);
	void setVector3f(const std::string& name, const glm::vec3& value);

	void Bind();
private:
	const GLuint m_Handle;

	GLuint LoadShader(const std::string& src, const GLenum& type);
	std::string LoadShaderSource(const std::string& filePath);
	void CompileShader(unsigned int shaderHandle);
	void HandleShaderError(const GLuint& shaderHandle);
	GLuint GetHandle() const;

	void AttachShaders(const int& shaderCount, const int* pShaderHandles);
	void DetachShaders(const int& shaderCount, const int* pShaderHandles);
	void DeleteShaders(const int& shaderCount, const int* pShaderHandles);

	void LinkProgram();
	void HandleProgramError();
};