#ifndef PAUSAMENU_H
#define PAUSAMENU_H
#include "../Gui/Gui.h"

enum buttonsMenuPausa
{
	Resume_Button, Exit_Button, Total_Buttons
};
class PausaMenu
{
private:
	Font fuenteMenu;
	Text menuText;
	RectangleShape background;
	RectangleShape container;
	RenderWindow* ventana;
	int size;
	Mapa<string, Gui::Buttons*> botones;
public:
	PausaMenu(RenderWindow& ventana, Font& fuenteMenu);
	virtual ~PausaMenu();
	void createNewButton(float xPos, float yPos, const string key, const string text);
	void update(const Vector2f& mousePos);
	bool checkIsUnPause();
	void render(RenderTarget* objTarget);
	const bool IsButtonPressed(const string key);
	Mapa<string, Gui::Buttons*> getBotones();


};

#endif // !PAUSAMENU_H

