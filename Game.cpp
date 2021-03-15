#include "pch.h"
#include "Game.h"
//public
Game::Game(){
	Init();
} 
Game::~Game(){
	End();
}

void Game::Init() {
	std::string src = "./resources/images/boxDiffuse.png";
	m_Sprites.push_back(Sprite(src, glm::vec3(300, 100, 0), glm::vec2(100, 100), glm::vec3(0,0,45)));
	m_Sprites.push_back(Sprite(src, glm::vec3(0, 100, 0), glm::vec2(100, 100)));
}
void Game::Update(float deltaSeconds) {
	m_Sprites[0].m_Rotation += (glm::vec3(0, 0, 360*deltaSeconds));
}
void Game::End() {

}

std::vector<Sprite>& Game::GetSprites() { return m_Sprites; }
