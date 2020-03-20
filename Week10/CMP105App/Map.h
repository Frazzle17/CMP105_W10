#pragma once
#include "Framework/TileMap.h"
#include "Framework/Input.h"
#include "Framework/Collision.h"
#include "Player.h"
class Map
{
public:
	Map();
	~Map();

	void setInput(Input* in) { input = in; };
	void setWindow(sf::RenderWindow* win) { window = win; };
	void setPlayer(Player* play) { player = play; };
	void setupView();

	virtual void handleInput(float dt);
	virtual void update();
	virtual void render();

protected:
	Input* input;
	sf::RenderWindow* window;
	Player* player;
	TileMap tileMap;
	sf::View view;
	sf::Vector2u mapSizePixel;
};

