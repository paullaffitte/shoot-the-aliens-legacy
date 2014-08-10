#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

class GameState;

class GameEngine
{
public:

	void Init(const char* titre, int largeur, int hauteur);
	void Cleanup();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() {return m_running;}
	void Quit() {m_running = false;}

	sf::RenderWindow* getFenetre() {return m_fenetre;}

private:
	// la pile d'états
	vector<GameState*> states;

	bool m_running;
	bool m_fullscreen;
	sf::RenderWindow* m_fenetre;
};

#endif
