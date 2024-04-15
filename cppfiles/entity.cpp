#include "pch.h"
#include "../doth/entity.h"

Entity::Entity()
{
	initVariables();
	this->entityTexture = NULL; this->entitySprite = NULL;
}

Entity::~Entity()
{
	delete entitySprite;
}

void Entity::render(RenderTarget* drawObj)
{

}

void Entity::run()
{
}

void Entity::createSprite(Texture* entityTexture)
{
	this->entityTexture = entityTexture;
	this->entitySprite = new Sprite(*entityTexture);
	this->entitySprite->setScale(spriteWidht,spriteHeight);
}

void Entity::initVariables()
{
	this->hp = 0; this->spriteHeight = 0.f; this->spriteWidht = 0.f;

}

Texture* Entity::getEntityTexture()
{
	return this->entityTexture;
}

void Entity::setEntityTexture(Texture* entityTexture)
{
	entityTexture = entityTexture;
}

Sprite* Entity::getEntitySprite()
{
	return this->entitySprite;
}

void Entity::setEntitySprite(Sprite* entitySprite)
{
	this->entitySprite = entitySprite;
}

int Entity::getHp()
{
	return this->hp;
}

void Entity::setHp(int hp)
{
	this->hp = hp;
}

String Entity::getName()
{
	return this->name;
}

void Entity::setName(String name)
{
	this->name = name;
}

float Entity::getSpriteWidht()
{
	return this->spriteWidht;
}

void Entity::setSpriteWidht(float spriteWidht)
{
	this->spriteWidht = spriteWidht;
}

float Entity::getSpriteHeight()
{
	return this->spriteHeight;
}

void Entity::setSpriteHeight(float spriteHeight)
{
	this->spriteHeight = spriteHeight;
}

