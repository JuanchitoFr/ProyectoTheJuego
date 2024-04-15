#ifndef ENTITY_H
#define ENTITY_H
#include "gamemethods.h"

class Entity : public GameMethods
{
	private:
		int hp;
		String name;
		float spriteWidht;
		float spriteHeight;
		Texture* entityTexture;
		Sprite* entitySprite;
		
	public:
		Entity();
		virtual ~Entity();
		//metodos
		void render(RenderTarget* drawObj) override;
		void run() override;
		void createSprite(Texture* entityTexture);
		void initVariables();

		//Get and set
		Texture* getEntityTexture();
		void setEntityTexture(Texture* entityTexture);
		Sprite* getEntitySprite();
		void setEntitySprite(Sprite* entitySprite);
		int getHp();
		void setHp(int hp);
		String getName();
		void setName(String name);
		float getSpriteWidht();
		void setSpriteWidht(float spriteWidht);
		float getSpriteHeight();
		void setSpriteHeight(float spriteHeight);
};
	


#endif // !ENTITY_H

