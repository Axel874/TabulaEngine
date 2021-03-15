#pragma once
#include "Core.h"
class Sprite;
class Camera;
class Game {
public:
	Game();
	~Game();

	std::vector<Sprite*>& GetSprites();
	Camera* GetActiveCamera() const;

	void Init();
	void Update(float deltaSeconds);
	void End();
private:
	std::vector<Sprite*> m_pSprites;
	Camera* m_pActiveCamera;
};