#include "cocos2d.h"


namespace Peli
{
	class Tile
	{
	public:
		Tile(cocos2d::Layer *layer);
		cocos2d::Point tileCoordForPosition(cocos2d::CCPoint position);
		void testFunc();
	private:
		cocos2d::TMXTiledMap *map;
		cocos2d::TMXLayer *_background;
		cocos2d::TMXLayer *_meta;

		int mapWidth, mapHeight, tileWidth, tileHeight, collidableLayer, i, j;
		
	};
}