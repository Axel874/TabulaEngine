#pragma once
class Sprite {
public:
	static float s_GLData[24];

	Sprite(
		const std::string& src, const glm::vec3& position,
		const glm::vec2& scale, const glm::vec3& rot = glm::vec3(0)
	);
	Sprite(const std::string& src, float x, float y, float z, float sx, float sy, float rx, float ry, float rz);
	virtual ~Sprite();

	virtual void Update(float deltaSeconds);

	virtual void OnKeyDown(const SDL_KeyboardEvent& e);
	virtual void OnKeyUp(const SDL_KeyboardEvent& e);

	virtual void OnControllerAxisMotion(const SDL_ControllerAxisEvent& e);
	virtual void onControllerKeyDown(const SDL_ControllerButtonEvent& e);
	virtual void onControllerKeyUp(const SDL_ControllerButtonEvent& e);

	virtual void onMouseMotion(const SDL_MouseMotionEvent& e);
	virtual void onMouseButtonDown(const SDL_MouseButtonEvent& e);
	virtual void onMouseButtonUp(const SDL_MouseButtonEvent& e);
	virtual void onMouseWheel(const SDL_MouseWheelEvent& e);

	std::string GetSource() const;
	glm::mat4 GetModelMatrix() const;
public:
	glm::vec3 m_Position;
	glm::vec2 m_Size;
	glm::vec3 m_Rotation;
	std::string m_Src;
};