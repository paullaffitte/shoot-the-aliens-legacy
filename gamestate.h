#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "gameengine.h"

class GameState
{
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(GameEngine* editeur) = 0;
	virtual void Update(GameEngine* editeur) = 0;
	virtual void Draw(GameEngine* editeur) = 0;

	void ChangeState(GameEngine* editeur, GameState* state) {
		editeur->ChangeState(state);
	}

protected:
	GameState() { }
};

#endif
