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

class Player : public Object
{
private:
	// [player state enum]
	enum PlayerState {
		IDLE, RUN, JUMP, WALL_JUMP, WALL_SLIDE,
		DASH, DEFENSE, HIT, DIE, ATTACK, SPECIAL_ATTACK
	};
	PlayerState curPlayerState;
	string tag = "Player";

	// [player state]
	BaseState* curState;
	BaseState* stateArr[12] = {};

	// transform
	Vector2 position;
	Vector2 screenPosition;
	float width;
	float height;

	// [player stat]
	int		hp = 100;
	int 	mp = 100;
	int		charge = 0;
	int 	power = 10;
	float	speed = 200.0f;
	float   dashSpeed = 500.0f;
	float   wallSlideSpeed = 100.0f;
	float	jumpPower = 300.0f;
	float   defecseAverage = 0.5f;
	float   gravity = 9.8f;

	// [player gauge] - hp, mp(dasyh, defences), charge
	int maxHp = 100;
	int maxMp = 100;
	int	chargeMax = 100;

	// [cool time & timer]
	float attackCoolTime = 0.5f;
	
	// [player flag]
	bool isDie = false;
	bool isHit = false;
	bool isFloor = false;
	bool isWall = false;
	bool isJumping = false;
	bool isDash = false;
	bool isMpEmpty = false;
	bool isChargeMax = false;

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
	Sprite jumpUpSprite;
	Sprite jumpDownSprite;
	/*Sprite WallSlideSprite;
	Sprite WallJumpSprite;
	Sprite DashSprite;
	Sprite DefenseSprite;
	Sprite HitSprite;
	Sprite DieSprite;
	Sprite Attack01Sprite;
	Sprite Attack02Sprite;
	Sprite Attack03Sprite;
	Sprite SpecialAttackSprite;*/

	// [player animation]
	AnimationClip idleAnimation;
	AnimationClip runAnimation;
	AnimationClip jumpUpAnimation;
	AnimationClip jumpDownAnimation;
	/*AnimationClip WallSlideAnimation;
	AnimationClip WallJumpAnimation;
	AnimationClip DashAnimation;
	AnimationClip DefenseAnimation;
	AnimationClip HitAnimation;
	AnimationClip DieAnimation;
	AnimationClip Attack01Animation;
	AnimationClip Attack02Animation;
	AnimationClip Attack03Animation;
	AnimationClip SpecialAttackAnimation;*/

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
	void KeyInputHandler();
	void ReSize();
	void SetScreenPosition();
	void GravityUpdate();

	// player event
	void ChargeUp();
	void ChargeDown();
	void MpUp();
	void MpDown();
	bool isCollision(BoxCollider other);
	void Hit(int damage);
	void Die();

	// get & set
	void SetPosition(Vector2 pos) { position = pos; }
	Vector2 GetPosition() { return position; }
	string GetTag() { return tag; }
	BoxCollider GetCollider() { return collider; }

	// debug
	void PlayerDebug();
	const char* PlayerStateToString(PlayerState state);

	// fsm friend
	friend class BaseState;
	friend class Idle;
	friend class Run;
	friend class Jump;
};

