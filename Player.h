#pragma once
#include "Sprite.h"
class Player : public Sprite{
public:
	Player(const glm::vec3& position);
	~Player();
private:
	static char s_TextureSource[64];
	static glm::vec2 s_TextureDimensions;
};