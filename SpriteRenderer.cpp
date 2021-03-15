#include "pch.h"
#include "SpriteRenderer.h"
#include "Sprite.h"

SpriteRenderer::SpriteRenderer(std::vector<Sprite*>& managedSprites)
	: m_rSprites(managedSprites), m_Shader(ProgramShader("./resources/shaders/base")),
	m_ProjectionMatrix(glm::ortho(0.f, 500.0f, 0.f, 280.f, 5.0f, -5.0f))
{
	//generate the VAO used to draw a single sprite
	GenerateVAO();
	//set the used texture unit to 0
	m_Shader.setInt("ourTexture", 0);
	//send projection matrix to our shader
	m_Shader.setMatrix4fv("projection", m_ProjectionMatrix);
}
void SpriteRenderer::GenerateVAO()
{
	//create vertex array object and bind it
	glGenVertexArrays(1, &m_VAOHandle);
	glBindVertexArray(m_VAOHandle);
	//create data buffer
	GLuint VBO{};
	glGenBuffers(1, &VBO);
	//bind data buffer to vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//push vertex data to buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, Sprite::s_GLData, GL_STATIC_DRAW);
	//set info about where to find 1st attribute of our data
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//idem for 2d attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//unbind the VAO
	glBindVertexArray(0);
}
SpriteRenderer::~SpriteRenderer() {
	for (Texture* t : m_LoadedTextures)delete t;
}

void SpriteRenderer::SetManagedSprites(std::vector<Sprite*>& sprites) { m_rSprites = sprites; }
void SpriteRenderer::RenderSprites(const glm::mat4& viewMatrix, SDL_Window* window) {
	RenderSetup(viewMatrix);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawSprites();
	SDL_GL_SwapWindow(window);

	RenderCleanup();
}
void SpriteRenderer::RenderCleanup()
{
	//unbind shader
	m_Shader.UnBind();
	//unbind our sprite VAO
	glBindVertexArray(0);
}
void SpriteRenderer::RenderSetup(const glm::mat4& viewMatrix)
{
	//send shader our view matrix
	m_Shader.setMatrix4fv("view", viewMatrix);
	//set our shader as the currently used shader by opengl
	m_Shader.Bind();
	//bind our "sprite data VAO"
	glBindVertexArray(m_VAOHandle);
}
void SpriteRenderer::DrawSprites()
{
	for (Sprite* s : m_rSprites) {
		DrawSprite(s);
	}
}
void SpriteRenderer::DrawSprite(Sprite* s)
{
	//get a pointer to the sprite's texture
	Texture* texture = GetTexture(s->GetSource());
	//tell texture unit 0 to use the sprite's texture
	texture->Bind(GL_TEXTURE0);
	//pass sprite model matrix to shader
	m_Shader.setMatrix4fv("model", s->GetModelMatrix());
	//draw our sprite
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
Texture* SpriteRenderer::GetTexture(const std::string& src) {
	//first try to return a texture already loaded
	for (Texture* t : m_LoadedTextures) {
		if (t->GetSource() == src)return t;
	}
	//second if not found in loaded textures, load it and return it
	return LoadTexture(src);
}
Texture* SpriteRenderer::LoadTexture(const std::string& src) {
	m_LoadedTextures.push_back(new Texture(src, GL_RGBA));
	return m_LoadedTextures.back();
}