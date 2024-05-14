#ifndef GAMESTATUS_H
#define GAMESTATUS_H


#include "gamemethods.h"
#include "Buttons.h"
#include "entity.h"
#include "player.h"


class GameStatus : public GameMethods
{
	protected:
		unsigned int textureArrSize, estadosArrSize,backLayersArrSize, playerArrSize, buttonArrSize;
		Buttons* buttons;
		Texture* textures;
		RectangleShape* backLayersArr;
		Entity** player;
		GameStatus** estados;
		RenderWindow* ventana;
		
		Vector2i mousePosScreen, mousePosWindow;
		Vector2f mousePosView;
		bool fin, active, isMenu;
	public:
		GameStatus();
		GameStatus(GameStatus** estados,RenderWindow* ventana);
		virtual ~GameStatus();
		
		// Metodos de la clase
			
		virtual void render(RenderTarget* drawObj) override;
		/*Esto se encarga de renderizar lo que se le pase, para ser
		mas específicos busquen sobre la funcion RenderTarget en la página de SFML :)*/
		virtual void checkKeyboardEvents(float deltaT) override;
		/*Esto se encarga de comprobar lo que ocurra con el teclado "eventos", para ser
		mas específicos busquen sobre lo que contiene el método en la página de SFML :)*/
		virtual void Update(float deltaTime) override;
		/*Esto se encarga de actualizar lo que tenga, segun el deltaT (El tiempo que se demora en renderizar cada frame el pc), 
		para ser mas específicos busquen sobre lo que contiene el método en la página de SFML :)*/
		virtual void updateMousePos() override;
		/*Esto se encarga de actualizar la posición del mouse, segun el deltaT (El tiempo que se demora en renderizar cada frame el pc 
		"Frame es como una escena, entonces seria el tiempo que se demora en generar cada escena del juego, como un storyboard" ).
		Para ser mas específicos busquen sobre lo que contiene los métodos que contiene el metodo en la página de SFML :)*/
		virtual Buttons* getButtons() = 0;
		virtual Entity* getPlayer(unsigned int i);
		virtual unsigned int getAmoutPlayer();

		// Gets and Sets
		RenderWindow* getWindow();
		GameStatus* getEstado(unsigned int num);
		Texture* getTexture(unsigned int num);
		unsigned int getTextureArrSize();
		unsigned int getEstadosArrSize();
		unsigned int setEstadosArrSize(unsigned int arrSize);
		bool getFin();
		void findEstado();
		void setActive(bool isActive);
		void setPlayer(unsigned int num, Player* player);
		bool getIsMenu();
		void setIsMenu(bool menu);
		
};


#endif // !GAMESTATUS_H

