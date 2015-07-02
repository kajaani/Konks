#include "Tile.h"

Peli::Tile::Tile(cocos2d::Layer *layer, std::string level)
{
	loadMap(level);
	MapBoundariesTop(layer);
	MapBoundariesRight(layer);
	MapBoundariesLeft(layer);

	layer->addChild(map, 0);

	cocos2d::Vec2 tileSize = map->getLayer("Meta")->getMapTileSize();

	for (i = 0; i < map->getMapSize().width; i++)
	{
		for (j = 0; j < map->getMapSize().height; j++)
		{
			tileCoord = new cocos2d::Vec2(i, j);
			float gidPlatform = map->getLayer("Meta")->getTileGIDAt(*tileCoord);
			float gidGoal = map->getLayer("Goal")->getTileGIDAt(*tileCoord);

			//Handling the platform collision
			if (gidPlatform)
			{

				tileXPosition = i * map->getTileSize().width;																	//	* tileWidth;
				tileYPosition = (map->getMapSize().height * map->getTileSize().height) - ((j + 1) * map->getTileSize().height);	//(mapHeight * tileHeight) - ((j + 1) tileHeight);

				//create a sprite
				auto sprite = cocos2d::Sprite::create();
				sprite->setPosition(cocos2d::Vec2(tileXPosition + map->getTileSize().width / 2, tileYPosition + map->getTileSize().height / 2));
				layer->addChild(sprite);

				//Creating the sprite

				// create a static PhysicsBody0
				physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(map->getTileSize().width, map->getTileSize().height));
				physicsBody->setDynamic(false);
				physicsBody->setTag(11);

				sprite->setPhysicsBody(physicsBody);
				sprite->getPhysicsBody()->setContactTestBitmask(BITMASK_A);
				sprite->getPhysicsBody()->setCategoryBitmask(BITMASK_B);
			}
			
			//Handling the object collision
			if (gidGoal)
			{
				tileXPosition = i * map->getTileSize().width;																	//	* tileWidth;
				tileYPosition = (map->getMapSize().height * map->getTileSize().height) - ((j + 1) * map->getTileSize().height); //(mapHeight * tileHeight) - ((j + 1) tileHeight);
				
				//Creating the sprite
				auto objectSprite = cocos2d::Sprite::create();
				objectSprite->setPosition(cocos2d::Vec2(tileXPosition + map->getTileSize().width / 2, tileYPosition + map->getTileSize().height / 2));
				layer->addChild(objectSprite);

				//Creating the physics body
				objectPhysicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(map->getTileSize().width, map->getTileSize().height));
				objectPhysicsBody->setDynamic(false);

				objectSprite->setPhysicsBody(objectPhysicsBody);
				objectSprite->getPhysicsBody()->setContactTestBitmask(BITMASK_B);
				objectSprite->getPhysicsBody()->setCategoryBitmask(BITMASK_A);

				objectPhysicsBody->setTag(12);
		
			}
		}
	}

}

void Peli::Tile::loadMap(std::string level)
{
	map = cocos2d::TMXTiledMap::create(level);
	_meta = map->layerNamed("Meta");
	_meta = map->layerNamed("Background");
	//_meta = map->layerNamed("TileCats");
	_meta->setVisible(true);
}

cocos2d::Point	Peli::Tile::tileCoordForPosition(cocos2d::Point position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return cocos2d::Point(x, y);
}


void Peli::Tile::MapBoundariesTop(cocos2d::Layer *layer)
{
//Top Collision
auto sprite = cocos2d::Sprite::create();
sprite->setPosition(cocos2d::Vec2((map->getMapSize().width*map->getTileSize().width) / 2, (map->getMapSize().height * map->getTileSize().height + (map->getTileSize().height / 2))));

physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(map->getMapSize().width * map->getTileSize().width, map->getTileSize().height));
physicsBody->setDynamic(false);
sprite->setPhysicsBody(physicsBody);
layer->addChild(sprite);

}

void Peli::Tile::MapBoundariesRight(cocos2d::Layer *layer)
{
	//Right collision
	auto sprite = cocos2d::Sprite::create();
	sprite->setPosition(cocos2d::Vec2(map->getMapSize().width * map->getTileSize().width + (map->getTileSize().width / 2), ((map->getMapSize().height * map->getTileSize().height)) / 2));

	physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(map->getTileSize().width, map->getMapSize().height * map->getTileSize().height));
	physicsBody->setDynamic(false);
	sprite->setPhysicsBody(physicsBody);
	layer->addChild(sprite);
}

void Peli::Tile::MapBoundariesLeft(cocos2d::Layer *layer)
{
	//Left collision
	auto sprite = cocos2d::Sprite::create();
	sprite->setPosition(cocos2d::Vec2(0 - (map->getTileSize().width / 2), ((map->getMapSize().height * map->getTileSize().height)) / 2));

	physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(map->getTileSize().width, map->getMapSize().height * map->getTileSize().height));
	physicsBody->setDynamic(false);
	sprite->setPhysicsBody(physicsBody);
	layer->addChild(sprite);
}

cocos2d::TMXTiledMap *Peli::Tile::getMap()
{
	return map;
}