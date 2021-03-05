#pragma once
class Texture {
public:
	Texture(const std::string& src, const GLint& format);
	void LoadTexture(const std::string& src, const GLint& format);
	void SetParameters();
	~Texture();

	void Bind(const GLenum& textureUnit);
private:
	GLuint m_Handle;

	GLuint glCreateTexture();
};