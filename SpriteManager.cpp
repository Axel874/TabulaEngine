#include "pch.h"
#include "SpriteManager.h"
#include "Sprite.h"

//vertex/uv data for drawing a basic sprite in opengl
float SpriteManager::s_SpriteData[24] = {
	// positions      // tex coords 
	//x       y        u      v
	0.0f,    0.0f,    0.0f,  0.0f,	//bottom left
	0.0f,    1.0f,    0.0f,  1.0f,	//top left
	1.0f,    1.0f,    1.0f,  1.0f,	//top right

	0.0f,    0.0f,    0.0f,  0.0f,	//bottom left
	1.0f,    1.0f,    1.0f,  1.0f,	//top right
	1.0f,    0.0f,    1.0f,  0.0f,	//bottom right
};

SpriteManager::SpriteManager(std::vector<Sprite*>& managedSprites)
: m_rSprites(managedSprites){}
SpriteManager::~SpriteManager(){}

void SpriteManager::SetManagedSprites(std::vector<Sprite*>& sprites) { m_rSprites = sprites; }
void SpriteManager::DrawSprites() {
	for (Sprite* s : m_rSprites) {
		//get a handle of the textureunit the sprite's texture is bound to
		GLuint handle = GetTextureHandle(s->GetSource());
		if(handle == -1)
	}
}
GLuint SpriteManager::GetTextureHandle(const std::string& src) const{
	for (TextureInfo t : m_TextureInfo) {
		if (t.src == src)return t.textureUnitHandle;
	}
	return -1;
}
GLuint SpriteManager::LoadTexture(const std::string& src) {
	
}