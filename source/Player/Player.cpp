#include "pch.h"
#include "Player.h"

Player::Player(Texture* playerTexture, float speed,
	unsigned int xTextureRectPos, unsigned int yTextureRectPos)
{
	 this->createSprite(playerTexture);
	 this->spriteWidth = (float)playerTexture->getSize().x / xTextureRectPos;
	 this->spriteHeight = (float)playerTexture->getSize().y / yTextureRectPos;

	 /*textureRect.width = entityTexture->getSize().x / imageCount.x;
	 std::cout << "Texture rect width" << textureRect.width << std::endl;
	 textureRect.width = entityTexture->getSize().y / imageCount.y;
	 std::cout << "Texture rect height " << textureRect.width << std::endl;*/
	 stats.x = 0; stats.y = 0; stats.hp = 0; stats.atkFisico = 0; stats.defFisica = 0; stats.atkMagico = 0; stats.defMagica = 0; stats.velocidad = 0;
	 
}

Player::~Player()
{
}

void Player::setTextureRect(unsigned int xCount, unsigned int yCount, unsigned int columns, unsigned int rows)
{
	this->coordinates.x = (float)xCount;
	this->coordinates.y = (float)yCount;
	this->spriteWidth = ((float)this->entityTexture->getSize().x) / (float)columns;
	this->spriteHeight = (float)this->entityTexture->getSize().y / (float)rows;
	cout << spriteWidth << "XDpe" << endl;
	cout << spriteHeight << "XDhe" << endl;
	this->entitySprite->setTextureRect(IntRect(xCount, yCount, static_cast<int>(spriteWidth), static_cast<int>(spriteHeight)));

	
} 

void Player::addDamage(int damage)
{
	stats.hp -= damage;
}

void Player::asignarEstadisticas(estadisticas& stats, int hpPercent, int defMagicaPercent, int defFisicaPercent, int atkFisicoPercent, int atkMagicoPercent, int velocidadPercent)
{
	// Calcula los puntos para cada estadística basados en los porcentajes
	stats.hp = (totalPoints * hpPercent / 100);
	stats.defMagica = totalPoints * defMagicaPercent / 100;
	stats.defFisica = totalPoints * defFisicaPercent / 100;
	stats.atkFisico = totalPoints * atkFisicoPercent / 100;
	stats.atkMagico = totalPoints * atkMagicoPercent / 100;
	stats.velocidad = totalPoints * velocidadPercent / 100;
}

void Player::variacionStats()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(-10, 10);
	cout << dis(gen);
	stats.hp = static_cast<int>(stats.hp * (1.0 + static_cast<double>(dis(gen)) / 100.0));
	stats.defMagica = static_cast<int>(stats.defMagica * (1.f + static_cast<float>(dis(gen)) / 100.f));
	stats.defFisica = static_cast<int>(stats.defFisica * (1.f + static_cast<float>(dis(gen)) / 100.f));
	stats.atkFisico = static_cast<int>(stats.atkFisico * (1.f + static_cast<float>(dis(gen)) / 100.f));
	stats.atkMagico = static_cast<int>(stats.atkMagico * (1.f + static_cast<float>(dis(gen)) / 100.f));
	stats.velocidad = static_cast<int>(stats.velocidad * (1.f + static_cast<float>(dis(gen)) / 100.f));
	
}


void Player::updateSprite(float deltaT, float switchT)
{
	elapsedT += deltaT;

	if (elapsedT >= switchT) {
		elapsedT -= switchT;

		coordinates.x++;
		// Obtener el ancho de la textura de la entidad
		unsigned int textureWidth = this->getEntityTexture()->getSize().x;

		// Verificar si se ha alcanzado el final de la fila de sprites
		if (coordinates.x * spriteWidth + 11.f >= textureWidth) {
			coordinates.x = 0; // Reiniciar a la primera columna
		}

	}
	this->entitySprite->setTextureRect(IntRect(static_cast<unsigned int>(coordinates.x) * static_cast<unsigned int>(spriteWidth),
		static_cast<unsigned int>(coordinates.y) * static_cast<unsigned int>(spriteHeight), static_cast<unsigned int>(spriteWidth), static_cast<unsigned int>(spriteHeight)));
}







/*void Player::setPosition(float xPos, float yPos)
{
	this->getEntitySprite()->setPosition(xPos, yPos);
}

Vector2f Player::getPosition() const
{
	return this->getEntitySprite()->getPosition();
}*/
