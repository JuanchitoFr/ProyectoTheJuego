#include "pch.h"
#include "Animation.h"


AnimationComponent::Animation::Animation(Sprite& sprite,Texture& texture, typeAnimation nameAnimation, unsigned int startXrowPos, unsigned int startYcolumnPos, unsigned int endXrowPos, unsigned int endYcolumnPos, unsigned int totalXrow, unsigned int totalYColumn, float switchTime)
	: texture(texture), sprite(sprite), nameAnimation(nameAnimation), switchTime(switchTime)
{
	this->elapsedTime = 0.f;
	this->width = texture.getSize().x / totalXrow;
	this->height = texture.getSize().x / totalYColumn;
	this->startTextureRect = IntRect(startXrowPos, startYcolumnPos, width, height);
	this->currentRect = startTextureRect;
	this->endTextureRect = IntRect(endXrowPos, endYcolumnPos, width, height);
	this->sprite.setTextureRect(startTextureRect);
}

AnimationComponent::Animation::~Animation()
{
}

void AnimationComponent::Animation::update(float deltaT)
{
}

void AnimationComponent::Animation::play()
{
}

typeAnimation& AnimationComponent::Animation::getNameAnimation()
{
	return this->nameAnimation;
}
