#include "pch.h"
#include "Player.h"

char Player::s_TextureSource[64] = "./resources/images/skul/Idle_0.png";
glm::vec2 Player::s_TextureDimensions = glm::vec2(500, 500);

Player::Player(const glm::vec3& position) : Sprite(std::string(s_TextureSource), position,s_TextureDimensions) {}
Player::~Player() {}