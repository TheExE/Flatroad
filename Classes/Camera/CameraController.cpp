#include "CameraController.h"
#include "../Character/Character.h"
#include "../GameStandart.h"

using namespace cocos2d;

bool CameraController::init(Camera* pMainCamera, Character* pCurCharacter)
{
	m_pCurCharacter = pCurCharacter;
	return true;
}
void CameraController::moveCameraTo(cocos2d::Vec2 worldPosition, float movementSpeed)
{
	// Move camera to input position
	Camera* defaultCamera = Camera::getDefaultCamera();
	Vec3 cameraPosition = defaultCamera->getPosition3D();
	Action* moveCamera = MoveTo::create(movementSpeed, Vec3(worldPosition.x, worldPosition.y,
		cameraPosition.z));
	moveCamera->setTag(MOVE_ACTION_TAG);
	// First stop any runing moving actions
	defaultCamera->stopActionByTag(MOVE_ACTION_TAG);
	// Then start new action
	defaultCamera->runAction(moveCamera);
}