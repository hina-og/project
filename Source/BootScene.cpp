#include "BootScene.h"
#include "../Library/SceneManager.h"

BootScene::BootScene()
{
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("PLAY"); // �N�����I�������Title��\��
}

void BootScene::Draw()
{
}
