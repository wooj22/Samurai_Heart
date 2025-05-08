#pragma once
#include "../GameEngineLib/Object.h"
#include "../GameEngineLib/Vector2.h"
#include "../GameEngineLib/framework.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Sprite.h"
#include "AnimationClip.h"
#include "Camera.h"
#include "BaseState.h"
#include "Idle.h"
#include "Run.h"
#include "Jump.h"
#include "Dash.h"
#include "Defense.h"
#include "Attack.h"
#include "SpecialAttack.h"
#include "Hit.h"
#include "Die.h"
#include "WallSlide.h"
#include "WallJump.h"
#include "UIManager.h"

class Boss;

class Player : public Object
{
private:
	// [boss]
	Boss* boss;

	// [player state]
	enum PlayerState {
		IDLE, RUN, JUMP, WALL_JUMP, WALL_SLIDE,
		DASH, DEFENSE, HIT, DIE, ATTACK, SPECIAL_ATTACK
	};
	PlayerState curPlayerState;
	string tag = "Player";

	BaseState* curState;
	BaseState* stateArr[11] = {};

	// [transform]
	Vector2 position;
	Vector2 screenPosition;
	float width;
	float height;
	
	float mapPosXMin = 0;
	float mapWidth;

	// [player stat]
	int		hp = 100;
	int		charge = 100;
	int 	power = 10;
	int		specialAttackPower = 100;
	float	speed = 200.f;
	float   dashSpeed = 900.f;
	float   wallSlideSpeed = 50.f;
	float	specialAttackSpeed = 700.f;
	float	jumpPower = 600.0f;
	float   defecseAverage = 0.1f;		// defense상태일때 hitDamage 절감
	float   gravity = 700.f;

	// [player gauge] - hp, charge
	int maxHp = 100;
	int	chargeMax = 100;

	// [player flag]
	bool isDie = false;
	bool isHit = false;
	bool isAttack = false;		
	bool isSpecialAttack = false;
	bool isDefense = false;
	bool isGround = false;
public:
	bool isWall = false;
private:
	bool isJumping = false;
	bool isDash = false;
	bool isChargeMax = true;

	// [direction controll]
	int wallDirection = 0;			// -1 left, 1 right
	int lastDirection = 0;			// -1 left, 1 right

	// [cool time & timer]
	float attackCoolTime = 0.5f;	// 일단 애니메이션 재생 시간으로 제어하는중..
	float attackTimer = 0.f;
	float dashCheckInterval = 1.7f;	    // 이 시간 안에 2번 눌렀다면 isDash ture
	float dashCheakTimer = 0.f;
	float dashTime = 0.3f;				// dash 유지시간
	float dashTimer = 0.f;				// dash 유지 체크 타이머
	float hitInvincibilityTime = 0.5f;	// 무적타임, hit 주기
	float hitInvincibilityTimer = 0.f;

	// [dash cheak]
	float lastLeftInputTime = -1.0f;     // 마지막 왼쪽 키 입력 시간
	float lastRightInputTime = -1.0f;    // 마지막 오른쪽 키 입력 시간
	int leftInputCount = 0;              // 왼쪽 연속 입력 횟수
	int rightInputCount = 0;             // 오른쪽 연속 입력 횟수

	// [player Key Input Flags]
	bool isMoveLKey;
	bool isMoveRKey;
	bool isJumpKey;
	bool isAttackKey;
	bool isSpecialAttackKey;
	bool isDefenseKey;

	// [key buliding]
	int MoveLKey = VK_LEFT;
	int MoveRKey = VK_RIGHT;
	int JumpKey = VK_SPACE;
	int AttackKey = 'D';
	int SpecialAttackKey = 'F';
	int DefenseKey = 'V';

	// components
	Rigidbody rigidbody;
	BoxCollider collider;
	Sprite* currentSprite;
	AnimationClip* currentAnimation;

	// [player sprite]
	Sprite idleSprite;
	Sprite runSprite;
	Sprite jumpSprite;
	Sprite wallSlideSprite;
	Sprite wallJumpSprite;
	Sprite dashSprite;
	Sprite defenseSprite;
	Sprite hitSprite;
	Sprite dieSprite;
	Sprite attack01Sprite;
	Sprite attack02Sprite;
	Sprite attack03Sprite;
	Sprite specialAttackSprite;

	// [player animation]
	AnimationClip idleAnimation;
	AnimationClip runAnimation;
	AnimationClip jumpAnimation;
	AnimationClip wallSlideAnimation;
	AnimationClip hitAnimation;
	AnimationClip dieAnimation;
	AnimationClip attack01Animation;
	AnimationClip attack02Animation;
	AnimationClip attack03Animation;
	AnimationClip specialAttackAnimation;

public:
	Player() { OutputDebugStringA("Player Create\n"); };
	~Player() override { OutputDebugStringA("Player Destory\n"); };

	void Start() override;
	void Update() override;
	void Render() override;

	// sprite & animation
	void SpriteInit();
	void AnimationInit();

	// fsm
	void FSMInt();
	void ChangeState(PlayerState state);

	// update
	void UpdateTimer();
	void UpdateKeyInput();
	void DashCheak();
	void UpdateSize();
	void UpdateScreenPos();
	void UpdateGravity();

	// player event
	void ChargeUp();
	void ChargeZero();
	void MpUp();
	void MpDown();
	bool isCollision(BoxCollider other);
	void DoAttack(int damage);
	void TakeDamage(int damage);
	void Death();

	// boss set
	void SetBoss(Boss* b) { boss = b; }
	
	// get & set
	void SetPosition(Vector2 pos) { position = pos; }
	void SetMapWidth(float width) { mapWidth = width; }
	Vector2 GetPosition() { return position; }
	string GetTag() { return tag; }
	int GetMaxHp() { return maxHp; }
	int GetMaxCharge() { return chargeMax; }
	BoxCollider GetCollider() { return collider; }

	// debug
	void PlayerDebug();
	const char* PlayerStateToString(PlayerState state);

	// fsm friend
	friend class BaseState;
	friend class Idle;
	friend class Run;
	friend class Jump;
	friend class Dash;
	friend class Defense;
	friend class Attack;
	friend class SpecialAttack;
	friend class Hit;
	friend class Die;
	friend class WallSlide;
	friend class WallJump;
};

