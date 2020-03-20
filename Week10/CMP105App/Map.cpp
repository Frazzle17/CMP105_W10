#include "Map.h"
Map::Map()
{
	window = nullptr;
	input = nullptr;
	player = nullptr;
	tileMap.loadTexture("gfx/marioTiles.png");

	//create the tileset
	GameObject tile;
	std::vector<GameObject> tiles;

	for (int i = 0; i < 7; i++)
	{
		tile.setSize(sf::Vector2f(32, 32));
		tile.setCollisionBox(0, 0, 32, 32);
		tile.setCollider(true);
		tiles.push_back(tile);
	}

	tiles[0].setCollider(false);
	tiles[0].setTextureRect(sf::IntRect(187, 51, 16, 16));
	tiles[1].setTextureRect(sf::IntRect(0, 0, 16, 16));
	tiles[2].setTextureRect(sf::IntRect(17, 0, 16, 16));
	tiles[3].setTextureRect(sf::IntRect(34, 0, 16, 16));
	tiles[4].setTextureRect(sf::IntRect(0, 34, 16, 16));
	tiles[5].setTextureRect(sf::IntRect(17, 34, 16, 16));
	tiles[6].setTextureRect(sf::IntRect(34, 34, 16, 16));

	tileMap.setTileSet(tiles);

	//map dimensions
	sf::Vector2u mapsize(40, 12);
	mapSizePixel = sf::Vector2u(mapsize.x * 32, mapsize.y * 32);

	//build map
	std::vector<int> map = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,4,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	};

	tileMap.setTileMap(map, mapsize);
	tileMap.setPosition(sf::Vector2f(0, 0));
	tileMap.buildLevel();
}

Map::~Map()
{

}

void Map::setupView()
{
	view.setSize(20*32, 12*32);
	view.setCenter(20 * 32 / 2, 12 * 32 / 2);
}

void Map::handleInput(float dt)
{
	float xOffset = 20 * 32 / 2;
	sf::Vector2f viewCenter = view.getCenter();
	if (input->isKeyDown(sf::Keyboard::Left) || input->isKeyDown(sf::Keyboard::Right))
	{
		if (player->getPosition().x <= 0)
		{
			player->setPosition(0, player->getPosition().y);
		}

		if (player->getPosition().x + player->getSize().x >= mapSizePixel.x)
		{
			player->setPosition(0, player->getPosition().y);
		}

		if (player->getPosition().x < xOffset)
		{
			view.setCenter(xOffset, viewCenter.y);
		}
		else if (player->getPosition().x > mapSizePixel.x - xOffset)
		{
			view.setCenter(mapSizePixel.x - xOffset, viewCenter.y);
		}
		else
		{
			view.setCenter(player->getPosition().x, 12 * 32 / 2);
		}
	}
}

void Map::update()
{
	window->setView(view);
	std::vector<GameObject>* world = tileMap.getLevel();
	for (int i = 0; i < world->size(); i++)
	{
		if ((*world)[i].isCollider())
		{
			if (Collision::checkBoundingBox(player, &((*world)[i])))
			{
				player->collisionResponse(&((*world)[i]));
			}
		}
	}
}

void Map::render()
{
	tileMap.render(window);
}