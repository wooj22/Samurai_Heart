#include "Player.h"
#include "Idle.h"
#include "Run.h"
#include "Jump.h"

void Player::Start() 
{
	SpriteInit();
	AnimationInit();
	FSMInt();

	collider.SetTag(this->tag);
}

void Player::Update() 
{
	UpdateTimer();
	UpdateKeyInput();
	UpdateSize();
	UpdateScreenPos();

	// fsm state update
	curState->ChangeStateLogic();
	curState->UpdateLogic();

	// rigidbody
	// 기본적으로 중력을 update하며 각 state에서 중력값을 setting
	// 이동 코드에 따라 velocity값을 setting하여 아래 로직에서 position에 더해짐
	UpdateGravity();
	position += rigidbody.GetVelocity() * TimeManager::Get().GetDeltaTime();

	// collider
	collider.UpdateCollider(position, width, height);
	collider.UpdateScreenCollider(screenPosition, width, height);

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
void Player::SpriteInit()
{
	idleSprite.Load(L"../Resource/Player/Idle.png");
	runSprite.Load(L"../Resource/Player/Run.png");
	jumpSprite.Load(L"../Resource/Player/JumpDown.png");
	DashSprite.Load(L"../Resource/Player/Dash.png");
	DefenseSprite.Load(L"../Resource/Player/Defense.png");
}

// animation load
void Player::AnimationInit()
{
	// idle
	idleAnimation.LoadFrameDataFromFile("../Resource/Player/Idle.txt");
	idleAnimation.SetFrameDuration(0.1f);
	
	// run
	runAnimation.LoadFrameDataFromFile("../Resource/Player/Run.txt");
	runAnimation.SetFrameDuration(0.1f);

	// jump
	jumpAnimation.LoadFrameDataFromFile("../Resource/Player/JumpDown.txt");
	jumpAnimation.SetFrameDuration(0.1f);

	// dash
	// animation x

	// defecse
	// animation x
}

/*-------------------- FSM --------------------*/
/// State Init
void Player::FSMInt() 
{
	// fsm state class 등록
	stateArr[IDLE] = new Idle(this);
	stateArr[RUN] = new Run(this);
	stateArr[JUMP] = new Jump(this);
	stateArr[DASH] = new Dash(this);
	stateArr[DEFENSE] = new Defense(this);

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
/// Timer
void Player::UpdateTimer() 
{
	attackTimer += TimeManager::Get().GetDeltaTime();
	dashCheakTimer += TimeManager::Get().GetDeltaTime();
}

/// Key Input Handler
void Player::UpdateKeyInput() 
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

	// dash cheak
	// 시간 경과 체크
	dashCheakTimer += TimeManager::Get().GetDeltaTime();

	// 대시 입력 처리
	if (InputManager::Get().GetKeyDown(MoveLKey)) {
		// 왼쪽 키가 눌렸을 때 처리
		if (lastLeftInputTime != -1.0f && dashCheakTimer < dashCheckInterval) {
			// 마지막 입력 이후 대시 체크 시간이 지났고, 두 번째 입력이라면
			leftInputCount++;
			if (leftInputCount == 2) {
				isDash = true;  // 대시 시작
				leftInputCount = 0; // 카운트 초기화
				dashCheakTimer = 0.f;  // 대시 타이머 초기화
			}
		}
		else {
			leftInputCount = 1;  // 첫 번째 입력
		}
		lastLeftInputTime = dashCheakTimer;  // 마지막 입력 시간 갱신
	}

	if (InputManager::Get().GetKeyDown(MoveRKey)) {
		// 오른쪽 키가 눌렸을 때 처리
		if (lastRightInputTime != -1.0f && dashCheakTimer < dashCheckInterval) {
			// 마지막 입력 이후 대시 체크 시간이 지났고, 두 번째 입력이라면
			rightInputCount++;
			if (rightInputCount == 2) {
				isDash = true;  // 대시 시작
				rightInputCount = 0; // 카운트 초기화
				dashCheakTimer = 0.f;  // 대시 타이머 초기화
			}
		}
		else {
			rightInputCount = 1;  // 첫 번째 입력
		}
		lastRightInputTime = dashCheakTimer;  // 마지막 입력 시간 갱신
	}

	// 대시 타이머가 0.5초 이상이면 대시 상태 초기화
	if (dashCheakTimer > dashCheckInterval) {
		leftInputCount = 0;
		rightInputCount = 0;
		dashCheakTimer = 0.f;  // 타이머 초기화
	}
}

/// ReSize
void Player::UpdateSize()
{
	width = currentSprite->GetFrameRect().Width;
	height = currentSprite->GetFrameRect().Height;
}

// ScreenPosition Update
void Player::UpdateScreenPos() {
	screenPosition = Camera::Get().WorldToCameraPos(position);
}

// gravity
void Player::UpdateGravity() {
	if(!isGround)
		rigidbody.UpdateGravity(TimeManager::Get().GetDeltaTime());
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

// Collision check
bool Player::isCollision(BoxCollider other)
{
	if (other.GetTag() == "Ground")
	{
		if (this->collider.isCollision(other)) {
			this->isGround = true;
			rigidbody.SetVelocityY(0);
		}
		else {
			this->isGround = false;
		}
	}

	if (other.GetTag() == "Boss")
	{

	}

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
float debugCooltime = 0.5f;

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

		// 현재 플레이어 screenPosition.x, screenPosition.y
		char s_posBuffer[128];
		sprintf_s(s_posBuffer, "Scrren Position: (%.2f, %.2f)\n", screenPosition.x, screenPosition.y);
		OutputDebugStringA(s_posBuffer);

		// 현재 플레이어 width, height
		char sizeBuffer[128];
		sprintf_s(sizeBuffer, "Size: (%.2f, %.2f)\n", width, height);
		OutputDebugStringA(sizeBuffer);

		// 현재 플레이어의 isGround
		char groundBuffer[128];
		sprintf_s(groundBuffer, "is Ground : %d\n", isGround);
		OutputDebugStringA(groundBuffer);

		// currentAnimation의 프레임 정보
		/*Frame currentFrame = currentAnimation->GetCurrentFrame();
		char frameBuffer[128];
		sprintf_s(frameBuffer, "Current Animation Frame: x=%d, y=%d, w=%d, h=%d\n",
			currentFrame.x, currentFrame.y, currentFrame.width, currentFrame.height);
		OutputDebugStringA(frameBuffer);*/

		// currentSprite의 프레임 정보
		/*Rect spriteRect = currentSprite->GetFrameRect();
		char spriteRectBuffer[128];
		sprintf_s(spriteRectBuffer, "Current Sprite Frame Rect: x=%d, y=%d, w=%d, h=%d\n",
			spriteRect.X, spriteRect.Y, spriteRect.Width, spriteRect.Height);
		OutputDebugStringA(spriteRectBuffer);*/

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