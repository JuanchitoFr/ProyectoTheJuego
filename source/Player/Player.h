#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"

//Clase del jugador, pueden implementarla utilizando polimorfismo con la de entity mediante punteros
class Player : public Entity 
{
private:
	float widht, height;
public:
	Player(Texture*, float speed, unsigned int totalXrows, unsigned int totalYColumns);
	~Player();
	/*Gestion del sprite de la entidad*/
	void updateSprite(float deltaT, float switchT) override;
	void setTextureRect(unsigned int xCount, unsigned int yCount, unsigned int columns, unsigned int rows) override;
	//Gestión de la entidad
	/*Controlar el daño -experimental-*/
	void addDamage(int damage) override;
	/*Asignar  estadisticas*/
	void asignarEstadisticas(estadisticas& stats, int hpPercent, int defMagicaPercent, int defFisicaPercent,
		int atkFisicoPercent, int atkMagicoPercent, int velocidadPercent) override;
	/*Aleatorizar el aumento de 10% o -10% de lasestadisticas*/
	void variacionStats() override;
	


};


#endif // !PLAYER_H

