#include "pch.h"
#include "ProgramShader.h"
#define LogWarning(message) LogWarning(message, __FILE__, __LINE__)

//public
ProgramShader::ProgramShader(const std::string& shaderSourceFolder)
	: m_Handle(glCreateProgram())
{
	const int shaderCount = 2;
	int shaderHandles[2];
	shaderHandles[0] = LoadShader(shaderSourceFolder + "/vs.txt", GL_VERTEX_SHADER);
	shaderHandles[1] = LoadShader(shaderSourceFolder + "/fs.txt", GL_FRAGMENT_SHADER);

	AttachShaders(shaderCount, shaderHandles);

	LinkProgram();

	DetachShaders(shaderCount, shaderHandles);
	DeleteShaders(shaderCount, shaderHandles);
}
ProgramShader::~ProgramShader() {
	glDeleteProgram(m_Handle);
}

void ProgramShader::setInt(const std::string& name, const int& value) {
	glUniform1i(glGetUniformLocation(m_Handle,name.c_str()),value);
}
void ProgramShader::setFloat(const std::string& name, const float& value){
	glUniform1f(glGetUniformLocation(m_Handle, name.c_str()), value);
}
void ProgramShader::setBool(const std::string& name, const bool& value){
	glUniform1i(glGetUniformLocation(m_Handle, name.c_str()), (int)value);
}
void ProgramShader::setUint(const std::string& name, const unsigned int& value){
	glUniform1ui(glGetUniformLocation(m_Handle, name.c_str()), value);
}
void ProgramShader::setMatrix4fv(const std::string& name, const glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(m_Handle, name.c_str()),1,GL_FALSE, glm::value_ptr(value));
}
void ProgramShader::setVector3f(const std::string& name, const glm::vec3& value) {
	glUniform3fv(glGetUniformLocation(m_Handle, name.c_str()), 1, glm::value_ptr(value));
}

void ProgramShader::Bind() {
	glUseProgram(m_Handle);
}

//private
GLuint ProgramShader::LoadShader(const std::string& src, const GLenum& type)
{
	unsigned int shaderHandle{ glCreateShader(type) };

	const std::string srcString = LoadShaderSource(src);
	const char* shaderSource = srcString.c_str();

	glShaderSource(shaderHandle, 1, &shaderSource, NULL);

	CompileShader(shaderHandle);

	return shaderHandle;
}
std::string ProgramShader::LoadShaderSource(const std::string& filePath) {
	std::ifstream file;
	file.open((filePath).c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			std::getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		utils::LogWarning("Unable to open shader file");
	}
	return output;
}
void ProgramShader::CompileShader(unsigned int shaderHandle)
{
	glCompileShader(shaderHandle);
	HandleShaderError(shaderHandle);
}
void ProgramShader::HandleShaderError(const GLuint& shaderHandle) {
	int success{};
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint logLength{};
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
		char* infoLog = new char[logLength];
		glGetShaderInfoLog(shaderHandle, logLength, NULL, infoLog);
		utils::LogWarning(("ERROR::SHADER::COMPILATION_FAILED\n" + std::string(infoLog)));
		delete[] infoLog;
	}
}
GLuint ProgramShader::GetHandle() const {
	return this->m_Handle;
}

void ProgramShader::AttachShaders(const int& shaderCount, const int* pShaderHandles)
{
	for (int i = 0; i < shaderCount; i++) {
		glAttachShader(m_Handle, pShaderHandles[i]);
	}
}
void ProgramShader::DetachShaders(const int& shaderCount, const int* pShaderHandles)
{
	for (int i = 0; i < shaderCount; i++) {
		glDetachShader(m_Handle, pShaderHandles[i]);
	}
}
void ProgramShader::DeleteShaders(const int& shaderCount, const int* pShaderHandles)
{
	for (int i = 0; i < shaderCount; i++) {
		glDeleteShader(pShaderHandles[i]);
	}
}

void ProgramShader::LinkProgram()
{
	glLinkProgram(m_Handle);
	HandleProgramError();
}
void ProgramShader::HandleProgramError() {
	int success{};
	glGetProgramiv(m_Handle, GL_LINK_STATUS, &success);
	if (!success) {
		GLint logLength{};
		glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &logLength);
		char* infoLog = new char[logLength];
		glGetProgramInfoLog(m_Handle, logLength, NULL, infoLog);
		utils::LogWarning(("ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(infoLog)));
		delete[] infoLog;
	}
}
