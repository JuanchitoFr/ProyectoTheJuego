#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player : public Entity 
{
private:

public:
	Player(int spriteWidth, int spriteHeight, Texture* playerTexture, float speed, int xPos, int yPos, unsigned int row, unsigned int xRowPos);
	virtual ~Player();
	void initAnimaions();
	


};


#endif // !PLAYER_H

