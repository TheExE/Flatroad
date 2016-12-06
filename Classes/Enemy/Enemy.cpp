#include "Enemy.h"
#include "Libs/tinyxml2.h"


bool Enemy::init(const char* pPath)
{
	tinyxml2::XMLDocument doc;
	std::string path = "../Resources/res/";
	path.append(pPath);
	doc.LoadFile(path.c_str());
	tinyxml2::XMLNode* pRoot = doc.RootElement();
	if (!pRoot)
	{
		cocos2d::log("Enemy: Failed to load XML!");
	}

	return true;
}