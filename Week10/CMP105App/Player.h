#pragma once
#include "Framework/GameObject.h"
class Player :public GameObject
{
public:
	Player();
	~Player();

	void setWindow(sf::RenderWindow* win) { window = win; };

	virtual void handleInput();
	virtual void update(float dt);

	void collisionResponse(GameObject* collider);

protected:
	sf::RenderWindow* window;
	float speed;
	float scale;
	sf::Vector2f gravity;
	sf::Vector2f stepVelocity;
	bool jumped;
	bool jumped2;
};
