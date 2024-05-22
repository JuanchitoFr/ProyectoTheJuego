#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include "../Gui/Gui.h"
#include "../Player/Player.h"



enum typeCharacter {
	Dragon, Ogro, Sirena, Yordle, Total_TypeCharacters
};

enum Estados
{
	Menu_State, Ingame_State
};


//Clase base de la cual derivan los 2 estados Menu y Ingame

class GameStatus
{
	protected:
		unsigned int textureArrSize, estadosArrSize,backLayersArrSize, playerArrSize, buttonArrSize, characterChosen;
		Gui::Buttons* buttons;
		Texture* textures;
		RectangleShape* backLayersArr;
		Entity** player;
		GameStatus** estados;
		RenderWindow* ventana;
		
		Vector2i mousePosScreen, mousePosWindow;
		Vector2f mousePosView;
		bool fin, active, isMenu, paused;
	public:
		GameStatus();
		GameStatus(GameStatus** estados,RenderWindow* ventana);
		virtual ~GameStatus();
		
		// Metodos de la clase
			
		virtual void render(RenderTarget* drawObj);
		/*Esto se encarga de renderizar lo que se le pase, para ser
		mas espec�ficos busquen sobre la funcion RenderTarget en la p�gina de SFML :)*/
		virtual void checkKeyboardEvents(float deltaT);
		/*Esto se encarga de comprobar lo que ocurra con el teclado "eventos", para ser
		mas espec�ficos busquen sobre lo que contiene el m�todo en la p�gina de SFML :)*/
		virtual void Update(float deltaTime);
		virtual void GUI();
		/*Esto se encarga de actualizar lo que tenga, segun el deltaT (El tiempo que se demora en renderizar cada frame el pc), 
		para ser mas espec�ficos busquen sobre lo que contiene el m�todo en la p�gina de SFML :)*/
		void updateMousePos();
		/*Esto se encarga de actualizar la posici�n del mouse, segun el deltaT (El tiempo que se demora en renderizar cada frame el pc 
		"Frame es como una escena, entonces seria el tiempo que se demora en generar cada escena del juego, como un storyboard" ).
		Para ser mas espec�ficos busquen sobre lo que contiene los m�todos que contiene el metodo en la p�gina de SFML :)*/
		virtual Gui::Buttons* getButtons() = 0;
		Entity* getPlayer(unsigned int i);
		unsigned int getAmoutPlayer();

		// Gets and Sets
		RenderWindow* getWindow();
		GameStatus* getEstado(unsigned int num);
		Texture* getTexture(unsigned int num);
		unsigned int getTextureArrSize();
		unsigned int getEstadosArrSize();
		unsigned int setEstadosArrSize(unsigned int arrSize);
		bool getFin();
		void findEstado();
		void pausarEstado();
		void unpauseEstado();
		void setActive(bool isActive);
		void setPlayer(unsigned int num, Player* player);
		bool getIsMenu();
		void setIsMenu(bool menu);
		void setChosenCharacter(unsigned int chosen);
		
};


#endif // !GAMESTATUS_H

