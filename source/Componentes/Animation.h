#ifndef ANIMATION_H
#define ANIMATION_H

class AnimationComponent
{
	private:
		class Animation
		{
		private:
			Sprite& sprite;
			Texture& texture;
			unsigned int width, height;
			float elapsedTime, switchTime;
			IntRect startTextureRect, currentRect, endTextureRect;
			bool finished;

		public:
			Animation(Sprite& sprite, Texture& texture, unsigned int startXrowPos, unsigned int startYcolumnPos,
				unsigned int endXrowPos, unsigned int endYcolumnPos, unsigned int totalXrow, unsigned int totalYColumn, float switchTime);
			Animation() : sprite(sprite) , texture(texture)
			{
			}
			~Animation();
			void update(const float& deltaT);
			void reset();
			bool isFinished() const;


		};

		Sprite& sprite;
		Texture& texture;
		Mapa<string, Animation*> animations;
		Animation* lastAnimation;
	
	public:
		AnimationComponent(Sprite& sprite, Texture& texture);
		~AnimationComponent();
		void addAnimation(const string nameOfAnimation, unsigned int startXrowPos, unsigned int startYcolumnPos, 
			unsigned int endXrowPos, unsigned int endYcolumnPos, unsigned int totalXrow, unsigned int totalYColumn, float switchTime);
		void play(const string nameOfAnimation, const float& deltaTime);
		void stop();
		Animation* getAnimations(const string key)
		{
			return this->animations[key];
		}

};


#endif // !ANIMATION_H

