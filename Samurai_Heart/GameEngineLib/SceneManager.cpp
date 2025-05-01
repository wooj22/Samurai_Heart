#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

/// SceneManager �ʱ�ȭ
void SceneManager::Init()
{
	if (currentScene)
		currentScene->Start();
}

/// SceneManager ����
void SceneManager::Release()
{
	for (auto& scene : sceneList)
	{
		delete scene;
	}
	sceneList.clear();
}

/// currentScene�� Update ȣ��
void SceneManager::Update()
{
	if (nextScene)
	{
		if (currentScene)
			currentScene->Exit();

		currentScene = nextScene;
		nextScene = nullptr;

		currentScene->Start();
	}

	if (currentScene)
		currentScene->Update();
}

/// currentScene�� Render ȣ��
void SceneManager::Render()
{
	if (currentScene)
		currentScene->Render();
}

/// Current Scene Set
void SceneManager::SetCurrentScene(size_t index) {
	if (index >= sceneList.size())
		return;

	currentScene = sceneList[index];
}

/// Current Scene get
Scene* SceneManager::GetCurrentScene() {
	return currentScene;
}

/// Scene Change
void SceneManager::ChangeScene(size_t index)
{
	if (index >= sceneList.size())
		return;

	nextScene = sceneList[index];
}

