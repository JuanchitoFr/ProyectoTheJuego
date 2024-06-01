#include "pch.h"
#include "Animation.h"

//Animation Definition
AnimationComponent::Animation::Animation(Sprite& sprite,Texture& texture, unsigned int startXrowPos, unsigned int startYcolumnPos, unsigned int endXrowPos, unsigned int endYcolumnPos, unsigned int totalXrow, unsigned int totalYColumn, float switchTime)
	: texture(texture), sprite(sprite), switchTime(switchTime) , finished(false)
{
	this->elapsedTime = 0.f;
	this->width = texture.getSize().x / totalYColumn;
	this->height = texture.getSize().y / totalXrow;
	this->startTextureRect = IntRect(startXrowPos * width, startYcolumnPos * height, width, height);
	this->currentRect = startTextureRect;
	this->endTextureRect = IntRect(endXrowPos * width, endYcolumnPos * height, width, height);
	this->sprite.setTexture(texture, true);
	this->sprite.setTextureRect(startTextureRect);

}

AnimationComponent::Animation::~Animation()
{
	
	
}

void AnimationComponent::Animation::update(const float& deltaT)
{
	elapsedTime += deltaT;
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
			finished = true;
		}
		// Verificar si se ha alcanzado el final de la fila de sprites
		this->sprite.setTextureRect(currentRect);

	}
}


void AnimationComponent::Animation::reset()
{
	this->elapsedTime = 0.f;
	this->currentRect = this->startTextureRect;
	this->finished = false;
}

bool AnimationComponent::Animation::isFinished() const
{
	return this->finished;
}


//AnimationComponent Definition

AnimationComponent::AnimationComponent(Sprite& sprite, Texture& texture) : sprite(sprite), texture(texture), lastAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto&& map : animations)
	{
		delete map.second;
	}
}

void AnimationComponent::addAnimation(const string nameOfAnimation,unsigned int startXrowPos, 
	unsigned int startYcolumnPos, unsigned int endXrowPos, unsigned int endYcolumnPos, unsigned int totalXrow, unsigned int totalYColumn, float switchTime)
{
	this->animations[nameOfAnimation] = new Animation(sprite, texture, startXrowPos, startYcolumnPos, endXrowPos, endYcolumnPos, totalXrow, totalYColumn, switchTime);
}

void AnimationComponent::play(const string nameOfAnimation, const float& deltaTime)
{
	if (this->lastAnimation != this->animations[nameOfAnimation])
	{
		// Si hay una animación en curso, reiníciala
		if (this->lastAnimation != nullptr)
		{
			this->lastAnimation->reset();
		}

		// Cambia a la nueva animación
		this->lastAnimation = this->animations[nameOfAnimation];
	}

	// Actualiza la animación actual
	this->lastAnimation->update(deltaTime);
}

void AnimationComponent::stop()
{
	if(this->lastAnimation != nullptr)
	{
		this->lastAnimation->reset();
		this->lastAnimation = nullptr;
	}
}







