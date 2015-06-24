#include "Tile.h"

Peli::Tile::Tile(cocos2d::Layer *layer, std::string level)
{
	map = cocos2d::TMXTiledMap::create(level);
	_meta = map->layerNamed("Meta");
	_meta = map->layerNamed("Background");
	_meta = map->layerNamed("TileCats");
	_meta->setVisible(true);

	layer->addChild(map, 0);


	cocos2d::Vec2 tileSize = map->getLayer("Meta")->getMapTileSize();


	for (i = 0; i < map->getMapSize().width; i++)
	{
		for (j = 0; j < map->getMapSize().height; j++)
		{
			tileCoord = new cocos2d::Vec2(i, j);
			float gid = map->getLayer("Meta")->getTileGIDAt(*tileCoord);
			if (gid)
			{
				CCLOG("gid: %i", gid);

				tileXPosition = i * map->getTileSize().width;						//	* tileWidth;
				tileYPosition = (map->getMapSize().height * map->getTileSize().height) - ((j + 1) * map->getTileSize().height);							//(mapHeight * tileHeight) - ((j + 1) tileHeight);

				/*	int Width = map->getLayer("Meta")->getPosition().x;
				int Height = map->getLayer("Meta")->getPosition().y;*/

				CCLOG("Width: %i Height: %i", Width, Height);


				// react = rect(tileXPosition, tileYPosition, tileWidth, tileHeight);

				//create a sprite
				auto sprite = cocos2d::Sprite::create();
				sprite->setPosition(cocos2d::Vec2(tileXPosition + map->getTileSize().width / 2, tileYPosition + map->getTileSize().height / 2));
				layer->addChild(sprite);

				// Creating sprites & collisions

				// create a static PhysicsBody0
				//PlayerPhysics = PhysicsBody::createBox(Size(112, 219));
				physicsBody = cocos2d::PhysicsBody::createBox(cocos2d::Size(map->getTileSize().width, map->getTileSize().height));
				physicsBody->setDynamic(false);

				sprite->setPhysicsBody(physicsBody);


				// sprite will use physicsBody
				// map->getLayer("Meta")->setPhysicsBody(physicsBody);

				/*add contact event listener*/
				//auto contactListener = cocos2d::EventListenerPhysicsContact::create();
				//contactListener->onContactBegin = CC_CALLBACK_1(Tile::onContactBegin, this);
				//	Peli::Tile->addEventListenerWithSceneGraphPriority(contactListener, this);

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









//Point tileCoord = this->tileCoordForPosition(touch->getLocation()); 	// Get tileCoord location from the XY in terms tileditor map values.
//int tileGid = _meta->getTileGIDAt(tileCoord);  // Get the value from the reference based on tileCoord location. 
//
//if (tileGid)
//{
//	auto properties = map->getPropertiesForGID(tileGid); //if the tile is set to colliadble, it should return '0' which is marked in the Background02 file
//	if (properties.isNull())
//	{
//		log("COLLISION HIT");
//		CCLOG("%f", _meta->getPositionX());
//		CCLOG("%f", map->getLayer("Meta")->getPositionX());
//	}
//}
//return true;

