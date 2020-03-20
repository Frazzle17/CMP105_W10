#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	map.setInput(input);
	map.setWindow(window);
	Player* play = &player;
	map.setPlayer(play);
	map.setupView();

	playerTexture.loadFromFile("gfx/MushroomTrans.png");
	player.setTexture(&playerTexture);
	player.setInput(input);
	player.setWindow(window);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	map.handleInput(dt);
	player.handleInput();
}

// Update game objects
void Level::update(float dt)
{
	player.update(dt);
	map.update();
}

// Render level
void Level::render()
{
	beginDraw();

	map.render();
	window->draw(player);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}