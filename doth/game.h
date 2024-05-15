
#ifndef GAME_H
#define GAME_H

#define constexpr FRAMERATE_LIMIT 60
#define SCREEN_WIDHT 1280
#define SCREEN_HEIGHT 720


#include "Ingame.h"
#include "menu.h"

namespace
{
	enum class CommunicationState
	{
		Send,Receive
	};

	struct Client
	{
		IpAddress clientAdress;
		unsigned short port;
	};
}

class Game
{
	private:
		unsigned int anchoVentana, altoVentana, framerate;
		int currentEstadoIndex;
		ContextSettings settings;
		String tituloJuego;
		RenderWindow* ventana;
		Event event;
		GameStatus** estados;
		GameStatus* currentState;
		Buttons* buttonsState;
		float deltaT;
		Clock deltaTclock;
		Time timer;
		//Sockets
		UdpSocket socket;
		Packet packet;
		IpAddress server;
		bool isSocketServer, isSocketClient;
		Entity* entity;
		
	public:
		Game(unsigned int altoV, unsigned int anchoV, unsigned int framerate, String tituloJ);
		virtual ~Game();
		//Gestión juego
			/*Renderiza de acuerdo al estado existente en el momento*/
		void render();
			/*Actualiza el estado*/
		void updateState();
			/*Inicializa y actualiza el deltaTime*/
		void updateDeltaT();
			/*Inicializa el juego*/
		void run();
			/*Inicializa los eventos del estado*/
		void stateEvents();
			/*Inicializa un estado*/
		void initStates();

		//Gestión Sockets
			/*Inicializa un cliente*/
		void initServer();
			/*Inicializa un servidor*/
		void initClient();
		//De prueba estas funciones, se pueden o no eliminar luego
			/*Recepcion de datos por parte del servidor*/
		void recibirDatosS();
			/*Envio de datos por parte del servidor*/
		void enviarDatosS();
			/*Recepcion de datos por parte del cliente*/
		void recibirDatosC();
			/*Envio de datos por parte del cliente*/
		void enviarDatosC();

		//Get-Set
		void isServer();
		void networkType();
		IpAddress getIpAdressServer();
		UdpSocket& getSocket();
		
		
};

#endif // !GAME_H






