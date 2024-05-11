#include "pch.h"
#include "../doth/entity.h"

void Entity::init(int stats[])
{
	if (arrSize > 0)
	{
		coordinates.x = stats[0];
		coordinates.y = stats[1];
		this->stats.x = (int)coordinates.x;
		this->stats.y = (int)coordinates.y;
		this->stats.hp = stats[2];
		this->stats.atkFisico = stats[3];
		this->stats.defMagica = stats[4];
		this->stats.atkMagico = stats[5];
		this->stats.defMagica = stats[6];
		this->stats.velocidad = stats[7];

	}
}

Entity::Entity(Texture* entityTexture = nullptr, float speed = 0.f) : entityTexture(entityTexture), speed(speed)
{
	this->velocity = Vector2f(0.f, 0.f); this->coordinates = Vector2f(0.f, 0.f); this->elapsedT = 0.f; 
	this->entitySprite = nullptr; this->spriteHeight = 0; this->spriteWidth = 0; this->checkDead = true;
	
	/*Tamaño de los array*/
	this->entitySize = 0; this->entityAmount = 0; this->checkSize = 0;

	
	
}
Entity::Entity()
{
	this->elapsedT = 0; this->entityAmount = 0;
	this->entitySize = 0; this->checkSize = 0; 
	this->entitySprite = nullptr; this->entityTexture = nullptr;
	this->spriteHeight = 0; this->spriteWidth = 0;
	this-> checkDead = false;
}

Entity::~Entity()
{
	delete[] this->entitySprite;
	delete[] this->entityTexture;
}

void Entity::entityMovement(float deltaTime, float x, float y)
{
		this->velocity.x = this->speed * x;
		this->velocity.y = this->speed * y;
		this->entitySprite->move(getVelocity() * deltaTime);
	
}



void Entity::render(RenderTarget* objTarget)
{
	if (entitySprite != NULL) {
		objTarget->draw(*this->entitySprite);
	}
		
}

// Anima el sprite, segun el tiempo que se le pase por argumento teniendo en cuenta el deltatime
void Entity::updateSprite(float deltaT, float switchT, int numS)
{
		elapsedT += deltaT;

		if (elapsedT >= switchT) {
			elapsedT -= switchT;
			coordinates.x++;

			if (coordinates.x * 64 >= this->getEntityTexture(numS).getSize().x) {
				coordinates.x = 0;
			}

		}
		this->entitySprite->setTextureRect(IntRect(static_cast<unsigned int>(coordinates.x) * spriteWidth, 
			static_cast<unsigned int>(coordinates.y) * spriteHeight, spriteWidth, spriteHeight));
		
}


/*Crea el sprite de la entidad, esto mediante la textura. Todo sprite, o figura necesita una textura o color para mostrarse*/

void Entity::createSprite(Texture spriteTexture)
{
	std::cout << "Im the create sprite from entity " << std::endl;
	try
	{
		this->entityTexture = &spriteTexture;

		this->entitySprite = new Sprite(*entityTexture);
		
	}
	catch (const std::exception& p)
	{
		std::cout << "The problemas was : " << p.what();
	}
	
}

void Entity::updateCharactState()
{

}

void Entity::addDamage(int damage)
{
	 stats.hp -= damage;
}



//Getters & setters

Texture Entity::getEntityTexture(unsigned int numT) const
{
	return this->entityTexture[numT];
}

Sprite Entity::getEntitySprite(unsigned int numS) const
{
	return this->entitySprite[numS];
}


int Entity::getSpriteWidth() const
{
	return this->spriteWidth;
}

void Entity::setSpriteWidth(unsigned int spriteWidth)
{
	this->spriteWidth = spriteWidth;
}

int Entity::getSpriteHeight() const
{
	return this->spriteHeight;
}

void Entity::setSpriteHeight(unsigned int spriteHeight)
{
	this->spriteHeight = spriteHeight;
}

unsigned int Entity::getEntityCount()
{
	return entityAmount;
}

int Entity::getHp()
{
	return stats.hp;
}

int Entity::getDefMagica()
{
	return stats.defFisica;
}

int Entity::getDefFisica()
{
	return stats.defFisica;
}

int Entity::getAtkFisico()
{
	return stats.atkFisico;
}

int Entity::getAtkMagico()
{
	return stats.atkMagico;
}

int Entity::getVelocidad()
{
	return stats.velocidad;
}

IpAddress Entity::getIp()
{
	return ip;
}

Estadisticas* Entity::estadisticas()
{
	return &stats;
}

bool Entity::isAlive()
{
	if(stats.hp = 0)
	{
		return false;
	}
	else {
		return true;
	}
}


unsigned int Entity::getEntitySize()
{
	return entitySize;
}

void Entity::setEntityAnimation(float x, float y)
{
	this->velocity.x = x;
	this->velocity.y = y;
}

Vector2f Entity::getEntityMovement()
{
	return this->velocity;
}

void Entity::setPosition(float xPos, float yPos)
{

	this->entitySprite->setPosition(xPos, yPos);
}


Vector2f Entity::getPosition()
{
	return this->entitySprite->getPosition();
}

void Entity::setSpeed(float speed)
{
	this->speed = speed;
}
float Entity::getSpeed() const {
	return this->speed;
}

Vector2f Entity::getVelocity()
{
	return velocity;
}

Packet& operator<<(Packet& packet, Entity& entity)
{
	return packet
		<< entity.coordinates.x
		<< entity.coordinates.y
		<< entity.stats.hp
		<< entity.stats.atkFisico
		<< entity.stats.defFisica
		<< entity.stats.atkMagico
		<< entity.stats.defMagica
		<< entity.stats.velocidad;
	
}

Packet& operator>>(Packet& packet, Entity& entity)
{
	return packet
		>> entity.coordinates.x
		>> entity.coordinates.y
		>> entity.stats.hp
		>> entity.stats.atkFisico
		>> entity.stats.defFisica
		>> entity.stats.atkMagico
		>> entity.stats.defMagica
		>> entity.stats.velocidad;
}
