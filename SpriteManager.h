#pragma once
class Sprite;
class SpriteManager {
public:
	SpriteManager(std::vector<Sprite*>& managedSprites);
	~SpriteManager();

	void SetManagedSprites(std::vector<Sprite*>& sprites);
	void DrawSprites();
private:
	//struct that stores what texture unit a certain texture is loaded in to
	struct TextureInfo {
		std::string src;
		GLuint textureUnitHandle;
	};

	static float s_SpriteData[24];
	std::vector<Sprite*>& m_rSprites;
	std::vector<TextureInfo> m_TextureInfo;

	GLuint GetTextureHandle(const std::string& src) const;
	GLuint LoadTexture(const std::string& src);
};