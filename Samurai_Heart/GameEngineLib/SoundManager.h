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

// TODO :: 추가 개선
// 지금은 Play시마다 계속 파일경로를 받아와서 재생하고있는데
// 자료구조를 활용해서 첫 실행시 필요한 파일을 저장해두고
// 실행중에는 그 자료구조 안에서 파일을 찾아서 재생하는 방식으로 수정