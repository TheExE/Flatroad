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
static const float CHARACTER_MOVE_SPEED = 50;
static const int RECT_DEF_COUNT = 4;

// Tags
static const int MOVE_ACTION_TAG = 1;
static const int WALK_ANIM_TAG = 2;

// XML parsing consts
static const char* WALK_ANIM = "Walk";
static const char* ATTACK_ANIM = "Attack";
static const char* IDLE_ANIM = "Idle";
static const char* SPRITE_SHEET = "SpriteSheet";
static const char* FILE_SOURCE = "Source";
static const char* ANIM_FRAME = "Frame";
static const char* SPRITE_SIZE = "Size";
static const char* SPRITE_POS = "Position";

// Type defs
class Actor;
class ActorComponent;
typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::shared_ptr<ActorComponent> StrongActorComponentPtr;
typedef std::weak_ptr<Actor> WeakActorPtr;

typedef unsigned int ActorId;
typedef unsigned int ComponentId;
static ActorId INVALID_ACTOR_ID = 0;
static ComponentId INVALID_COMPONENT_ID = 0;
