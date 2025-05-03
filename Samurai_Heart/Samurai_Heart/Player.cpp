#include "Player.h"
#include "Idle.h"
#include "Run.h"
#include "Jump.h"

void Player::Start() 
{
	PlayerSpriteInit();
	PlayerAnimationInit();
	StateInit();
}

void Player::Update() 
{
	KeyInputHandler();
	ReSize();
	collider.UpdateCollider(position, width, height);
	
	// fsm state update
	curState->ChangeStateLogic();
	curState->UpdateLogic();

	// debug
	PlayerDebug();
}

void Player::Render()
{
	collider.DrawCollider();

	// fsm state render
	curState->Render();
}


/*-------------------- Sprite & Animation --------------------*/
// sprite load
void Player::PlayerSpriteInit()
{
	idleSprite.Load(L"../Resource/Player/Idle.png");
	runSprite.Load(L"../Resource/Player/Run.png");
	jumpUpSprite.Load(L"../Resource/Player/JumpUp.png");
	jumpDownSprite.Load(L"../Resource/Player/JumpDown.png");
}

// animation load
void Player::PlayerAnimationInit()
{
	// idle
	idleAnimation.LoadFrameDataFromFile("../Resource/Player/Idle.txt");
	idleAnimation.SetFrameDuration(0.1f);
	
	// run
	runAnimation.LoadFrameDataFromFile("../Resource/Player/Run.txt");
	runAnimation.SetFrameDuration(0.1f);

	// jump down (jump up 1 frame)
	jumpDownAnimation.LoadFrameDataFromFile("../Resource/Player/JumpDown.txt");
	jumpDownAnimation.SetFrameDuration(0.1f);
}

/*-------------------- FSM --------------------*/
/// State Init
void Player::StateInit() 
{
	// fsm state class 등록
	stateArr[IDLE] = new Idle(this);
	stateArr[RUN] = new Run(this);
	stateArr[JUMP] = new Jump(this);

	// state set
	curPlayerState = IDLE;
	curState = stateArr[curPlayerState];
	ChangeState(curPlayerState);
}

/// State Change
void Player::ChangeState(PlayerState newState) 
{
	if (curState) curState->Exit();
	
	curPlayerState = newState;
	curState = stateArr[curPlayerState];
	curState->Enter();
}

/*-------------------- Update --------------------*/
/// Key Input Handler
void Player::KeyInputHandler() 
{
	// move key
	if (InputManager::Get().GetKeyDown(MoveLKey))
		isMoveLKey = true;
	if (InputManager::Get().GetKeyUP(MoveLKey))
		isMoveLKey = false;
	if (InputManager::Get().GetKeyDown(MoveRKey))
		isMoveRKey = true;
	if (InputManager::Get().GetKeyUP(MoveRKey))
		isMoveRKey = false;

	// jump key
	if (InputManager::Get().GetKeyDown(JumpKey))
		isJumpKey = true;
	if (InputManager::Get().GetKeyUP(JumpKey))
		isJumpKey = false;

	// attack key
	if (InputManager::Get().GetKeyDown(AttackKey))
		isAttackKey = true;
	if (InputManager::Get().GetKeyUP(AttackKey))
		isAttackKey = false;
	if (InputManager::Get().GetKeyDown(SpecialAttackKey))
		isSpecialAttackKey = true;
	if (InputManager::Get().GetKeyUP(SpecialAttackKey))
		isSpecialAttackKey = false;

	// defense key
	if (InputManager::Get().GetKeyDown(DefenseKey))
		isDefenseKey = true;
	if (InputManager::Get().GetKeyUP(DefenseKey))
		isDefenseKey = false;
}

/// ReSize
void Player::ReSize()
{
	width = currentSprite->GetFrameRect().Width;
	height = currentSprite->GetFrameRect().Height;
}

/*-------------------- Player Event --------------------*/
// Charge up hp
void Player::ChargeUp() 
{
	this->charge += 5;
	if (this->charge >= chargeMax)
	{
		this->charge = chargeMax;
		isChargeMax = true;
	}
	else
	{
		isChargeMax = false;
	}
}

// Charge downhp
void Player::ChargeDown()
{
	this->charge -= 5;
	if (this->charge <= 0)
	{
		this->charge = 0;
		isChargeMax = false;
	}
	else
	{
		isChargeMax = true;
	}
}

// MP up
void Player::MpUp() 
{
	this->mp += 5;
	if (this->mp >= maxMp)
	{
		this->mp = maxMp;
		isMpEmpty = false;
	}
	else
	{
		isMpEmpty = true;
	}
}

// MP down
void Player::MpDown()
{
	this->mp -= 5;
	if (this->mp <= 0)
	{
		this->mp = 0;
		isMpEmpty = true;
	}
	else
	{
		isMpEmpty = false;
	}
}

// Collision check
bool Player::isCollision(BoxCollider other)
{
	return this->collider.isCollision(other);
}

// Hit event
void Player::Hit(int damage) 
{
	this->hp -= damage;
	this->isHit = true;

	if (this->hp <= 0)
	{
		hp = 0;
		isDie = true;
		this->Die();
	}
}

// Die event
void Player::Die() 
{

}


/*----- Debug ------*/
float debugtimer = 0;
float debugCooltime = 0.1f;

// player debug
void Player::PlayerDebug() {
	debugtimer += TimeManager::Get().GetDeltaTime();

	if (debugtimer >= debugCooltime) {
		// 현재 플레이어의 State
		std::string stateInfo = std::string("[Player State] ") + PlayerStateToString(curPlayerState) + "\n";
		OutputDebugStringA(stateInfo.c_str());

		// 현재 플레이어 position.x, position.y
		char posBuffer[128];
		sprintf_s(posBuffer, "Position: (%.2f, %.2f)\n", position.x, position.y);
		OutputDebugStringA(posBuffer);

		// 현재 플레이어 width, height
		char sizeBuffer[128];
		sprintf_s(sizeBuffer, "Size: (%.2f, %.2f)\n", width, height);
		OutputDebugStringA(sizeBuffer);

		// currentAnimation의 프레임 정보
		Frame currentFrame = currentAnimation->GetCurrentFrame();
		char frameBuffer[128];
		sprintf_s(frameBuffer, "Current Animation Frame: x=%d, y=%d, w=%d, h=%d\n",
			currentFrame.x, currentFrame.y, currentFrame.width, currentFrame.height);
		OutputDebugStringA(frameBuffer);

		// currentSprite의 프레임 정보
		Rect spriteRect = currentSprite->GetFrameRect();
		char spriteRectBuffer[128];
		sprintf_s(spriteRectBuffer, "Current Sprite Frame Rect: x=%d, y=%d, w=%d, h=%d\n",
			spriteRect.X, spriteRect.Y, spriteRect.Width, spriteRect.Height);
		OutputDebugStringA(spriteRectBuffer);

		debugtimer = 0;
	}
}

// enum → 문자열 변환 함수
const char* Player::PlayerStateToString(PlayerState state)
{
	switch (state)
	{
	case IDLE: return "Idle";
	case RUN: return "Move";
	case JUMP: return "Jump";
	default: return "Unknown";
	}
}