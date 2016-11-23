#pragma once

#define DEBUG
#ifdef DEBUG
	#define MK_NEW new(1, __FILE__, __LINE__)
#else
	#define MK_NEW new
#endif

// Default values
static const int PI = 3.14159265359;
static const int SCREEN_WIDTH = 1200;
static const int SCREEN_HEIGHT = 800;
static const float CHARACTER_MOVE_SPEED = 200;
static const int RECT_DEF_COUNT = 4;

// Tags
static const int MOVE_ACTION_TAG = 1;
static const int WALK_ANIM_TAG = 2;

// XML KEYWORDS
static const char* WALK_ANIM = "WalkAnim";
static const char* SPRITE_FRAME = "SpriteFrame";
