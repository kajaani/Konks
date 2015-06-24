#include "cocos2d.h"

using namespace std;

namespace Peli
{
	class Tile
	{
	public:
		Tile(cocos2d::Layer *layer, string level);
		cocos2d::Point tileCoordForPosition(cocos2d::CCPoint position);
		void testFunc();
	private:
		cocos2d::TMXTiledMap *map;
		cocos2d::TMXLayer *_background;
		cocos2d::TMXLayer *_meta;

		int mapWidth, mapHeight, tileWidth, tileHeight, collidableLayer, i, j;
	};
}