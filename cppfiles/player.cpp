#include "pch.h"
#include "../doth/player.h"

Player::Player(Texture* playerTexture = nullptr, float speed = 0.f,
	unsigned int xTextureRectPos = 0, unsigned int yTextureRectPos = 0) : Entity(playerTexture,speed)
{
	 this->createSprite(*playerTexture);
	 /*textureRect.width = entityTexture->getSize().x / imageCount.x;
	 std::cout << "Texture rect width" << textureRect.width << std::endl;
	 textureRect.width = entityTexture->getSize().y / imageCount.y;
	 std::cout << "Texture rect height " << textureRect.width << std::endl;*/
	 this->entitySprite->setTextureRect(IntRect(xTextureRectPos, yTextureRectPos, spriteWidth, spriteHeight));
	 stats.x = 0; stats.y = 0; stats.hp = 0; stats.atkFisico = 0; stats.defFisica = 0; stats.atkMagico = 0; stats.defMagica = 0; stats.velocidad = 0;
	 
}

Player::Player()
{

}
 
Player::~Player()
{
}


void Player::asignarEstadisticas(estadisticas& stats, int hpPercent, int defMagicaPercent,
	int defFisicaPercent, int atkFisicoPercent, int atkMagicoPercent, int velocidadPercent) {
	Entity::asignarEstadisticas(stats, hpPercent, defMagicaPercent, defFisicaPercent, atkFisicoPercent, atkFisicoPercent, velocidadPercent);
}



/*void Player::setPosition(float xPos, float yPos)
{
	this->getEntitySprite()->setPosition(xPos, yPos);
}

Vector2f Player::getPosition() const
{
	return this->getEntitySprite()->getPosition();
}*/
