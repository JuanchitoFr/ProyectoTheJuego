#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

class Player : public Entity 
{
private:

public:
	Player(Texture* entityTexture, float speed,
		unsigned int xTextureRectPos, unsigned int yTextureRectPos);
	Player();
	virtual ~Player();
	


};


#endif // !PLAYER_H

