#include "../Componentes/Animation.h"

#ifndef ENTITY_H
#define ENTITY_H

enum statsOrder
{
	x,y,hp, atkFisico,defFisica,atkMagico,defMagica, velocidad, totalStatsSize
};

enum class typeOfAnimation : short
{
	Idle_Anim,
	Walk_Anim,
	Attack_Anim,
	Defend_Anim,
	Dead_Anim,
	Hurt_Anim,
	Total_Anim
	
};
struct estadisticas
{
	int hp; int defMagica;
	int defFisica; int atkFisico;
	int atkMagico; int velocidad;
};



class Entity
{
	protected:
		bool checkDead, restart, animationRequested;
		estadisticas stats;
		static const short arrSize = 8;
		int arrStats[arrSize];
		const int totalPoints = 600;
		Vector2f mousePos, coordinates;
		//Movimiento
		float speed;
		Vector2f velocity;
		//Gestion del sprite de la entidad
		unsigned int entitySize, entityAmount, checkSize, typeAnim;
		float spriteWidth, spriteHeight, currentTimer, currentAnimationDuration;
		Texture* entityTexture;
		Sprite* entitySprite;
		float elapsedT;
		AnimationComponent* animations;
		typeOfAnimation currenStateAnim, nextAnimation;
		//Gestion de los paquetes (envio y recepción de información)
		friend Packet& operator<<(Packet& packet, Entity& entity);
		friend Packet& operator>>(Packet& packet, Entity& entity);
		friend ostream& operator<<(ostream& out, Entity& entity);

	public:
		Entity();
		/*void initStats(int stats[]);*/
		virtual ~Entity();
		
		// METODOS
		void createAnimationComponent(Texture& texture);
		virtual void setTypeAnim(unsigned int typeAnim);
		virtual unsigned int getTypeAnim();
		virtual void setCurrentAnimation(typeOfAnimation xd);
		virtual void setNextAnimation(typeOfAnimation xd);
		void resetCurrentTimer();
		/*Movimiento y posicion de la entidad*/
		void setPosition(float xPos, float yPos);
		Vector2f getPosition();
		void setSpeed(float speed);
		float getSpeed() const;
		Vector2f getVelocity();
		virtual void entityMovement(float deltaTime, float x, float y);
		void setEntityAnimation(float x, float y);
		Vector2f getEntityMovement();

		/*Gestion del sprite de la entidad*/
		void render(RenderTarget* objTarget);
		virtual void update(const float& deltaT);
		void createSprite(Texture* spriteTexture);
		virtual void setTextureRect(unsigned int xCount, unsigned int yCount, unsigned int columns, unsigned int rows);
		//Gestión de la entidad
		void updateCharactState();
		 /*Controlar el daño -experimental-*/
		virtual void addDamage(int damage);
		/*Asignar  estadisticas*/
		virtual void asignarEstadisticas(estadisticas& stats, int hpPercent, int defMagicaPercent, int defFisicaPercent,
			int atkFisicoPercent, int atkMagicoPercent, int velocidadPercent);
		/*Aleatorizar el aumento de 10% o -10% de lasestadisticas*/
		virtual void variacionStats();

		
		//Getters and setters
		Texture* getEntityTexture() const;
		Sprite* getEntitySprite() const;
		void setEntityTexture(Texture& texture);
		void setEntitySprite(Sprite& sprite);
		float getSpriteWidth() const;
		void setSpriteWidth(unsigned int spriteWidth);
		float getSpriteHeight() const;
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
		void setId(unsigned int id);
		unsigned int getId();
		
		bool isAlive();
		estadisticas* getStats();
		
		
};
	


#endif // !ENTITY_H

