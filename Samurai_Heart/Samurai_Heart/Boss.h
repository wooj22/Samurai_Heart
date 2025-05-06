#pragma once
#include "../GameEngineLib/Object.h"
#include "../GameEngineLib/Vector2.h"
#include "../GameEngineLib/framework.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Sprite.h"
#include "AnimationClip.h"
#include "Camera.h"
#include "BossBaseState.h"
#include "BossIdle.h"
#include "BossRun.h"
#include "BossJump.h"
#include "BossAttack.h"
#include "BossHit.h"
#include "BossDie.h"

class Player;

// 보스 패턴
// default : IDLE
// curDist < 1000 일 경우 RUN
// curDist < 350 일 경우 ATTACK
// 플레이어에게 10번 공격당했을경우 direction 반대방향으로 Jump
// 플레이어에게 공격당했을 경우 Hit or Die

class Boss : public Object
{
private:
	// [Plyaer]
	Player* player;

	// [Boss state]
	enum BossState {
		IDLE, RUN, JUMP, HIT, DIE, ATTACK
	};
	BossState curBossState;
	string tag = "Boss";

	BossBaseState* curState;
	BossBaseState* stateArr[6] = {};
	
	// [Transform]
	Vector2 position;
	Vector2 screenPosition;
	float width;
	float height;

	// [Boss stat]
	int hp = 3000;
	int maxHp = 3000;
	int power = 10;
	float speed = 150.f;
	float jumpPower = 1000.f;
	float gravity = 700.f;

	// [Boss Ai data]
	float traceLimit = 1000.f;
	float attackLimit = 100.f;
	int hitCountLimit = 3;	// 10번 공격받으면 한번 도망치기

	// [Boss flag]
	bool isDie = false;
	bool isHit = false;
	bool isGround = false;
	bool isJumping = false;

	// [Controll]
	float distance = 0;	// player와의 거리
	int direction = 0;	// player 방향 -1 left, 1 right
	int hitCount = 0;

	// [Components]
	Rigidbody rigidbody;
	BoxCollider collider;
	Sprite* currentSprite;
	AnimationClip* currentAnimation;

	// [Boss Sprite]
	Sprite idleSprite;
	Sprite runSprite;
	Sprite jumpUpSprite;
	Sprite jumpDownSprite;
	Sprite hitSprite;
	Sprite dieSprite;
	Sprite attack01Sprite;
	Sprite attack02Sprite;

	// [Boss Animation]
	AnimationClip idleAnimation;
	AnimationClip runAnimation;
	AnimationClip jumpUpAnimation;
	AnimationClip jumpDownAnimation;
	AnimationClip hitAnimation;
	AnimationClip dieAnimation;
	AnimationClip attack01Animation;
	AnimationClip attack02Animation;

public:
	Boss() { OutputDebugStringA("Boss Create\n"); };
	~Boss() override { OutputDebugStringA("Boss Destory\n"); };

	void Start() override;
	void Update() override;
	void Render() override;

	// sprite & animation
	void SpriteInit();
	void AnimationInit();

	// fsm
	void FSMInt();
	void ChangeState(BossState state);

	// update
	void UpdateTimer();
	void UpdateSize();
	void UpdateScreenPos();
	void UpdateGravity();
	void UpdatePlayerDist();
	void UpdateDirection();

	// boss event
	bool isCollision(BoxCollider other);
	void DoAttack();
	void TakeDamage(int damage);
	void Death();

	// player set
	void SetPlayer(Player* p) { player = p; }

	// get & set
	void SetPosition(Vector2 pos) { position = pos; }
	Vector2 GetPosition() { return position; }
	string GetTag() { return tag; }
	BoxCollider GetCollider() { return collider; }

	// fsm class
	friend class BossIdle;
	friend class BossRun;
	friend class BossJump;
	friend class BossAttack;
	friend class BossHit;
	friend class BossDie;
};

