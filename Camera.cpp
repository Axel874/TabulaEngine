#include "pch.h"
#include "Camera.h"
//public
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movementSpeed, float mouseSensitivity)
	: m_Position(position), m_WorldUp(up), m_Yaw(yaw), m_Pitch(pitch),
	m_TranslateSensitivity(movementSpeed), m_RotateSensitivity(mouseSensitivity),
	m_Up(up), m_Direction(glm::vec3(0.0f, 0.0f, -1.0f)), m_WorldDirection(m_Direction)
{
	UpdateVectors();
}

void Camera::ProcessKeyState(const CameraMovement& movement, const float& deltaTime) {
	const float velocity = m_TranslateSensitivity * deltaTime;

	switch (movement) {
	case CameraMovement::FORWARDS:
		m_Position += m_WorldDirection * velocity;
		break;
	case CameraMovement::BACKWARDS:
		m_Position -= m_WorldDirection * velocity;
		break;
	case CameraMovement::RIGHT:
		m_Position += m_Right * velocity;
		break;
	case CameraMovement::LEFT:
		m_Position -= m_Right * velocity;
		break;
	}
}
void Camera::ProcessMouseMovement(const float& dx, const float& dy, const bool& constrainPitch) {
	m_Yaw += dx * m_RotateSensitivity;
	m_Pitch += dy * m_RotateSensitivity;

	if (constrainPitch) {
		if (m_Pitch > 89.0f)m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)m_Pitch = -89.0f;
	}
	UpdateVectors();
}

glm::mat4 Camera::GetViewMatrix() const{
	return glm::lookAt(m_Position, m_Position+m_Direction, m_Up);
}
glm::vec3 Camera::GetPosition() const { return m_Position; }
//private
void Camera::UpdateVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Direction = glm::normalize(front);
	m_Right = glm::normalize(glm::cross(m_Direction, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Direction));
	m_WorldDirection = glm::normalize(glm::cross(m_WorldUp, m_Right));//grounded direction
}