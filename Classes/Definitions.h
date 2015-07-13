#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

//Defines the time in seconds that
//BackgroundSprite is visible
#define DISPLAY_TIME_SPLASH_SCENE 2
#define TRANSITION_TIME 0.5

#define MAXDISTANCE 500

// Bitmasks for collision check
#define BITMASKTILE 0x01
#define BITMASKPLAYER 0x02
#define BITMASKCOLLISIONBOX 0x03
#define BITMASKROPE 0x04
#define BITMASKNONE 0x00

// Tags
#define PLAYER 0
#define TILE 1
#define GOAL 2
#define MAPNAME 3
#define HOOK 4
#define RAYCASTCOLLISIONBOX 5

#endif // __DEFINITIONS_H__
