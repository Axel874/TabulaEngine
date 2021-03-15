#include "pch.h"
#include "Game.h"
#include "Sprite.h"
#include "Camera.h"
#include "Player.h"
//public
Game::Game() : m_Quitflag(false) {
	std::string src = "./resources/images/boxDiffuse.png";
	m_pSprites.push_back(new Sprite(src, glm::vec3(300, 100, 0), glm::vec2(100, 100), glm::vec3(0, 0, 45)));
	m_pSprites.push_back(new Sprite(src, glm::vec3(0, 100, 0), glm::vec2(100, 100)));
	m_pSprites.push_back(new Player(glm::vec3(50, 50, -1)));

	m_pActiveCamera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 500.0f, glm::vec3(0.0f, 0.0f, -1.0f));
}
Game::~Game() {
	for (Sprite* s : m_pSprites)delete s;
	delete m_pActiveCamera;
}

void Game::Update(float deltaSeconds) {
	m_pSprites[0]->m_Rotation += (glm::vec3(0, 0, 360 * deltaSeconds));
	for (Sprite* s : m_pSprites) { s->Update(deltaSeconds); }
	m_pActiveCamera->Update(deltaSeconds);
}

void Game::OnKeyDown(const SDL_KeyboardEvent& e){
	for (Sprite* s : m_pSprites) { s->OnKeyDown(e); }
}
void Game::OnKeyUp(const SDL_KeyboardEvent& e){
	for (Sprite* s : m_pSprites) { s->OnKeyUp(e); }
}

void Game::OnControllerAxisMotion(const SDL_ControllerAxisEvent& e){
	for (Sprite* s : m_pSprites) { s->OnControllerAxisMotion(e); }
}
void Game::onControllerKeyDown(const SDL_ControllerButtonEvent& e){
	for (Sprite* s : m_pSprites) { s->onControllerKeyDown(e); }
}
void Game::onControllerKeyUp(const SDL_ControllerButtonEvent& e){
	for (Sprite* s : m_pSprites) { s->onControllerKeyUp(e); }
}
	 
void Game::onMouseMotion(const SDL_MouseMotionEvent& e){
	for (Sprite* s : m_pSprites) { s->onMouseMotion(e); }
}
void Game::onMouseButtonDown(const SDL_MouseButtonEvent& e){
	for (Sprite* s : m_pSprites) { s->onMouseButtonDown(e); }
}
void Game::onMouseButtonUp(const SDL_MouseButtonEvent& e){
	for (Sprite* s : m_pSprites) { s->onMouseButtonUp(e); }
}
void Game::onMouseWheel(const SDL_MouseWheelEvent& e){
	for (Sprite* s : m_pSprites) { s->onMouseWheel(e); }
}

std::vector<Sprite*>& Game::GetSprites() { return m_pSprites; }
Camera* Game::GetActiveCamera() const { return m_pActiveCamera; }
bool Game::ShouldQuit() const { return m_Quitflag; }