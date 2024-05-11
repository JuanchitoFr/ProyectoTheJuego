#ifndef ENTITY_H
#define ENTITY_H
#include "entitymethods.h"

enum statsOrder
{
	x,y,hp, atkFisico,defFisica,atkMagico,defMagica, velocidad, totalStatsSize
};
struct Estadisticas
{
	int x; int y;
	int hp; int defMagica;
	int defFisica; int atkFisico;
	int atkMagico; int velocidad;
};


class Entity : public EntityMethods
{
	protected:
		//Movimiento
		IpAddress ip;
		float speed;
		Vector2f velocity;
		Vector2f coordinates;
		//Gestion del sprite de la entidad
		unsigned int entitySize, entityAmount, checkSize;
		unsigned int spriteWidth, spriteHeight;
		Texture* entityTexture;
		Sprite* entitySprite;
		float elapsedT;
		bool checkDead;
		Estadisticas stats;
		void init(int stats[]);
		static const short arrSize = 8;
		int arrStats[arrSize];
		const int totalAllStatsAmount = 600;
	public:
		Entity(Texture* entityTexture, float speed);
		Entity();
		virtual ~Entity();
		
		// METODOS
		/*Movimiento y posicion de la entidad*/
		void setPosition(float xPos, float yPos) override;
		Vector2f getPosition() override;
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
		void updateCharactState();
		virtual void addDamage(int damage);

		
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
		int getHp(); 
		int getDefMagica();
		int getDefFisica(); 
		int getAtkFisico();
		int getAtkMagico(); 
		int getVelocidad();
		IpAddress getIp();
		Estadisticas* estadisticas();
		bool isAlive();

		friend Packet& operator<<(Packet& packet, Entity& entity);
		friend Packet& operator>>(Packet& packet, Entity& entity);
		
		

		
		
};
	


#endif // !ENTITY_H

