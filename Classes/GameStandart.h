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
static const int WAITE_BETWEEN_WANDER = 2;	// 2 - seconds

// Tags
static const int MOVE_ACTION_TAG = 1;
static const int WALK_ANIM_TAG = 2;
static const int MOVE_TARGET_ACTION_TAG = 3;
static const int MOVE_UI_ACTION_TAG = 4;

// XML KEYWORDS

		// Animation stuff
static const char* WALK_ANIM = "WalkAnim";
static const char* SPRITE_FRAME = "SpriteFrame";
		// Spell stuff
static const char* SPELL_LIST = "Spells";
static const char* FIRE_BOLT = "FireBolt";
static const char* ICE_BOLT = "IceBolt";
static const char* GROUND_BOLT = "GroundBolt";
static const char* PARTICLE = "Particle";
static const char* COLOR = "Color";
static const char* DAMAGE = "Damage";
static const char* RANGE = "Range";

// Enemys
static const char* ENEMY_BUNNY = "bunny";