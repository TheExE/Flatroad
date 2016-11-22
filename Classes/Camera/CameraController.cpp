#include "CameraController.h"
#include "../Character/Character.h"

using namespace cocos2d;

bool CameraController::init(Camera* pMainCamera, Character* pCurCharacter)
{
	m_pMainCamera = pMainCamera;
	m_pCurCharacter = pCurCharacter;
	mCameraZCoord = pMainCamera->getPosition3D().z;

	return true;
}

void CameraController::update()
{
	Vec2 charPosition = m_pCurCharacter->getPosition();
	m_pCurCharacter->setPosition3D(Vec3(charPosition.x, charPosition.y, mCameraZCoord));
}