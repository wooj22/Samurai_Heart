#include "pch.h"
#include "SoundManager.h"

// FMOD System Init
void SoundManager::Init() 
{
	System_Create(&this->system);
	system->init(512, FMOD_INIT_NORMAL, nullptr);
}

// FMOD System Release
void SoundManager::Release() 
{
	if (bgm_sound) {
		bgm_sound->release();
		bgm_sound = nullptr;
	}

	if (sfx_sound) {
		sfx_sound->release();
		sfx_sound = nullptr;
	}

	if (system) {
		system->close();
		system->release();
		system = nullptr;
	}
}

/// BGM play
void SoundManager::PlayBGM(const char* filePath) 
{
	// 기존 BGM 해제
	if (bgm_sound) {
		bgm_sound->release();
		bgm_sound = nullptr;
	}

	// 새 파일로 BGM 로드 (루프 모드 설정)
	system->createSound(filePath, FMOD_LOOP_NORMAL, nullptr, &bgm_sound);

	// 루프 카운트 무한(-1)로 명시적으로 설정
	if (bgm_sound) {
		bgm_sound->setMode(FMOD_LOOP_NORMAL);
		bgm_sound->setLoopCount(-1);
	}

	// 재생
	system->playSound(bgm_sound, nullptr, false, &bgm_channel);
}

/// 현재 play중인 BGM Stop
void SoundManager::StopBGM() 
{
	if(bgm_channel) bgm_channel->stop();
}

/// SFX play
void SoundManager::PlaySFX(const char* filePath) 
{
	// 메모리 누수 방지
	if (sfx_sound) {
		sfx_sound->release();
		sfx_sound = nullptr;
	}

	// 새 file 받아서 play
	system->createSound(filePath, FMOD_DEFAULT, nullptr, &sfx_sound);
	system->playSound(sfx_sound, nullptr, false, &sfx_channel);
}

/// 현재 play중인 SFX Stop
void SoundManager::StopSFX() 
{
	if (sfx_channel)sfx_channel->stop();
}

/// 전체 sound Stop
void SoundManager::AllSoundStop() 
{
	if (bgm_channel) {
		bgm_channel->stop();
	}

	if (sfx_channel) {
		sfx_channel->stop();
	}
}