#pragma once
#include <cassert>

/* [Singleton Ŭ����]
* �̱��� �ڵ带 ��Ȱ���Ͽ� ��Ӹ����� �� Ŭ������ �̱������� ���� �� �ִ�.
* - Class RenderManager : public Singleton<RenderManager> {};
* - RenderManager�� ����� ���� Singleton�����ڿ� ���� static RenderManager Instance�� ����Ƿ� �������� Ȱ���� �� �ִ�.
* - RenderManager::Get().DrawImage(bitmap, posX, posY);
*/

template <typename T>
class Singleton
{
private:
	static T* Instance;	

public:
	// ������
	Singleton()
	{
		assert(Instance == nullptr && "Singleton instance already created!");
		Instance = static_cast<T*>(this);
	}

	// �Ҹ���
	virtual ~Singleton() = default;

	// static ��ü ��ȯ
	static T& Get()
	{
		assert(Instance != nullptr && "Singleton instance not created!");
		return *Instance;
	}

	// ���� �� �̵� ����
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
};

template <typename T>
T* Singleton<T>::Instance = nullptr;