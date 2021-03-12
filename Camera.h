#pragma once
enum class CameraMovement {
	UPWARDS,
	DOWNWARDS,
	LEFT,
	RIGHT
};

class Camera {
public:
	Camera(glm::vec3 position, glm::vec3 up, float movementSpeed, glm::vec3 direction);
	
	void ProcessKeyState(const CameraMovement& movement, const float& deltaTime);

	glm::mat4 GetViewMatrix() const;
	glm::vec3 GetPosition() const;
private:
	float m_TranslateSensitivity;
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Up;
	
};