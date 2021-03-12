#include "pch.h"
#include "Camera.h"
//public
Camera::Camera(glm::vec3 position, glm::vec3 up, float movementSpeed, glm::vec3 direction)
	: m_Position(position),
	m_TranslateSensitivity(movementSpeed),
	m_Up(up),
	m_Direction(direction)
{
}

void Camera::ProcessKeyState(const CameraMovement& movement, const float& deltaTime) {
	const float velocity = m_TranslateSensitivity * deltaTime;

	switch (movement) {
	case CameraMovement::UPWARDS:
		m_Position.y += velocity;
		break;
	case CameraMovement::DOWNWARDS:
		m_Position.y -=  velocity;
		break;
	case CameraMovement::RIGHT:
		m_Position.x +=  velocity;
		break;
	case CameraMovement::LEFT:
		m_Position.x -= velocity;
		break;
	}
}

glm::mat4 Camera::GetViewMatrix() const{
	return glm::lookAt(m_Position, m_Position+m_Direction, m_Up);
}
glm::vec3 Camera::GetPosition() const { return m_Position; }