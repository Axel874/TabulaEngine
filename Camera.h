#pragma once
class Camera {
public:
	Camera(glm::vec3 position, glm::vec3 up, float movementSpeed, glm::vec3 direction);

	glm::mat4 GetViewMatrix() const;
	glm::vec3 GetPosition() const;

	void Update(float deltaSeconds);
private:
	float m_TranslateSensitivity;
	glm::vec3 m_Position;
	glm::vec3 m_Direction;
	glm::vec3 m_Up;
	
};