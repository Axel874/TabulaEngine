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
	bool ShouldQuit() const;

	void Update(float deltaSeconds);

	void OnKeyDown(const SDL_KeyboardEvent& e);
	void OnKeyUp(const SDL_KeyboardEvent& e);

	void OnControllerAxisMotion(const SDL_ControllerAxisEvent& e);
	void onControllerKeyDown(const SDL_ControllerButtonEvent& e);
	void onControllerKeyUp(const SDL_ControllerButtonEvent& e);

	void onMouseMotion(const SDL_MouseMotionEvent& e);
	void onMouseButtonDown(const SDL_MouseButtonEvent& e);
	void onMouseButtonUp(const SDL_MouseButtonEvent& e);
	void onMouseWheel(const SDL_MouseWheelEvent& e);
private:
	std::vector<Sprite*> m_pSprites;
	Camera* m_pActiveCamera;
	bool m_Quitflag;
};