#pragma once
#include <vector>
using namespace std;

/* [Scene Ŭ����]
* Scene�� ��ü�� �������� Ȱ���Ѵ�.
* ���� ���� ������������ Scene�� ��ӹ޴� �پ��� �� Ŭ����(Menu, Stage1, Stage2 ..)�� ����� Ȱ���ϰ�,
* �� ���� CreateObject()�� ���� ���� Ȱ��� ������Ʈ���� objects�� ����Ͽ� ���� �����Ѵ�.
* SceneManager���� ���� ���� Updete�� ȣ�� -> Scene���� ������Ʈ���� update ȣ�� 
*/

class Object;
class Scene
{
private:
	vector<Object*> objectList;				    // ���� ��ϵ� object list
	//vector<Object*> deletePendingObjectList;	// ���� �������� object list

public:
	Scene() = default;
	virtual ~Scene(){ Clear(); }

	template<typename T>
	T* CreateObject()
	{
		T* pObject = new T();
		objectList.push_back(pObject);
		return pObject;
	}

	template<typename T>
	void DeleteObject(T object)
	{
		auto it = find(objectList.begin(), objectList.end(), object);
		objectList.erase(it);	
	}

	void Clear();
	virtual void Start();
	virtual void Update();
	virtual void Render();
	virtual void Exit() { Clear(); }
};

// TODO :: deletePendingObjectList Ȱ�� ���� �м� �� �߰� �ڵ� �ۼ�