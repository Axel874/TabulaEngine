#pragma once
class Sprite {
public:
	Sprite(const std::string& src, const glm::vec3& position, const glm::vec2& scale);
	Sprite(const std::string& src, float x, float y, float z, float sx, float sy);
	std::string GetSource() const;
	glm::vec2 GetSize() const;
	glm::vec3 getPosition() const;
private:
	glm::vec3 m_Position;
	glm::vec2 m_Size;
	std::string m_Src;
};