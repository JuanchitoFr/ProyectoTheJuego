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
	Gui::Buttons* buttons[2];
public:
	PausaMenu(RenderWindow& ventana, Font& fuenteMenu);
	virtual ~PausaMenu();
	void createNewButton(float xPos, float yPos);
	void update(const Vector2f& mousePos);
	bool checkIsUnPause();
	void render(RenderTarget* objTarget);
	void IsButtonPressed();
	Gui::Buttons** getButtons();



};

#endif // !PAUSAMENU_H

