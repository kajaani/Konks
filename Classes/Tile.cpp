#include "Tile.h"

Peli::Tile::Tile(cocos2d::Layer *layer, std::string level)
{
	map = cocos2d::TMXTiledMap::create(level);
	_meta = map->layerNamed("Meta");
	_meta = map->layerNamed("Background");
	_meta = map->layerNamed("Goal");
	//_meta = map->layerNamed("TileCats");
	_meta->setVisible(true);

	layer->addChild(map, 0);

	cocos2d::Vec2 tileSize = map->getLayer("Meta")->getMapTileSize();

	int BITMASK_A = 0x1 << 0;
	int BITMASK_B = 0x1 << 1;

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

				sprite->setPhysicsBody(physicsBody);
				sprite->getPhysicsBody()->setContactTestBitmask(BITMASK_B);
				sprite->getPhysicsBody()->setCategoryBitmask(BITMASK_A);
			}
			
			//Handling the object collision
			if (gidGoal)
			{
				int BITMASK_A = 0x1 << 0;
				int BITMASK_B = 0x1 << 1;

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

cocos2d::Point	Peli::Tile::tileCoordForPosition(cocos2d::Point position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return cocos2d::Point(x, y);
}