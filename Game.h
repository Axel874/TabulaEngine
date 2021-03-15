#pragma once
#include "Sprite.h"
#include "Core.h"
class Game {
public:
	Game();
	~Game();

	std::vector<Sprite>& GetSprites();
	void Init();
	void Update(float deltaSeconds);
	void End();
private:
	std::vector<Sprite> m_Sprites;
};