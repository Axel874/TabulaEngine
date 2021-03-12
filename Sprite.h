#pragma once
class Sprite {
public:
	Sprite(const std::string& src, const glm::vec3& position, const glm::vec2& dimensions);
	Sprite(const std::string& src, float x, float y, float z, float w, float h);

	float* GetVertexData();
	std::string GetSource() const;
protected:
	glm::vec3 m_Position;
private:
	float m_VertexData[24];
	std::string m_Src;
	glm::vec2 m_Dimensions;

	void UpdateVertexData();
};