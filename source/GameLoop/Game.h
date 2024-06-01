
#ifndef GAME_H
#define GAME_H

#include "../source/Escenas-Estados/Ingame.h"
#include "../source/Escenas-Estados/Menu.h"
#include "../Sockets/Network.h"
//Bucle del juego, aqui va todo lo esencial de lo que hagan en menu o ingame.
class Game
{
	private:
		unsigned int anchoVentana, altoVentana, framerate, nextEntityId;
		size_t currentEstadoIndex;
		ContextSettings settings;
		String tituloJuego;
		RenderWindow* ventana;
		Event event;
		GameStatus** estados;
		GameStatus* currentState;
		float deltaT;
		Clock deltaTclock;
		Time timer;
		bool isClientTurn, isServerTurn, isServer,isClient;
		TcpListener listener;
		TcpSocket client, socket;
		
	public:
		Game(unsigned int altoV, unsigned int anchoV, unsigned int framerate, String tituloJ);
		virtual ~Game();
		//Gestión juego
			/*Renderiza de acuerdo al estado existente en el momento*/
		void render();
			/*Actualiza el estado (eventos o si ya finalizo este mismo)*/
		void updateState();
			/*Inicializa y actualiza el deltaTime*/
		void updateDeltaT();
			/*Inicializa el juego, bucle principal*/
		void run();
			/*Inicializa los eventos del estado*/
		void stateEvents();
			/*Inicializa un estado, pasandole la dirección de memoria de un estado*/
		void updateGui();
		void initStates();
		void serverSide();
		void clientSide();
		void manageDataServer();
		void manageDataClient();
		void buttonStatus();
		void switchTurn();
		void determineTurn();
		
		
		
};

#endif // !GAME_H






