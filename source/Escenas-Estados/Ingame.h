#ifndef INGAME_H
#define INGAME_H

#include "GameStatus.h"
#include "../source/Gui/PausaMenu.h"



enum Keybinds : unsigned short
{
	Down,Left,Right,Up, Total_Keybinds
};
enum Players
{
	Player_1, Player_2
};
enum mapLayers : unsigned short
{
	decoration1,decoration2,floorC,wallsC, Total_MapLayers
};

enum textureType : unsigned short
{
	Dragon_T, Dragon_FireEffect , Ogro_T , Sirena_T, Yordle_T, Battle_Background,  Total_TexturesIg
};

//enum typeAnim
//{
//	Idle_Anim,
//	Walk_Anim,
//	Attack_Anim,
//	Defend_Anim,
//	Dead_Anim,
//	Total_Anim
//};



// Estado ya en el juego
class Ingame : public GameStatus
{
private:
		Mapa<string, Gui::Box*> uiBoxes;
		Mapa<string, Entity*> playersIngame;
		RectangleShape battleBackground;
		std::pair<bool, string> actions;
		PausaMenu* pausaM;
		FloatRect winSize;
		Font font;
		//JAJAJAJA
		string forCorrectPorpouses;
		

		//funciones de inicio
		void textureProcessor(const string rute, const string key);
		void initBackgroud();
		void initPlayer();
		void createPlayer(const string& key, float xPos, float yPos);
		void initUI();
		void initFont();
		void initPauseMenu();
	public:
		Ingame(GameStatus** estados, RenderWindow* ventana);
		virtual ~Ingame();
		void render(RenderTarget* drawObj) override;
		void checkKeyboardEvents(float deltaT) override;
		void checkKeyboardPause(const float& deltaT);
		void Update(float deltaT) override;
		void updateGuiStatus(const std::string& playerKey, std::string& action) override;
		void updateMap();
		void updateButtons();
		Gui::Buttons* getButtons() override;
		Mapa<string, Entity*> getMapPlayer() override;
		void setActualPlayers(Mapa<string, Entity*> players) override;
		Mapa<string, Gui::Box*> getUiBoxes() override;
		std::pair<bool, string> getPlayerAction(const std::string& playerKey);
		void handleAttack(const string& attacker, const string& defender) override;
		int calculateDamage(int attackStat, const std::string& defenderKey, bool isDefending) override;
		void updateHealth(const std::string& playerKey, int damage) override;
		void determinateTurn();

};


#endif // !INGAME_H

