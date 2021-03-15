#include "pch.h"
#include "Texture.h"
#define LogWarning(message) LogWarning(message, __FILE__, __LINE__)
//public
Texture::Texture(const std::string& src, const GLint& format)
	: m_Handle(glCreateTexture()), m_Src(src)
{
	LoadTexture(src, format);
	SetParameters();
	glBindTexture(GL_TEXTURE_2D, 0);
}
Texture::~Texture() {
	glDeleteTextures(1, &m_Handle);
}

void Texture::Bind(const GLenum& textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_Handle);
}
std::string Texture::GetSource() const { return m_Src; }
GLuint Texture::GetHandle() const { return m_Handle; }
//private
GLuint Texture::glCreateTexture() {
	GLuint handle;
	glGenTextures(1, &handle);
	return handle;
}
void Texture::LoadTexture(const std::string& src, const GLint& format)
{
	glBindTexture(GL_TEXTURE_2D, m_Handle);

	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* imgData = stbi_load(src.c_str(), &width, &height, &nrChannels, 0);

	if (imgData) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imgData);
	}
	else { utils::LogWarning("Failed to load texture" + src); }
	stbi_image_free(imgData);
}
void Texture::SetParameters()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}