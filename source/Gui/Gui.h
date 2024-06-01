#ifndef GUI_H
#define GUI_H

enum btnStates : unsigned short{idle = 0, hover, pressed};

//En esta clase se gestionan los botones, pueden implementar una que gestione en si toda la interfaz ya sea en el menu o ingame.
namespace Gui
{
	class Buttons
	{
	private:
		unsigned short buttonState;
		RectangleShape buttonBody;
		Font* buttonFont;
		Text buttonText;
		Texture textureIdle;
		Texture textureHover;
		Texture texturePressed;
		bool visible;

	public:

		Buttons(float xPos, float yPos, float width, float heightFont, Font* font, string text, Texture textureIdle, Texture textureHover, Texture texturePressed);
		Buttons();
		virtual ~Buttons();
		void setPosition(float x, float y);
		void setSize(float width, float height);
		void render(RenderTarget* drawObj);
		void update(const Vector2f& mousePos);
		bool getButtonState();
		bool isPressed() const;
		bool isHover() const;
		bool isVisible() const;
		void setVisible(bool visible);
		float getButtonWidth();
		float getButtonHeight();
		Texture getTextureIdle();
		Texture getTextureHover();
		Texture getTexturePressed();
		RectangleShape getButtonBody();
		Text getBttonText();
		void centerText();
		void setCharacterSize(int num);


	};

	class Box
	{
	private:
		RectangleShape box;
		Font* boxFont;
		Text textBox;
		short boxState;
		bool visible;
	public:
		Box(float xPos, float yPos, float width, float height, Font& font, string text);
		virtual ~Box();
		void render(RenderTarget* drawObj);
		bool isVisible() const;
		bool isPressed() const;
		void setVisible(const bool visible);
		void update(const Vector2f& mousePos);
		void centerText();
		Vector2f getPosition();
		void setFont(float size);
	};

	class Bar
	{
	private:
	public:
		Bar();
		~Bar();

	

	};

}
	

#endif // !GUI_H
