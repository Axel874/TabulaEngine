#include "pch.h"
#include "Sprite.h"
//public
Sprite::Sprite(const std::string& src, const glm::vec3& position, const glm::vec2& dimensions)
	: m_Dimensions(dimensions), m_Src(src), m_Position(position)
{
	UpdateVertexData();
}
Sprite::Sprite(const std::string& src, float x, float y, float z, float w, float h)
	: Sprite(src,glm::vec3(x,y,z), glm::vec2(w,h))
{}

float* Sprite::GetVertexData() {
	return m_VertexData;
}
std::string Sprite::GetSource() const {
	return m_Src;
}
//protected
void Sprite::UpdateVertexData()
{
	//calculate data to be passed to shader beforehand to save frame time
	const glm::vec2& dm = m_Dimensions;
	float data[24] = {
		// positions          // tex coords 
		//x       y        u      v
		0.0f,    0.0f,    0.0f,  0.0f,	//bottom left
		0.0f,    dm.y,    0.0f,  1.0f,	//top left
		dm.x,    dm.y,    1.0f,  1.0f,	//top right

		0.0f,    0.0f,    0.0f,  0.0f,	//bottom left
		dm.x,    dm.y,    1.0f,  1.0f,	//top right
		dm.x,    0.0f,    1.0f,  0.0f,	//bottom right
	};

	std::copy(data, data + 24, m_VertexData);
}
