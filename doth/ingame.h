#ifndef INGAME_H
#define INGAME_H

#include "gamestatus.h"
#include "player.h"
#include "entity.h"
//Animation player
enum Keybinds
{
	Down,Left,Right,Up
};

enum mapLayers
{
	decoration1,decoration2,floorC,wallsC
};

class Ingame : public GameStatus
{
	private:
		Entity* npc;
		Entity* playerS;
		std::map<unsigned short, RectangleShape> background;
		void initTextures();
		void initPlayer();
		void initMap();
		FloatRect winSize;
		Vector2f currentWinSize;
		bool sizeChange;
		
	public:
		Ingame(std::stack<GameStatus*>* Statetype, RenderWindow* ventana);
		virtual ~Ingame();
		void render(RenderTarget* drawObj) override;
		void checkKeyboardEvents(float deltaT) override;
		void Update(float deltaT) override;
		void updateMap();
		void run() override;
		void endState() override;
		void parcialEndState() override;


};


#endif // !INGAME_H

