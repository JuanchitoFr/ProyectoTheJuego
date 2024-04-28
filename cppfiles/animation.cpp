#include <pch.h>
#include <../doth/animation.h>

Animation::Animation(Sprite& objeto) : objective(objeto)
{
	progress = totalLength = 0.f;
}

Animation::~Animation()
{
}

void Animation::addAframe(Frame&& frame)
{
	totalLength += frame.duration;
	frames.push_back(std::move(frame));
}

void Animation::update(double elapsed)
{
    progress += elapsed;
    double p = progress;
    for (size_t i = 0; i < frames.size(); i++) {
        p -= frames[i].duration;

        if (objective.getTexture()->isRepeated() == true && p > 0.0 && &(frames[i]) == &frames.back())
        {
            i = 0;
            continue;
        }
        // if we have progressed OR if we're on the last frame, apply and stop.
        if (p <= 0.0 || &(frames[i]) == &frames.back())
        {
            objective.setTextureRect(frames[i].textureR);
            break; // we found our frame
        }
    }
}

const double Animation::getLength() const
{
	return this->totalLength;
}
