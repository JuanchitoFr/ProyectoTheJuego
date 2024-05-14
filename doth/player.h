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
	void asignarEstadisticas(estadisticas& stats, int hpPercent, int defMagicaPercent, int defFisicaPercent,
		int atkFisicoPercent, int atkMagicoPercent, int velocidadPercent) override;
	virtual ~Player();
	


};


#endif // !PLAYER_H

