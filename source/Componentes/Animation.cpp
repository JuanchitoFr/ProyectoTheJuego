#include "pch.h"
#include "Animation.h"

//Animation Definition
AnimationComponent::Animation::Animation(Sprite& sprite,Texture& texture, typeAnimation nameAnimation, unsigned int startXrowPos, unsigned int startYcolumnPos, unsigned int endXrowPos, unsigned int endYcolumnPos, unsigned int totalXrow, unsigned int totalYColumn, float switchTime)
	: texture(texture), sprite(sprite), nameAnimation(nameAnimation), switchTime(switchTime)
{
	this->elapsedTime = 0.f;
	this->width = texture.getSize().x / totalXrow;
	this->height = texture.getSize().x / totalYColumn;
	this->startTextureRect = IntRect(startXrowPos * width, startYcolumnPos * height, width, height);
	this->currentRect = startTextureRect;
	this->endTextureRect = IntRect(endXrowPos * width, endYcolumnPos * height, width, height);
	this->sprite.setTextureRect(startTextureRect);
}

AnimationComponent::Animation::~Animation()
{
}

void AnimationComponent::Animation::update(const float& deltaT)
{
	elapsedTime += deltaT ;

	if (elapsedTime >= switchTime) {
		elapsedTime -= switchTime;

		// Obtener el ancho de la textura de la entidad

		if(this->currentRect != this->endTextureRect)
		{
			this->currentRect.left += this->width;
		}
		else //Resetea
		{
			this->currentRect.left = startTextureRect.left;
		}
		// Verificar si se ha alcanzado el final de la fila de sprites
		this->sprite.setTextureRect(currentRect);

	}
}

void AnimationComponent::Animation::reset()
{
	this->elapsedTime = 0.f;
	this->currentRect = this->startTextureRect;
}


typeAnimation& AnimationComponent::Animation::getNameAnimation()
{
	return this->nameAnimation;
}


//AnimationComponent Definition

AnimationComponent::AnimationComponent(Sprite& sprite, Texture& texture) : sprite(sprite), texture(texture)
{
}

AnimationComponent::~AnimationComponent()
{
}


void AnimationComponent::addAnimation(const string animation, Animation& animationType)
{
	this->map.insert(animation, animationType);
}

void AnimationComponent::play(const string animation, const float& deltaTime)
{
	this->map.get(animation).update(deltaTime);
}
