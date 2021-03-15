#pragma once
class Sprite {
public:
	static float s_GLData[24];

	Sprite(
		const std::string& src, const glm::vec3& position,
		const glm::vec2& scale, const glm::vec3& rot = glm::vec3(0)
	);
	Sprite(const std::string& src, float x, float y, float z, float sx, float sy, float rx, float ry, float rz);

	std::string GetSource() const;
	glm::mat4 GetModelMatrix() const;
public:
	glm::vec3 m_Position;
	glm::vec2 m_Size;
	glm::vec3 m_Rotation;
	std::string m_Src;
};