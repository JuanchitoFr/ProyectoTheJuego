#ifndef ENTITY_H
#define ENTITY_H
//ola
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

enum typeAnimation
{
	Idle_Animation, Attack_Animation, Walk_Animation, Dead_Animation, Total_Animations
};



class Entity
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
		float spriteWidth, spriteHeight;
		Texture* entityTexture;
		Sprite* entitySprite;
		float elapsedT;
		//Gestion de los paquetes (envio y recepción de información)
		friend Packet& operator<<(Packet& packet, Entity& entity);
		friend Packet& operator>>(Packet& packet, Entity& entity);
		friend ostream& operator<<(ostream& out, Entity& entity);

	public:
		Entity();
		/*void initStats(int stats[]);*/
		virtual ~Entity();
		
		// METODOS
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
		virtual void updateSprite(float deltaT, float switchT);
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
		string getLogin();
		void setId(unsigned int id);
		unsigned int getId();
		bool isAlive();
		estadisticas* getStats();
		
		
};
	


#endif // !ENTITY_H

