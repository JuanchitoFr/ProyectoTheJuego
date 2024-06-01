#include "Entity.h"
#ifndef YORDLE_H
#define YORDLE_H

class Yordle : public Entity
{
private:
public:
	Yordle(Texture& texture, float xPos, float yPos);
	virtual ~Yordle();
	void update(const float& deltaT) override;
	void setNextAnimation(typeOfAnimation xd) override;
	void setCurrentAnimation(typeOfAnimation xd) override;
	void setTypeAnim(unsigned int typeAnim) override;
	unsigned int getTypeAnim() override;


};



#endif // !YORDLE_H

