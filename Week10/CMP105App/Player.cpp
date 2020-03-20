#include "Player.h"
#include <iostream>
Player::Player()
{
	window = nullptr;
	setPosition(0, 0);
	setSize(sf::Vector2f(32, 32));
	setCollisionBox(0, 0, 32, 32);
	speed = 300.f;
	scale = 200.f;
	gravity = sf::Vector2f(0, 9.8) * scale;
	stepVelocity = sf::Vector2f(0, 0);
	jumped = false;
	jumped2 = false;
}

Player::~Player()
{

}

void Player::handleInput()
{
	//Move Right
	if (input->isKeyDown(sf::Keyboard::Right))
	{
		velocity.x += speed;
	}
	//Move Left
	if (input->isKeyDown(sf::Keyboard::Left))
	{
		velocity.x -= speed;
	}
	//Jump
	if (input->isKeyDown(sf::Keyboard::Up))
	{
		input->setKeyUp(sf::Keyboard::Up);
		if (jumped == false)
		{
			stepVelocity.y = -750;
			jumped = true;
		}
	}
	//Double Jump
	if (!input->isKeyDown(sf::Keyboard::Up) && jumped == true && jumped2 == false)
	{
		jumped = false;
		jumped2 = true;
	}
}

void Player::update(float dt)
{
	//Gravity
	sf::Vector2f pos = stepVelocity * dt + 0.5f * gravity * dt * dt;
	stepVelocity += gravity * dt;
	setPosition(getPosition() + pos);
	//Floor collision
	if (getPosition().y + getSize().y >= window->getSize().y)
	{
		jumped = false;
		jumped2 = false;
		setPosition(getPosition().x, window->getSize().y - getSize().y);
		stepVelocity = sf::Vector2f(0, 0);
	}
	//Other Movement
	move(velocity * dt);
	velocity = sf::Vector2f(0, 0);
}

void Player::collisionResponse(GameObject* collider)
{
	float diffX = (collider->getPosition().x + (collider->getSize().x / 2)) - (getPosition().x + (getSize().x / 2));
	float diffY = (collider->getPosition().y + (collider->getSize().y / 2)) - (getPosition().y + (getSize().y / 2));

	if (std::abs(diffX) > std::abs(diffY))
	{
		std::cout << "x axis collision: ";
		if (diffX > 0)
		{
			std::cout << "left\n";
			velocity.x = 0;
			setPosition(collider->getPosition().x - getSize().x, getPosition().y);
		}
		else
		{
			std::cout << "right\n";
			velocity.x = 0;
			setPosition(collider->getPosition().x + collider->getSize().x, getPosition().y);
		}
	}
	else
	{
		std::cout << "y axis collision: ";
		if (diffY < 0)
		{
			std::cout << "bottom\n";
			setPosition(getPosition().x, collider->getPosition().y + collider->getSize().y);
			stepVelocity = sf::Vector2f(0, 0);
		}
		else
		{
			std::cout << "top\n";
			jumped = false;
			jumped2 = false;
			setPosition(getPosition().x, collider->getPosition().y - getSize().y);
			stepVelocity = sf::Vector2f(0, 0);
		}
	}
}