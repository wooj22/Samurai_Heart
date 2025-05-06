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
	// ���� BGM ����
	if (bgm_sound) {
		bgm_sound->release();
		bgm_sound = nullptr;
	}

	// �� ���Ϸ� BGM �ε� (���� ��� ����)
	system->createSound(filePath, FMOD_LOOP_NORMAL, nullptr, &bgm_sound);

	// ���� ī��Ʈ ����(-1)�� ��������� ����
	if (bgm_sound) {
		bgm_sound->setMode(FMOD_LOOP_NORMAL);
		bgm_sound->setLoopCount(-1);
	}

	// ���
	system->playSound(bgm_sound, nullptr, false, &bgm_channel);
}

/// ���� play���� BGM Stop
void SoundManager::StopBGM() 
{
	if(bgm_channel) bgm_channel->stop();
}

/// SFX play
void SoundManager::PlaySFX(const char* filePath) 
{
	// �޸� ���� ����
	if (sfx_sound) {
		sfx_sound->release();
		sfx_sound = nullptr;
	}

	// �� file �޾Ƽ� play
	system->createSound(filePath, FMOD_DEFAULT, nullptr, &sfx_sound);
	system->playSound(sfx_sound, nullptr, false, &sfx_channel);
}

/// ���� play���� SFX Stop
void SoundManager::StopSFX() 
{
	if (sfx_channel)sfx_channel->stop();
}

/// ��ü sound Stop
void SoundManager::AllSoundStop() 
{
	if (bgm_channel) {
		bgm_channel->stop();
	}

	if (sfx_channel) {
		sfx_channel->stop();
	}
}