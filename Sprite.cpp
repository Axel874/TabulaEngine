#include "pch.h"
#include "Sprite.h"

//public//
//static
//vertex/uv data for drawing a basic sprite in opengl
float Sprite::s_GLData[24] = {
	// positions      // tex coords 
	//x       y        u      v
	0.0f,    0.0f,    0.0f,  0.0f,	//bottom left
	0.0f,    1.0f,    0.0f,  1.0f,	//top left
	1.0f,    1.0f,    1.0f,  1.0f,	//top right

	0.0f,    0.0f,    0.0f,  0.0f,	//bottom left
	1.0f,    1.0f,    1.0f,  1.0f,	//top right
	1.0f,    0.0f,    1.0f,  0.0f,	//bottom right
};

//dynamic
Sprite::Sprite(
	const std::string& src, const glm::vec3& position,
	const glm::vec2& scale, const glm::vec3& rot
)
	: m_Size(scale), m_Src(src), m_Position(position), m_Rotation(rot)
{
}
Sprite::Sprite(
	const std::string& src, float x, float y, float z,
	float sx, float sy, float rx, float ry, float rz
)
	: Sprite(src, glm::vec3(x, y, z), glm::vec2(sx, sy), glm::vec3(rx, ry, rz))
{}
Sprite::~Sprite() {}

void Sprite::Update(float deltaSeconds) {}

void Sprite::OnKeyDown(const SDL_KeyboardEvent& e) {}
void Sprite::OnKeyUp(const SDL_KeyboardEvent& e) {}

void Sprite::OnControllerAxisMotion(const SDL_ControllerAxisEvent& e) {}
void Sprite::onControllerKeyDown(const SDL_ControllerButtonEvent& e) {}
void Sprite::onControllerKeyUp(const SDL_ControllerButtonEvent& e) {}

void Sprite::onMouseMotion(const SDL_MouseMotionEvent& e) {}
void Sprite::onMouseButtonDown(const SDL_MouseButtonEvent& e) {}
void Sprite::onMouseButtonUp(const SDL_MouseButtonEvent& e) {}
void Sprite::onMouseWheel(const SDL_MouseWheelEvent& e) {}

std::string Sprite::GetSource() const { return m_Src; }
glm::mat4 Sprite::GetModelMatrix() const {
	//calculate model matrix//

	//calculate half size
	const glm::vec2 halfSize = m_Size / 2.0f;
	//start with identity matrix
	glm::mat4 model = glm::mat4(1.0f);
	//matrix multiplications from bottom to top !
	//apply translation matrix (5)
	model = glm::translate(model, m_Position);
	//reverse trasnform done to rotate around midpoint (4)
	model = glm::translate(model, glm::vec3(halfSize, 1));
	//apply rotations (3)
	model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	//offset model matrix to rotate around midpoint (2)
	model = glm::translate(model, glm::vec3(-halfSize, 1));
	//apply scale (1)
	model = glm::scale(model, glm::vec3(m_Size.x, m_Size.y, 1));
	return model;
}