#include "cocos2d.h"
#include "Definitions.h"

namespace Peli
{
	class Tile
	{
	public:
		Tile(cocos2d::Layer *layer, std::string level);
		cocos2d::Point tileCoordForPosition(cocos2d::Point position);
		void testFunc();
		void CollisionCreator();
		int Width, Height = 0;

		void loadMap(std::string level);
		void MapBoundariesTop(cocos2d::Layer *layer);
		void MapBoundariesRight(cocos2d::Layer *layer);
		void MapBoundariesLeft(cocos2d::Layer *layer);
		cocos2d::TMXTiledMap *getMap();
		cocos2d::Vec2 GetSpawnPosition();
	private:
		cocos2d::TMXTiledMap *map;
		cocos2d::TMXLayer *_background;
		cocos2d::TMXLayer *_meta;
		cocos2d::Sprite *prevTile;


		int mapWidth, mapHeight, tileWidth, tileHeight, collidableLayer, i, j = 0;
		int tileYPosition, tileXPosition;

		cocos2d::Vec2 SpawnPosition;

		cocos2d::PhysicsBody *physicsBody;
		cocos2d::PhysicsBody *objectPhysicsBody;
		cocos2d::Vec2 *tileCoord;
		cocos2d::Sprite *sprite;
		bool onContactBegin(cocos2d::PhysicsContact &contact);
	};
}
