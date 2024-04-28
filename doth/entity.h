#ifndef ENTITY_H
#define ENTITY_H
#include "entitymethods.h"


class Entity : public EntityMethods
{
	protected:
		//Movimiento
		float speed;
		Vector2f velocity;
		Vector2i coordinates;
		//Gestion del sprite de la entidad
		int spriteWidth, spriteHeight;
		Texture* entityTexture;
		Sprite* entitySprite;
		float elapsedT;
		bool isMoving;

		
		
	public:
		Entity(int spriteWidth, int spriteHeight, Texture* entityTexture,
			Sprite* entitySprite, float speed);
		virtual ~Entity();
		//Movimiento de la entidad
		virtual void entityMovement(float deltaTime, float x, float y) override;
		void setEntityAnimation(float x, float y);
		Vector2f getEntityMovement();
		//Gestion del sprite de la entidad
		virtual void render(RenderTarget* objTarget);
		virtual void updateSprite(float deltaT, float switchT) override;
		virtual void createSprite(Texture* spriteTexture);
		


		//Get and set
		virtual void setPosition(float xPos, float yPos) override;
		virtual Vector2f getPosition() override;
		void setSpeed(float speed);
		float getSpeed() const;
		Vector2f getVelocity();
		Texture* getEntityTexture() const;
		void setEntityTexture(Texture* entityTexture);
		Sprite* getEntitySprite() const;
		void setEntitySprite(Sprite* entitySprite);
		int getSpriteWidth() const;
		void setSpriteWidth(int spriteWidth);
		int getSpriteHeight() const;
		void setSpriteHeight(int spriteHeight);
		int getCoordinatesX();
		int getCoordinatesY();
		void setCoordinatesX(int x);
		void setCoordinatesY(int y);
		bool getIsMoving();
		void setIsMoving(bool isMoving);
		
		
};
	


#endif // !ENTITY_H

