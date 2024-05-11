
#ifndef GAME_H
#define GAME_H

#define constexpr FRAMERATE_LIMIT 60
#define SCREEN_WIDHT 1280
#define SCREEN_HEIGHT 720


#include "Ingame.h"
#include "menu.h"

enum stateName
{
	menu, ingame
};
class Game
{
	private:
		unsigned int anchoVentana, altoVentana, framerate;
		int currentEstadoIndex;
		ContextSettings settings;
		String tituloJuego;
		RenderWindow* ventana;
		Event event;
		GameStatus* estados;
		GameStatus* currentState;
		float deltaT;
		Clock deltaTclock;
		Time timer;
		Packet packet;
		UdpSocket socket;

	public:
		Game(unsigned int altoV, unsigned int anchoV, unsigned int framerate, String tituloJ);
		virtual ~Game();
		void render();
		void updateState();
		void updateDeltaT();
		void run();
		void stateEvents();
		void initStates();
		void recibirDatos();
		void enviarDatos();
};

#endif // !GAME_H






