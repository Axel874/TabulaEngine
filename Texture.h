#pragma once
class Texture {
public:
	Texture(const std::string& src, const GLint& format);
	void LoadTexture(const std::string& src, const GLint& format);
	void SetParameters();
	~Texture();

	void Bind(const GLenum& textureUnit);

	std::string GetSource() const;
	GLuint GetHandle() const;
private:
	GLuint m_Handle;
	const std::string m_Src;

	GLuint glCreateTexture();
};