#include "pch.h"
#include "Camera.h"
//public
Camera::Camera(glm::vec3 position, glm::vec3 up, float movementSpeed, glm::vec3 direction)
	: m_Position(position),
	m_Sensitivity(movementSpeed),
	m_Up(up),
	m_Direction(direction)
{
}

void Camera::Update(float deltaSeconds){
	const Uint8* s = SDL_GetKeyboardState(NULL);
	if (s[SDL_SCANCODE_W])m_Position.y += deltaSeconds * m_Sensitivity;
	if (s[SDL_SCANCODE_S])m_Position.y -= deltaSeconds * m_Sensitivity;
	if (s[SDL_SCANCODE_A])m_Position.x -= deltaSeconds * m_Sensitivity;
	if (s[SDL_SCANCODE_D])m_Position.x += deltaSeconds * m_Sensitivity;
}
glm::mat4 Camera::GetViewMatrix() const{
	return glm::lookAt(m_Position, m_Position+m_Direction, m_Up);
}
glm::vec3 Camera::GetPosition() const { return m_Position; }