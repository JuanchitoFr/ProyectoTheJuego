#ifndef ENTITY_H
#define ENTITY_H
#include "entitymethods.h"

enum statsOrder
{
	x,y,hp, atkFisico,defFisica,atkMagico,defMagica, velocidad, totalStatsSize
};
struct estadisticas
{
	int x; int y;
	int hp; int defMagica;
	int defFisica; int atkFisico;
	int atkMagico; int velocidad;
};



class Entity : public EntityMethods
{
	protected:
		//Socket
		IpAddress ip;
		//Gestión de la información que se recibe-envia
		string data, login;
		unsigned int id;
		bool checkDead, restart;
		estadisticas stats;
		static const short arrSize = 8;
		int arrStats[arrSize];
		const int totalPoints = 600;
		Vector2f mousePos, coordinates;
		//Movimiento
		float speed;
		Vector2f velocity;
		//Gestion del sprite de la entidad
		unsigned int entitySize, entityAmount, checkSize;
		unsigned int spriteWidth, spriteHeight;
		Texture* entityTexture;
		Sprite* entitySprite;
		float elapsedT;
		//Gestion de los paquetes (envio y recepción de información)
		friend Packet& operator<<(Packet& packet, Entity& entity);
		friend Packet& operator>>(Packet& packet, Entity& entity);
		friend ostream& operator<<(ostream& out, Entity& entity);

	public:
		Entity(Texture* entityTexture, float speed);
		Entity();
		void initStats(int stats[]);
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
		//Gestión de la entidad
		void updateCharactState();
		virtual void addDamage(int damage);
		virtual void asignarEstadisticas(estadisticas& stats, int hpPercent, int defMagicaPercent, int defFisicaPercent,
			int atkFisicoPercent, int atkMagicoPercent, int velocidadPercent);
		virtual void variacionStats();

		
		//Getters and setters
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
		void setIp(IpAddress ip);
		void setLogin(string data);
		string getLogin();
		void setId(unsigned int id);
		unsigned int getId();
		bool isAlive();
		estadisticas* getStats();
		
		
};
	


#endif // !ENTITY_H

