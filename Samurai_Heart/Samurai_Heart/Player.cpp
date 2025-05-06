#include "Player.h"
#include "Boss.h"

void Player::Start() 
{
	SpriteInit();
	AnimationInit();
	FSMInt();
	
	// ui init
	UIManager::Get().UpdatePlayerHP_Image(hp);
	UIManager::Get().UpdatePlayerChage_Image(charge);

	collider.SetTag(this->tag);
}

void Player::Update() 
{
	if (!isDie) {

		UpdateTimer();
		UpdateKeyInput();
		UpdateSize();
		UpdateScreenPos();

		// fsm update
		curState->ChangeStateLogic();
		curState->UpdateLogic();

		// rigidbody
		UpdateGravity();
		position += rigidbody.GetVelocity() * TimeManager::Get().GetDeltaTime();

		// 맵 경계 제어
		if (position.x <= mapPosXMin) position.x = 0 + width / 2;
		if (position.x >= mapWidth) position.x = mapWidth - width / 2;

		// collider
		collider.UpdateCollider(position, width, height);
		collider.UpdateScreenCollider(screenPosition, width, height);

	}

	// debug
	PlayerDebug();
}

void Player::Render()
{
	//collider.DrawCollider();

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
	dashSprite.Load(L"../Resource/Player/Dash.png");
	defenseSprite.Load(L"../Resource/Player/Defense.png");
	attack01Sprite.Load(L"../Resource/Player/Attack01.png");
	attack02Sprite.Load(L"../Resource/Player/Attack02.png");
	attack03Sprite.Load(L"../Resource/Player/Attack03.png");
	specialAttackSprite.Load(L"../Resource/Player/Attack04.png");
	hitSprite.Load(L"../Resource/Player/Hit.png");
	dieSprite.Load(L"../Resource/Player/Die.png");
	wallSlideSprite.Load(L"../Resource/Player/Wall.png");
	wallJumpSprite.Load(L"../Resource/Player/WallJumpUp.png");
}

// animation load
void Player::AnimationInit()
{
	// idle
	idleAnimation.LoadFrameDataFromFile("../Resource/Player/Idle.txt");
	idleAnimation.SetFrameDuration(0.1f);
	
	// run
	runAnimation.LoadFrameDataFromFile("../Resource/Player/Run.txt");
	runAnimation.SetFrameDuration(0.05f);

	// jump
	jumpAnimation.LoadFrameDataFromFile("../Resource/Player/JumpDown.txt");
	jumpAnimation.SetFrameDuration(0.8f);

	// dash
	// animation x

	// defecse
	// animation x

	// attack
	attack01Animation.LoadFrameDataFromFile("../Resource/Player/Attack01.txt");
	attack01Animation.SetFrameDuration(0.1f);

	attack02Animation.LoadFrameDataFromFile("../Resource/Player/Attack02.txt");
	attack02Animation.SetFrameDuration(0.1f);

	attack03Animation.LoadFrameDataFromFile("../Resource/Player/Attack03.txt");
	attack03Animation.SetFrameDuration(0.1f);

	// special attack
	specialAttackAnimation.LoadFrameDataFromFile("../Resource/Player/Attack04.txt");
	specialAttackAnimation.SetFrameDuration(0.15f);

	// hit
	hitAnimation.LoadFrameDataFromFile("../Resource/Player/Hit.txt");
	hitAnimation.SetFrameDuration(0.15f);

	// die
	dieAnimation.LoadFrameDataFromFile("../Resource/Player/Die.txt");
	dieAnimation.SetFrameDuration(0.15f);

	// wall slide
	wallSlideAnimation.LoadFrameDataFromFile("../Resource/Player/Wall.txt");
	wallSlideAnimation.SetFrameDuration(0.3f);
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
	stateArr[ATTACK] = new Attack(this);
	stateArr[SPECIAL_ATTACK] = new SpecialAttack(this);
	stateArr[HIT] = new Hit(this);
	stateArr[DIE] = new Die(this);
	stateArr[WALL_SLIDE] = new WallSlide(this);
	stateArr[WALL_JUMP] = new WallJump(this);

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
	DashCheak();

	// --- test ---
	/*if (InputManager::Get().GetKeyDown('K')) {
		TakeDamage(20);
	}*/
}

// Dash Cheak
void Player::DashCheak() {
	dashCheakTimer += TimeManager::Get().GetDeltaTime();

	// dash - left
	if (InputManager::Get().GetKeyDown(MoveLKey)) {
		if (lastLeftInputTime != -1.0f && dashCheakTimer < dashCheckInterval) {
			// 마지막 입력 이후 대시 체크 시간이 지났고, 두 번째 입력이라면
			leftInputCount++;
			if (leftInputCount == 2) {
				isDash = true;			// 대시 시작
				leftInputCount = 0;		// 카운트 초기화
				dashCheakTimer = 0.f;   // 대시 타이머 초기화
			}
		}
		else {
			leftInputCount = 1;
		}
		lastLeftInputTime = dashCheakTimer;
	}

	// dash - right
	if (InputManager::Get().GetKeyDown(MoveRKey)) {
		if (lastRightInputTime != -1.0f && dashCheakTimer < dashCheckInterval) {
			// 마지막 입력 이후 대시 체크 시간이 지났고, 두 번째 입력이라면
			rightInputCount++;
			if (rightInputCount == 2) {
				isDash = true;			// 대시 시작
				rightInputCount = 0;	// 카운트 초기화
				dashCheakTimer = 0.f;   // 대시 타이머 초기화
			}
		}
		else {
			rightInputCount = 1;
		}
		lastRightInputTime = dashCheakTimer;
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
void Player::UpdateScreenPos()
{
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

	// ui update
	UIManager::Get().UpdatePlayerChage_Image(charge);
}

// Charge downhp
void Player::ChargeZero()
{
	this->charge = 0;
	isChargeMax = false;

	// ui update
	UIManager::Get().UpdatePlayerChage_Image(charge);
}

// Collision check
bool Player::isCollision(BoxCollider other)
{
	string otherTag = other.GetTag();

	// isGround
	if (otherTag == "Ground")
	{
		if (this->collider.isCollision(other)) {
			this->isGround = true;

			// ground collider 최상단보다 아래일경우 보정
			if (collider.max.y > other.min.y)
			{
				float overlap = collider.max.y - other.min.y;
				position.y -= overlap;
			}

			rigidbody.SetVelocityY(0);
		}
		else {
			this->isGround = false;
		}

		return isGround;
	}

	// isWall
	if (otherTag == "Wall") 
	{
		return this->collider.isCollision(other);;
	}

	return this->collider.isCollision(other);
}

// Attack
void Player::DoAttack(int damage) {
	if (isCollision(boss->GetCollider())) {
		boss->TakeDamage(damage);
	}
}

// Hit event
void Player::TakeDamage(int damage) 
{
	// hit 상태인동안은 무적 (HIT STATE 제어)
	if (!isHit) {

		// damage
		if(isDefense) this->hp -= damage* defecseAverage;
		else {
			// flag (off는 HIT state를 나올때 처리)
			isHit = true;
			this->hp -= damage;
		}

		// state change
		if (this->hp <= 0)
		{
			hp = 0;
			//isDie = true;
			//this->Death();
			ChangeState(DIE);
		}
		else {
			if(!isDefense) ChangeState(HIT);
		}

		// ui update
		UIManager::Get().UpdatePlayerHP_Image(hp);

		// debug
		char hitBuffer[128];
		sprintf_s(hitBuffer, "# player Hit! [hp] : %d\n", hp);
		OutputDebugStringA(hitBuffer);
	}
}

// Die event
void Player::Death() 
{
	// fadeout 후 씬전환
	SceneManager::Get().ChangeScene(GameApp::MENU);
}


/*----- Debug ------*/
float debugtimer = 0;
float debugCooltime = 1.f;

// player debug
void Player::PlayerDebug() {
	debugtimer += TimeManager::Get().GetDeltaTime();

	if (debugtimer >= debugCooltime) {
		OutputDebugStringA("---- Plyaer Debug ----\n");
		// 현재 플레이어의 State
		std::string stateInfo = std::string("[Player State] ") + PlayerStateToString(curPlayerState) + "\n";
		OutputDebugStringA(stateInfo.c_str());

		// 현재 플레이어의 Hp
		char hpBuffer[123];
		sprintf_s(hpBuffer, "hp : %d\n", hp);
		OutputDebugStringA(hpBuffer);

		// 현재 플레이어의 Charge
		char chargeBuffer[123];
		sprintf_s(chargeBuffer, "charge : %d (is Cahrge? : %d)\n", charge, isChargeMax);
		OutputDebugStringA(chargeBuffer);

		// 현재 플레이어의 isDefense
		char defenseBuffer[123];
		sprintf_s(defenseBuffer, "is Defense? : %d\n", isDefense);
		OutputDebugStringA(defenseBuffer);

		// 현재 플레이어의 isGround
		char groundBuffer[128];
		sprintf_s(groundBuffer, "is Ground? : %d\n", isGround);
		OutputDebugStringA(groundBuffer);

		// 현재 플레이어의 isWall
		char wallBuffer[128];
		sprintf_s(wallBuffer, "is Wall? : %d\n", isWall);
		OutputDebugStringA(wallBuffer);

		// 현재 플레이어 position.x, position.y
		/*char posBuffer[128];
		sprintf_s(posBuffer, "Position: (%.2f, %.2f)\n", position.x, position.y);
		OutputDebugStringA(posBuffer);*/

		// 현재 플레이어 screenPosition.x, screenPosition.y
		/*char s_posBuffer[128];
		sprintf_s(s_posBuffer, "Scrren Position: (%.2f, %.2f)\n", screenPosition.x, screenPosition.y);
		OutputDebugStringA(s_posBuffer);*/

		// 현재 플레이어 width, height
		/*char sizeBuffer[128];
		sprintf_s(sizeBuffer, "Size: (%.2f, %.2f)\n", width, height);
		OutputDebugStringA(sizeBuffer);*/

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
	case RUN: return "RUN";
	case JUMP: return "Jump";
	case DASH: return "Dash";
	case DEFENSE: return "Defense";
	case ATTACK: return "Attack";
	case SPECIAL_ATTACK: return "Special Attack";
	case HIT: return "Hit";
	case DIE: return "Die";
	case WALL_SLIDE: return "Wall Slide";
	case WALL_JUMP: return "Wall Jump";
	default: return "Unknown";
	}
}