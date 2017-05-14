#pragma once

#define DEBUG
#ifdef DEBUG
	#define MK_NEW new(1, __FILE__, __LINE__)
#else
	#define MK_NEW new
#endif

// Default values
static const int PI = 3.14159265359;
static const int SCREEN_WIDTH = 900;
static const int SCREEN_HEIGHT = 600;
static const float CHARACTER_MOVE_SPEED = 200;
static const int RECT_DEF_COUNT = 4;
static const int WAITE_BETWEEN_WANDER = 2;	// 2 - seconds
static const int MAX_SKILL_IN_HUD = 9;
static const float SCALE = ((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);
static const float CELL_SIZE =  SCALE * 40.0f;
static const float BUNNY_SIZE = SCALE * 16.0f;

// Z order
static const int Z_ORDER_WORLDMAP = -2;
static const int Z_ORDER_WAYPOINT = -1;


// Tags
static const int MOVE_ACTION_TAG = 1;
static const int WALK_ANIM_TAG = 2;
static const int MOVE_TARGET_ACTION_TAG = 3;
static const int MOVE_UI_ACTION_TAG = 4; 

// XML KEYWORDS

		// Animation stuff
static const char* XML_WALK_ANIM = "WalkAnim";
static const char* XML_SPRITE_FRAME = "SpriteFrame";
		// Spell stuff
static const char* XML_SPELL_LIST = "Spells";
static const char* XML_FIRE_BOLT = "FireBolt";
static const char* XML_ICE_BOLT = "IceBolt";
static const char* XML_GROUND_BOLT = "GroundBolt";
static const char* XML_PARTICLE = "Particle";
static const char* XML_COLOR = "Color";
static const char* XML_DAMAGE = "Damage";
static const char* XML_RANGE = "Range";
		// Enemy stuff
static const char* XML_ENEMY_BUNNY = "Bunny";
static const char* XML_BASE_SPRITE = "BaseSprite";
static const char* XML_LEVEL = "Level";
static const char* XML_MOVE_SPEED = "MoveSpeed";
static const char* XML_RADIUS = "Radius";
		// HUD stuff
static const char* XML_WALKPOINT = "WalkPoint";
static const char* XML_SKILLPLACEMENT = "SkillPlacement";
static const char* XML_BG = "Background";
static const char* XML_CELL_BG = "CellBackground";