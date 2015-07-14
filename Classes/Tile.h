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
		int tileAmount = 0;

		void loadMap(std::string level);
		void MapBoundariesTop(cocos2d::Layer *layer);
		void MapBoundariesRight(cocos2d::Layer *layer);
		void MapBoundariesLeft(cocos2d::Layer *layer);
		cocos2d::TMXTiledMap *getMap();
		cocos2d::Vec2 GetSpawnPosition();

		std::vector<cocos2d::Sprite*> tileCollisions;
	private:
		cocos2d::TMXTiledMap *map;
		cocos2d::TMXLayer *_background;
		cocos2d::TMXLayer *_meta;

		int mapWidth, mapHeight, tileWidth, tileHeight, collidableLayer, i, j = 0;
		int tileYPosition, tileXPosition;
		int AmountOfTilesInRow = 0;

		cocos2d::Vec2 SpawnPosition;
		cocos2d::Vec2 previousTilePosition;

		cocos2d::PhysicsBody *physicsBody;
		cocos2d::PhysicsBody *objectPhysicsBody;
		cocos2d::PhysicsBody *spikePhysicsBody;

		cocos2d::Vec2 *tileCoord;
		cocos2d::Sprite *sprite;
		bool onContactBegin(cocos2d::PhysicsContact &contact);

		std::vector<cocos2d::Vec2> TilesInRow;
	};
}
