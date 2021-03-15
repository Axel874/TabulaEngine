#include "pch.h"
#include "Game.h"
#include "Sprite.h"
#include "Camera.h"
//public
Game::Game() {
	Init();
}
Game::~Game() {
	End();
}

void Game::Init() {
	std::string src = "./resources/images/boxDiffuse.png";
	m_pSprites.push_back(new Sprite(src, glm::vec3(300, 100, 0), glm::vec2(100, 100), glm::vec3(0, 0, 45)));
	m_pSprites.push_back(new Sprite(src, glm::vec3(0, 100, 0), glm::vec2(100, 100)));

	m_pActiveCamera = new Camera(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		500.0f, glm::vec3(0.0f, 0.0f, -1.0f));
}
void Game::Update(float deltaSeconds) {
	m_pSprites[0]->m_Rotation += (glm::vec3(0, 0, 360 * deltaSeconds));
}
void Game::End() {
	for (Sprite* s : m_pSprites)delete s;
	delete m_pActiveCamera;
}

std::vector<Sprite*>& Game::GetSprites() { return m_pSprites; }
Camera* Game::GetActiveCamera() const { return m_pActiveCamera; }