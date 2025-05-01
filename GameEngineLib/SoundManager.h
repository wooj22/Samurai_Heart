#pragma once
#pragma comment(lib, "fmod_vc.lib")
#include <fmod.hpp>
#include "Singleton.h"
using namespace FMOD;

class SoundManager : public Singleton<SoundManager>
{
private:
	System* system = nullptr;
	Sound* bgm_sound = nullptr;
	Sound* sfx_sound = nullptr;
	Channel* bgm_channel = nullptr;
	Channel* sfx_channel = nullptr;

public:
	SoundManager() = default;
	~SoundManager() override = default;

	void Init();
	void Release();

	void PlayBGM(const char* filePath);
	void StopBGM();
	void PlaySFX(const char* filePath);
	void StopSFX();
	void AllSoundStop();
};

// TODO :: �߰� ����
// ������ Play�ø��� ��� ���ϰ�θ� �޾ƿͼ� ����ϰ��ִµ�
// �ڷᱸ���� Ȱ���ؼ� ù ����� �ʿ��� ������ �����صΰ�
// �����߿��� �� �ڷᱸ�� �ȿ��� ������ ã�Ƽ� ����ϴ� ������� ����