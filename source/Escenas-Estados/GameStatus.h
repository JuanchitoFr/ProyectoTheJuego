#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include "../Gui/Gui.h"
#include "../Player/Ogro.h"
#include "../Player/Sirena.h"
#include "../Player/Dragon.h"
#include "../Player/Yordle.h"



enum typeCharacter {
	Dragon_C, Ogro_C, Sirena_C, Yordle_C, Total_TypeCharacters
};

enum Estados
{
	Menu_State, Ingame_State
};


//Clase base de la cual derivan los 2 estados Menu y Ingame

class GameStatus
{
	protected:
		unsigned int estadosArrSize, buttonArrSize, characterChosen, clientNumber;
		Gui::Buttons* buttons;
		Mapa<string, Entity*> players;
		Mapa<string, Texture*> stateTextures;
		GameStatus** estados;
		RenderWindow* ventana;
		TcpSocket* socket;
		Vector2i mousePosScreen, mousePosWindow;
		Vector2f mousePosView;
		bool fin, active, isMenu, paused, conection, selectedCharacter, anotherClient;
	public:
		GameStatus();
		GameStatus(GameStatus** estados,RenderWindow* ventana);
		virtual ~GameStatus();
		
		// Metodos de la clase
			
		virtual void render(RenderTarget* drawObj);
		/*Esto se encarga de renderizar lo que se le pase, para ser
		mas específicos busquen sobre la funcion RenderTarget en la página de SFML :)*/
		virtual void checkKeyboardEvents(float deltaT);
		/*Esto se encarga de comprobar lo que ocurra con el teclado "eventos", para ser
		mas específicos busquen sobre lo que contiene el método en la página de SFML :)*/
		virtual void Update(float deltaTime);
		/*Esto se encarga de actualizar lo que tenga, segun el deltaT (El tiempo que se demora en renderizar cada frame el pc), 
		para ser mas específicos busquen sobre lo que contiene el método en la página de SFML :)*/
		void updateMousePos();
		/*Esto se encarga de actualizar la posición del mouse, segun el deltaT (El tiempo que se demora en renderizar cada frame el pc 
		"Frame es como una escena, entonces seria el tiempo que se demora en generar cada escena del juego, como un storyboard" ).
		Para ser mas específicos busquen sobre lo que contiene los métodos que contiene el metodo en la página de SFML :)*/
		virtual Gui::Buttons* getButtons() = 0;

		// Gets and Sets
		RenderWindow* getWindow();
		GameStatus* getEstado(unsigned int num);
		unsigned int getEstadosArrSize();
		unsigned int setEstadosArrSize(unsigned int arrSize);
		virtual void updateGuiStatus(const std::string& playerKey, std::string& action);
		bool getFin();
		void findEstado();
		void pausarEstado();
		void unpauseEstado();
		void setActive(bool isActive);
		bool getIsMenu();
		void setIsMenu(bool menu);
		void setChosenCharacter(unsigned int chosen);
		const unsigned int& getChosenCharacter() ;
		void thereIsConection(bool conection);
		const bool getThereIsConection();
		void isSelectedCharacter(bool conection);
		const bool getSelectedCharacter();
		void isAnotherClient(bool what);
		const bool getAnotherClient();
		virtual Entity* getPlayer();
		virtual Mapa<string, Entity*> getMapPlayer();
		virtual Mapa<string, Gui::Box*> getUiBoxes();
		std::pair<bool, string> getPlayerAction(const std::string& playerKey);
		friend sf::Packet& operator<<(sf::Packet& packet, const std::pair<bool, std::string>& action)
		{
			return packet << action.first << action.second;
		}

		friend sf::Packet& operator>>(sf::Packet& packet, std::pair<bool, std::string>& action)
		{
			return packet >> action.first >> action.second;
		}
		virtual void setSocket(TcpSocket& socket);
		virtual void handleAttack(const string& attacker, const string& defender);
		virtual int calculateDamage(int attackStat, const std::string& defenderKey, bool isDefending);
		virtual void updateHealth(const std::string& playerKey, int damage);
		
};


#endif // !GAMESTATUS_H

