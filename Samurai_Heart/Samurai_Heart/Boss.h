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

class Boss : public Object
{
private:
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
	int hp = 10000;
	int maxHp = 10000;
	int power = 10;
	float speed = 180.f;
	float jumpPower = 1000.f;
	float gravity = 700.f;

	// [Boss Ai data]
	float traceLimit = 300.f;
	float attackLimit = 150.f;

	// [Boss flag]
	bool isDie = false;
	bool isHit = false;
	bool isGround = false;
	bool isJumping = false;

	// [Controll]
	int lastDirection = 0;
	float curDist = 0;	// player客狼 芭府

	float attackCoolTime = 0.5f;		
	float attackTimer = 0.f;
	float hitInvincibilityTime = 0.5f;	// 公利鸥烙, hit 林扁
	float hitInvincibilityTimer = 0.f;

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

	// boss event
	bool isCollision(BoxCollider other);
	void TakeDamage(int damage);
	void Death();

	// get & set
	void SetPosition(Vector2 pos) { position = pos; }
	Vector2 GetPosition() { return position; }
	string GetTag() { return tag; }
	BoxCollider GetCollider() { return collider; }

	// fsm class
	friend class BossIdle;
	friend class BossRun;
	friend class BossJump;
};

