#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player : public Entity 
{
private:

public:
	Player(float xPos, float yPos, int hp, String name, float spriteWidht, float spriteHeight, Texture* playerTexture);
	virtual ~Player();
	void entityMovement(double deltaTime, float x, float y, float speed) override;
	void render(RenderTarget* objTarget) override;
	void updateTimeInScreen(double deltaT) override;

};


#endif // !PLAYER_H

