#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

//Clase del jugador, pueden implementarla utilizando polimorfismo con la de entity mediante punteros
class Player : public Entity 
{
private:

public:
	Player(Texture*, float, unsigned int, unsigned int);
	~Player();
	void setTextureRect(unsigned int xCount, unsigned int yCount, unsigned int columns, unsigned int rows) override;

	


};


#endif // !PLAYER_H

