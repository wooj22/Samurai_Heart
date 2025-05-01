#include "pch.h"
#include "Scene.h"
#include "Object.h"

/// 씬에 등록된 모든 오브젝트 삭제
void Scene::Clear()
{
	for (auto& object : objectList)
	{
		delete object;
	}
	objectList.clear();

	/*for (auto& object : deletePendingObjectList)
	{
		delete object;
	}
	deletePendingObjectList.clear();*/
}

/// 씬에 등록된 모든 오브젝트 start 호출
void Scene::Start() {
	for (auto& object : objectList)
	{
		object->Start();
	}
}

/// 씬에 등록된 모든 오브젝트 update 호출
void Scene::Update()
{
	for (auto& object : objectList)
	{
		object->Update();
	}
}

/// 씬에 등록된 모든 오브젝트 render 호출
void Scene::Render()
{
	for (auto& object : objectList)
	{
		object->Render();
	}
}