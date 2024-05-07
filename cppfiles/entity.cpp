#include "pch.h"
#include "../doth/entity.h"


Entity::Entity(Texture* entityTexture = nullptr, float speed = 0.f) : entityTexture(entityTexture), speed(speed)
{
	this->velocity = Vector2f(0.f, 0.f); this->coordinates = Vector2f(0.f, 0.f); this->elapsedT = 0.f; 
	this->entitySprite = NULL; this->spriteHeight = 0; this->spriteWidth = 0;
	
	/*Tamaño de los array*/
	this->entitySize = 0; this->entityAmount = 0; this->checkSize = 0;

	
	
}
Entity::Entity()
{
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
		this->entitySize += entityAmount;
		
		if (entitySize == checkSize) 
		{
			Texture* newArrTexture = new Texture[entitySize]();
			Sprite* newArrSprite = new Sprite[entitySize]();
			for (unsigned int i = 0; i < entitySize - 1; i++)
			{
				newArrTexture[i] = entityTexture[i];
				newArrSprite[i].setTexture(newArrTexture[i]);
			}
			for (unsigned int i = entitySize; i <= entitySize; i++)
			{
				newArrTexture[i] = spriteTexture;
				newArrSprite[i].setTexture(newArrTexture[i]);
			}
			this->entityTexture = newArrTexture;
			this->entitySprite = newArrSprite;
			delete[] newArrTexture, newArrSprite;
		}
		
		if (entityAmount == 0) {
			this->entityAmount++;
		}
		else {
			this->entityAmount = entityAmount;
			this->checkSize++;
		}
		
	}
	catch (const std::exception& p)
	{
		std::cout << "The problemas was : " << p.what();
	}
	
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







