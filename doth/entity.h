#ifndef ENTITY_H
#define ENTITY_H
#include "entitymethods.h"


class Entity : public EntityMethods
{
	protected:
		//Movimiento
		float speed;
		Vector2f velocity;
		Vector2f coordinates;
		//Gestion del sprite de la entidad
		unsigned int entitySize, entityAmount, checkSize;
		unsigned int spriteWidth, spriteHeight;
		Texture* entityTexture;
		Sprite* entitySprite;
		float elapsedT;

	public:
		Entity(Texture* entityTexture, float speed);
		Entity();
		virtual ~Entity();
		
		// METODOS
		/*Movimiento y posicion de la entidad*/
		virtual void setPosition(float xPos, float yPos) override;
		virtual Vector2f getPosition() override;
		void setSpeed(float speed);
		float getSpeed() const;
		Vector2f getVelocity();
		virtual void entityMovement(float deltaTime, float x, float y) override;
		void setEntityAnimation(float x, float y);
		Vector2f getEntityMovement();

		/*Gestion del sprite de la entidad*/
		virtual void render(RenderTarget* objTarget);
		virtual void updateSprite(float deltaT, float switchT, int numS) override;
		virtual void createSprite(Texture spriteTexture);
		
		//Getters and setters
		/*Gestion de la textura y el sprite*/
		Texture getEntityTexture(unsigned int numT) const;
		Sprite getEntitySprite(unsigned int numS) const;
		int getSpriteWidth() const;
		void setSpriteWidth(unsigned int spriteWidth);
		int getSpriteHeight() const;
		void setSpriteHeight(unsigned int spriteHeight);
		unsigned int getEntitySize();
		unsigned int getEntityCount();
		
		

		
		
};
	


#endif // !ENTITY_H

