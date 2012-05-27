#ifndef BLANKGAME_H_
#define BLANKGAME_H_

#include "BaseGame.h"

class BlankGame : public BaseGame
{
	public:
		BlankGame();
		virtual ~BlankGame();

		virtual bool loadContent();
		virtual void unloadContent();

		virtual void update(float deltaTime);
		virtual void render();
};

#endif