#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

//Defines the time in seconds that
//BackgroundSprite is visible
#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 0.5
#define RESTART_TIME 0.5

// Maximum distance for rope
#define MAXDISTANCE 500


#define GRAVITY 2
#define RESTITUTION 1

// Bitmasks for collision check
#define BITMASKTILE 0x01
#define BITMASKPLAYER 0x02
#define BITMASKCOLLISIONBOX 0x03
#define BITMASKROPE 0x04
#define BITMASKSPIKE 0x05
#define BITMASKMETAL 0x06
#define BITMASKNONE 0x00

// Tags
#define PLAYER 0
#define TILE 1
#define GOAL 2
#define MAPNAME 3
#define HOOK 4
#define RAYCASTCOLLISIONBOX 5
#define SPIKE 6
#define METAL 7

#endif // __DEFINITIONS_H__
