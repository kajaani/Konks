#include "Tile.h"
#include "Constant.h"
cocos2d::Vec2 Constant::spawn = cocos2d::Vec2(0, 0);
Peli::Tile::Tile(cocos2d::Layer *layer)
{
	loadMap();
	MapBoundariesTop(layer);
	MapBoundariesRight(layer);
	MapBoundariesLeft(layer);

	previousTilePosition = cocos2d::Vec2(-1, -1);

	layer->addChild(map, 0);
	layer->addChild(minimap, 1);

	cocos2d::Vec2 tileSize = map->getLayer("Collision")->getMapTileSize();

	for (i = 0; i < map->getMapSize().width; i++)
	{
		for (j = 0; j < map->getMapSize().height; j++)
		{
			tileCoord = new cocos2d::Vec2(i, j);
			float gidPlatform = map->getLayer("Collision")->getTileGIDAt(*tileCoord);
			map->getLayer("Collision")->setVisible(false);
			map->getLayer("Spawn")->setVisible(false);
			float gidGoal = map->getLayer("Goal")->getTileGIDAt(*tileCoord);
			float gidSpike = map->getLayer("Spike")->getTileGIDAt(*tileCoord);
			float gidMetal = map->getLayer("Metal")->getTileGIDAt(*tileCoord);
			float gidSpawn = map->getLayer("Spawn")->getTileGIDAt(*tileCoord);

			//Handling the platform collision
			if (gidPlatform)
			{
				tileXPosition = i * map->getTileSize().width;																	//	* tileWidth;
				tileYPosition = (map->getMapSize().height * map->getTileSize().height) - ((j + 1) * map->getTileSize().height);	//(mapHeight * tileHeight) - ((j + 1) tileHeight);

				// Do this for first tile in the map
				if (previousTilePosition.x < 0)
				{
					previousTilePosition = cocos2d::Vec2(tileXPosition, tileYPosition);
				}

				if (previousTilePosition.x + map->getTileSize().width == tileXPosition)
				{
					//CCLOG("Collision was found next to this guy");
					previousTilePosition = cocos2d::Vec2(tileXPosition, tileYPosition);
				}
				//create a sprite
				auto sprite = cocos2d::Sprite::create();
				sprite->setPosition(cocos2d::Vec2(tileXPosition + map->getTileSize().width / 2, tileYPosition + map->getTileSize().height / 2));
				layer->addChild(sprite);

				//Creating the sprite

				// create a static PhysicsBody0
				physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(map->getTileSize().width, map->getTileSize().height), cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f));
				physicsBody->setDynamic(false);
				physicsBody->setEnable(false);
				physicsBody->setTag(TILE);

				sprite->setPhysicsBody(physicsBody);

				sprite->getPhysicsBody()->setCategoryBitmask(BITMASKTILE);
				sprite->getPhysicsBody()->setCollisionBitmask(BITMASKPLAYER);
				sprite->getPhysicsBody()->setContactTestBitmask(BITMASKCOLLISIONBOX);

				tileCollisions.push_back(sprite);
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

				objectSprite->getPhysicsBody()->setCategoryBitmask(BITMASKTILE);
				objectSprite->getPhysicsBody()->setCollisionBitmask(BITMASKNONE);
				objectSprite->getPhysicsBody()->setContactTestBitmask(BITMASKPLAYER);

				objectPhysicsBody->setTag(GOAL);

				tiles.push_back(objectSprite);
			}
			//Handling the spike collisions
			if (gidSpike)
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

				objectSprite->getPhysicsBody()->setCategoryBitmask(BITMASKSPIKE);
				objectSprite->getPhysicsBody()->setCollisionBitmask(BITMASKNONE);
				objectSprite->getPhysicsBody()->setContactTestBitmask(BITMASKPLAYER);

				objectPhysicsBody->setTag(SPIKE);

				tiles.push_back(objectSprite);
			}
			//Handling the metal collisions
			if (gidMetal)
			{
				tileAmount++;
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

				objectSprite->getPhysicsBody()->setCategoryBitmask(BITMASKSPIKE);
				objectSprite->getPhysicsBody()->setCollisionBitmask(BITMASKPLAYER);
				objectSprite->getPhysicsBody()->setContactTestBitmask(BITMASKCOLLISIONBOX);

				objectPhysicsBody->setTag(METAL);

				tiles.push_back(objectSprite);
			}
			if (gidSpawn)
			{
				tileXPosition = i * map->getTileSize().width;																	//	* tileWidth;
				tileYPosition = (map->getMapSize().height * map->getTileSize().height) - ((j + 1) * map->getTileSize().height); //(mapHeight * tileHeight) - ((j + 1) tileHeight);

				Constant::spawn = cocos2d::Vec2(tileXPosition, tileYPosition);
			}
		}
	}
}

void Peli::Tile::loadMap()
{
	map = cocos2d::TMXTiledMap::create(Constant::mapname);
	minimap = cocos2d::TMXTiledMap::create(Constant::mapname);
	minimap->setScaleY(0.1);
	minimap->setScaleX(0.05);
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

cocos2d::TMXTiledMap *Peli::Tile::getminiMap()
{
	return minimap;
}