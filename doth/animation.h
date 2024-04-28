#ifndef ANIMATION_H
#define ANIMATION_H

struct Frame
{
	IntRect textureR;
	double duration;
};

class Animation
{
	private:	
		std::vector<Frame> frames;
		double totalLength;
		double progress;
		Sprite& objective;
		
	public:
		Animation(Sprite& objeto);
		virtual ~Animation();
		void addAframe(Frame&& frame);
		void update(double elapsed);
		const double getLength() const;
};



#endif // !ANIMATION_H
