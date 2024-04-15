#include "pch.h"
#include "../doth/player.h"

Player::Player(Texture* playerTexture = nullptr)
{
	this->createSprite(playerTexture);
}

Player::~Player()
{
}
