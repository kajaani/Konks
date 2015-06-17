#include "Tile.h"

Peli::Tile::Tile(cocos2d::Layer *layer)
{
	map = cocos2d::TMXTiledMap::create("Background02.tmx");
	_meta = map->layerNamed("Meta");
	_meta = map->layerNamed("Background");
	_meta = map->layerNamed("TileCats");
	_meta->setVisible(true);

	layer->addChild(map, 0);
}

void Peli::Tile::testFunc()
{

}
 
//cocos2d::Point Peli::Tile::tileCoordForPosition(cocos2d::CCPoint position)
//{
//	int x = position.x / map->getTileSize().width;
//	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
//	return cocos2d::Point(x, y);
//}
	/*
	for (i = 0; i < map->getWidth(); i++){
		for (j = 0; j < map->getHeight(); j++)
		{
			int tileCoord = new Point(i, j);
			int gid = map->getTileGIDAt(tileCoord);
			if (gid) {
				tileXPosition = i * tileWidth;
				tileYPosition = (mapHeight * tileHeight) - ((j + 1) tileHeight);
				// react = rect(tileXPosition, tileYPosition, tileWidth, tileHeight);
				
				// Creating sprites & collisions

				// create a static PhysicsBody
				auto physicsBody = PhysicsBody::createBox(Size(map->getTileWidth, map->getTileHeight), PhysicsMaterial(0.1f, 1.0f, 0.0f));
				physicsBody->setDynamic(false);



				//create a sprite
				auto sprite = Sprite::create("cat03.png");
				sprite->setPosition(Vec2(tileXPosition, tileYPosition)); 

				// sprite will use physicsBody
				sprite->setPhysicsBody(physicsBody);

				//add contact event listener
				auto contactListener = EventListenerPhysicsContact::create();
				contactListener->onContactBegin = CC_CALLBACK_1(onContactBegin, this);
				_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
			}
			*/







	

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

