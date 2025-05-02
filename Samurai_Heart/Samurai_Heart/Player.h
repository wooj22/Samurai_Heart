#pragma once
#include "Character.h"
#include "BaseState.h"
#include "../GameEngineLib/framework.h"

class Player : public Character
{
//protected:
//	// transform
//	Vector2 position;
//	float width;
//	float height;
//
//	// components
//	Rigidbody rigidbody;
//	BoxCollider collider;
//	Sprite* currentSprite;
//	AnimationClip* currentAnimation;

public:
	// [player state enum]
	enum PlayerState {
		IDLE, RUN, JUMP, WALL_JUMP, WALL_SLIDE,
		DASH, DEFENSE, HIT, DIE, ATTACK, SPECIAL_ATTACK
	};
	PlayerState curPlayerState;

private:
	// [player state]
	BaseState* curState;
	BaseState* stateArr[12] = {};

public:
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
	bool isDie;
	bool isHit;
	bool isFloor;
	bool isWall;
	bool isJumping;
	bool isDash;
	bool isMpEmpty;
	bool isChargeMax;

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

	// [player sprite]
	Sprite idleSprite;
	Sprite runSprite;
	Sprite jumpUpSprite;
	Sprite jumpDownSprite;
	Sprite WallSlideSprite;
	Sprite WallJumpSprite;
	Sprite DashSprite;
	Sprite DefenseSprite;
	Sprite HitSprite;
	Sprite DieSprite;
	Sprite Attack01Sprite;
	Sprite Attack02Sprite;
	Sprite Attack03Sprite;
	Sprite SpecialAttackSprite;

	// [player animation]
	AnimationClip idleAnimation;
	AnimationClip runAnimation;
	AnimationClip jumpUpAnimation;
	AnimationClip jumpDownAnimation;
	AnimationClip WallSlideAnimation;
	AnimationClip WallJumpAnimation;
	AnimationClip DashAnimation;
	AnimationClip DefenseAnimation;
	AnimationClip HitAnimation;
	AnimationClip DieAnimation;
	AnimationClip Attack01Animation;
	AnimationClip Attack02Animation;
	AnimationClip Attack03Animation;
	AnimationClip SpecialAttackAnimation;

public:
	Player() { OutputDebugStringA("Player Create\n"); }
	~Player() override {};

	void Start() override;
	void Update() override;
	void Render() override;

	// sprite & animation
	void PlayerSpriteInit();
	void PlayerAnimationInit();

	// fsm
	void StateInit();
	void ChangeState(PlayerState state);

	// update
	void KeyInputHandler();
	void ReSize();

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
};

