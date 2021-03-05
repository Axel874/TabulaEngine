#pragma once
enum class CameraMovement {
	FORWARDS,
	BACKWARDS,
	LEFT,
	RIGHT
};

class Camera {
public:
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float movementSpeed, float mouseSensitivity);
	
	void ProcessKeyState(const CameraMovement& movement, const float& deltaTime);
	void ProcessMouseMovement(const float& dx, const float& dy, const bool& constrainPitch);

	glm::mat4 GetViewMatrix() const;
	glm::vec3 GetPosition() const;
private:
	float m_Yaw, m_Pitch;
	float m_TranslateSensitivity, m_RotateSensitivity;
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;
	glm::vec3 m_WorldDirection;
	
	void UpdateVectors();
};