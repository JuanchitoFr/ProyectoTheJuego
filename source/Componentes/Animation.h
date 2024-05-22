#ifndef ANIMATION_H
#define ANIMATION_H


enum typeAnimation
{
	Attack_Animation,
	Magic_Animation,
	Defense_Animation,
	Move_Animation,
	Death_Animation

};
const size_t Max_Size = 100;
class AnimationComponent
{
private:
	class Animation
	{
	private:
		typeAnimation nameAnimation;
		Sprite& sprite;
		Texture& texture;
		unsigned int width, height;
		float elapsedTime, switchTime;
		IntRect startTextureRect, currentRect, endTextureRect;

	public:
		Animation(Sprite& sprite, Texture& texture, typeAnimation nameAnimation, unsigned int startXrowPos, unsigned int startYcolumnPos,
			unsigned int endXrowPos, unsigned int endYcolumnPos, unsigned int totalXrow, unsigned int totalYColumn, float switchTime);
		Animation() : sprite(sprite) , texture(texture)
		{
		}
		~Animation();
		void update(const float& deltaT);
		void reset();
		typeAnimation& getNameAnimation();

		Animation& operator=(Animation& animation)
		{
			nameAnimation = animation.nameAnimation;
			sprite = animation.sprite;
			texture = animation.texture;
			width = animation.width;
			height = animation.height;
			elapsedTime = animation.elapsedTime;
			switchTime = animation.switchTime;
			startTextureRect = animation.startTextureRect;
			endTextureRect = animation.endTextureRect;
			return *this;
		}



	};

	class AnimationMap
	{
	private:
		std::string keys[Max_Size];
		Animation animations[Max_Size];
		int size;
	public:
		AnimationMap() : size(0)
		{
		}
		~AnimationMap()
		{
		}
		Animation get(const std::string key)
		{
			for (int i = 0; i < size; ++i) {
				if (keys[i] == key) {
					return animations[i];
				}
			}
			std::cerr << "Error: Key not found!" << std::endl;
			return Animation();  // Valor por defecto en caso de no encontrar la clave
		}
		void insert(const std::string key, Animation& animation)
		{
			for (size_t i = 0; i < size; i++)
			{
				if (keys[i] == key) {
					animations[i] = animation;
					return;
				}
			}
			if (size < Max_Size) {
				keys[size] = key;
				animations[size] = animation;
				++size;
			}
			else {
				std::cerr << "Error: Map is full!" << std::endl;
			}
		}
		void erase(const std::string key)
		{
			for (int i = 0; i < size; ++i) {
				if (keys[i] == key) {
					// Mover el último elemento a la posición del elemento eliminado
					keys[i] = keys[size - 1];
					animations[i] = animations[size - 1];
					--size;
					return;
				}
			}
			std::cerr << "Error: Key not found!" << std::endl;
		}
		size_t getSize() const
		{
			return size;
		}
	};

	Sprite& sprite;
	Texture& texture;
	AnimationMap map;
	
public:
	AnimationComponent(Sprite& sprite, Texture& texture);
	~AnimationComponent();
	Animation getClass()
	{
		return Animation();
	}
	void addAnimation(const string animation, Animation& animationType);
	void play(const string animation, const float& deltaTime);
	



};





#endif // !ANIMATION_H

