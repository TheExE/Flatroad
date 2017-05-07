#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Camera/CameraController.h"
#include "GameStandart.h"
#include "Entities/Character/Character.h"
#include "System/Input/InputManager.h"
#include "UI/CharacterHUD.h"
#include "Entities/Enemy/Enemy.h"
#include <System/Utils/Utils.h>
#include "UI/SkillPlacmentHUD.h"
//#include <network\WebSocket.h>


USING_NS_CC;

using namespace cocostudio::timeline;


HelloWorld::~HelloWorld()
{
	// Free the memory to avoid leaks
	delete m_pWizardChar;
	delete m_pEnemy;
	delete m_pInputManager;
	delete m_pCharacterHUD;
	delete m_pCameraController;
}
Scene* HelloWorld::createScene()
{
	/*
	 * --- Example of websocket creation ---
	 * network::WebSocket* s = new network::WebSocket();
	*/


	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// init and add root node to this layer
	m_pRootNode = Node::create();
	addChild(m_pRootNode);


	// Create current worldmap
	auto map = TMXTiledMap::create(Utils::appendFullPathToAssetsPath(
		"TileMaps/Constantinapole/constantinapole.tmx"));
	m_pRootNode->addChild(map, Z_ORDER_WORLDMAP);

	Node* pEntityLayer = Node::create();
	// Create character
	m_pWizardChar = new Character();
	if (!m_pWizardChar->init("Configs/Characters/Wizard.xml"))
	{
		cocos2d::log("HelloWorldScene: %s", "Failed to initialize wiz character !");
	}
	else
	{
		pEntityLayer->addChild(m_pWizardChar);
	}

	// Add the entitie layer to root node before UI layer is added	
	m_pRootNode->addChild(pEntityLayer);


	// Setup client interface
	m_pCameraController = new CameraController();
	if (!m_pCameraController->init())
	{
		cocos2d::log("HelloWorldScene: %s", "Failed to initialize Camera Controller !");
	}

	auto uiLayer = Node::create();
	m_pInputManager = new InputManager();
	if (!m_pInputManager->init(uiLayer, this))
	{
		cocos2d::log("HelloWorldScene: Failed to initialize input manager !");
	}
	m_pCharacterHUD = new CharacterHUD();
	if (!m_pCharacterHUD->init("Configs/Characters/HUD.xml", m_pRootNode, uiLayer))
	{
		cocos2d::log("HelloWorldScene: Failed to initiazlize Character controller !");
	}

	// Load enemies
	m_pEnemy = new Enemy();
	if (!m_pEnemy->init("Configs/Enemies/Bunny.xml"))
	{
		cocos2d::log("HelloWorldScene: Failed to initialize Enemy!");
	}
	else
	{
		// Add the enemy to entities layer
		pEntityLayer->addChild(m_pEnemy);
	}

	// Scheduling update is necessarry to update enemy AI
	this->scheduleUpdate();

	return true;
}

void HelloWorld::update(float deltaTime) 
{
	m_pEnemy->update(deltaTime);
}

void HelloWorld::receiveMomentInput(cocos2d::Vec2 screenPosInput)
{
	// Cauculate move speed
	Vec2 clickInWorld = screenPositionToWorldPosition(screenPosInput);
	float distanceToTravel = m_pWizardChar->getPosition().distance(clickInWorld);
	float moveTime = distanceToTravel / CHARACTER_MOVE_SPEED;

	// Inform character and camera to move
	m_pWizardChar->onStartMoving(clickInWorld, moveTime);
	m_pCameraController->moveCameraTo(clickInWorld, moveTime);

	// Draw HUD point at target area
	m_pCharacterHUD->onMouseDown(clickInWorld, moveTime);
}
Node* HelloWorld::getRootNode()
{
	return m_pRootNode;
}
Vec2 HelloWorld::screenPositionToWorldPosition(cocos2d::Vec2 screenPosition) const
{
	Vec2 playerCharPos = m_pWizardChar->getPosition();
	return Vec2(playerCharPos.x + (screenPosition.x - (SCREEN_WIDTH / 2)),
		playerCharPos.y + ((screenPosition.y - (SCREEN_HEIGHT / 2)) * (-1)));
}
void HelloWorld::receivedKeyboardInput(cocos2d::EventKeyboard::KeyCode keyCode)
{
	SpellType spellType = None;

	// Find out which spell we need to cast
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_1:
		spellType = m_pCharacterHUD->getSpellTypeFromPlacementPos(Position_1);
			break;

	case EventKeyboard::KeyCode::KEY_2:
		spellType = m_pCharacterHUD->getSpellTypeFromPlacementPos(Position_2);
		break;

	case EventKeyboard::KeyCode::KEY_3:
		spellType = m_pCharacterHUD->getSpellTypeFromPlacementPos(Position_3);
		break;

	case EventKeyboard::KeyCode::KEY_4:
		spellType = m_pCharacterHUD->getSpellTypeFromPlacementPos(Position_4);
		break;

	case EventKeyboard::KeyCode::KEY_5:
		spellType = m_pCharacterHUD->getSpellTypeFromPlacementPos(Position_5);
		break;

	case EventKeyboard::KeyCode::KEY_6:
		spellType = m_pCharacterHUD->getSpellTypeFromPlacementPos(Position_6);
		break;

	case EventKeyboard::KeyCode::KEY_7:
		spellType = m_pCharacterHUD->getSpellTypeFromPlacementPos(Position_7);
		break;

	case EventKeyboard::KeyCode::KEY_8:
		spellType = m_pCharacterHUD->getSpellTypeFromPlacementPos(Position_8);
		break;

	case EventKeyboard::KeyCode::KEY_9:
		spellType = m_pCharacterHUD->getSpellTypeFromPlacementPos(Position_9);
		break;

	default:
		break;
	}

	// cast the spell
	m_pWizardChar->onShootSpell(Vec2::ANCHOR_TOP_LEFT, spellType);
}