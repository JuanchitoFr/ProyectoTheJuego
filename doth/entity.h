#ifndef ENTITY_H
#define ENTITY_H
#include "entitymethods.h"

class Entity : public EntityMethods
{
	private:
		int hp;
		String name;
		float xPos, yPos;
		float spriteWidht, spriteHeight;
		float speed;
		Texture* entityTexture;
		Sprite* entitySprite;
		
		
	public:
		Entity();
		virtual ~Entity();
		//metodos
		virtual void entityMovement(double deltaTime, float x, float y, float speed) override;
		virtual void render(RenderTarget* objTarget) override;
		virtual void updateTimeInScreen(double deltaT) override;
		virtual void setPosition(float xPos, float yPos) override;
		virtual Vector2f getPosition() const override;
		void createSprite(Texture* spriteTexture);
		


		//Get and set
		Texture* getEntityTexture() const;
		void setEntityTexture(Texture* entityTexture);
		Sprite* getEntitySprite() const;
		void setEntitySprite(Sprite* entitySprite);
		int getHp() const;
		void setHp(const int hp);
		String getName() const;
		void setName(const String name);
		float getSpriteWidht() const;
		void setSpriteWidht(const float spriteWidht);
		float getSpriteHeight() const;
		void setSpriteHeight(const float spriteHeight);
		void setSpeed(const float speed);
		float getSpeed() const;
		float getXpos() const;
		void setXpos(const float xPos);
		float getYpos() const;
		void setYpos(const float yPos);
};
	


#endif // !ENTITY_H

