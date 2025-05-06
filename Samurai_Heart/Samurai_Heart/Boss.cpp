#include "Boss.h"
#include "Player.h"
#include "PlayScene.h"
#include "GameApp.h"

void Boss::Start() 
{
	SpriteInit();
	AnimationInit();
	FSMInt();

	collider.SetTag(this->tag);
}

void Boss::Update() 
{
	if (!isDie) {
		UpdateSize();
		UpdateScreenPos();

		// player trace data
		UpdatePlayerDist();
		UpdateDirection();

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
	//BossDebug();
}

void Boss::Render() 
{
	//collider.DrawCollider();

	// fsm render
	curState->Render();
}


/*-------------------- Sprite & Animation --------------------*/
void Boss::SpriteInit() {
	idleSprite.Load(L"../Resource/Boss/Idle.png");
	runSprite.Load(L"../Resource/Boss/Run.png");
	jumpUpSprite.Load(L"../Resource/Boss/JumpUp.png");
	jumpDownSprite.Load(L"../Resource/Boss/JumpDown.png");
	hitSprite.Load(L"../Resource/Boss/Hit.png");
	dieSprite.Load(L"../Resource/Boss/Die.png");
	attack01Sprite.Load(L"../Resource/Boss/Attack01.png");
	attack02Sprite.Load(L"../Resource/Boss/Attack02.png");
}

void Boss::AnimationInit() {
	// idle
	idleAnimation.LoadFrameDataFromFile("../Resource/Boss/Idle.txt");
	idleAnimation.SetFrameDuration(0.1f);

	// run
	runAnimation.LoadFrameDataFromFile("../Resource/Boss/Run.txt");
	runAnimation.SetFrameDuration(0.05f);

	// jump
	jumpUpAnimation.LoadFrameDataFromFile("../Resource/Boss/JumpUp.txt");
	jumpUpAnimation.SetFrameDuration(0.1f);

	jumpDownAnimation.LoadFrameDataFromFile("../Resource/Boss/JumpDown.txt");
	jumpDownAnimation.SetFrameDuration(0.1f);

	// hit
	hitAnimation.LoadFrameDataFromFile("../Resource/Boss/Hit.txt");
	hitAnimation.SetFrameDuration(0.1f);

	// die
	dieAnimation.LoadFrameDataFromFile("../Resource/Boss/Die.txt");
	dieAnimation.SetFrameDuration(0.3f);

	// attack
	attack01Animation.LoadFrameDataFromFile("../Resource/Boss/Attack01.txt");
	attack01Animation.SetFrameDuration(0.15f);

	attack02Animation.LoadFrameDataFromFile("../Resource/Boss/Attack02.txt");
	attack02Animation.SetFrameDuration(0.3f);
}


/*-------------------- FSM --------------------*/
void Boss::FSMInt() {
	// fsm state class 등록
	stateArr[IDLE] = new BossIdle(this);
	stateArr[RUN] = new BossRun(this);
	stateArr[JUMP] = new BossJump(this);
	stateArr[ATTACK] = new BossAttack(this);
	stateArr[HIT] = new BossHit(this);
	stateArr[DIE] = new BossDie(this);

	// state set
	curBossState = IDLE;
	curState = stateArr[curBossState];
	ChangeState(curBossState);
}

void Boss::ChangeState(BossState newState) {
	if (curState) curState->Exit();

	curBossState = newState;
	curState = stateArr[curBossState];
	curState->Enter();
}


/*-------------------- Update --------------------*/

void Boss::UpdateSize()
{
	width = currentSprite->GetFrameRect().Width;
	height = currentSprite->GetFrameRect().Height;
}

void Boss::UpdateScreenPos() 
{
	screenPosition = Camera::Get().WorldToCameraPos(position);
}

void Boss::UpdateGravity()
{
	if (!isGround)
		rigidbody.UpdateGravity(TimeManager::Get().GetDeltaTime());

}

void Boss::UpdatePlayerDist() {
	distance = this->position.Distance(player->GetPosition());
}

void Boss::UpdateDirection() {
	direction =
		this->position.x - player->GetPosition().x < 0 ? 1 : -1;
}

/*-------------------- Event --------------------*/
bool Boss::isCollision(BoxCollider other) 
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

	return this->collider.isCollision(other);
}

void Boss::DoAttack() {
	if (isCollision(player->GetCollider())) {
		player->TakeDamage(power);
	}
}

void Boss::TakeDamage(int damage) 
{
	// dmage
	this->hp -= damage;
	isHit = true;

	// player chage
	player->ChargeUp();
	
	// state
	if (this->hp <= 0)
	{
		hp = 0;
		//isDie = true;
		//this->Death();
		ChangeState(DIE);
	}
	else {
		// hit count
		hitCount++;
		if (hitCount >= hitCountLimit) {
			ChangeState(JUMP);
			hitCount = 0;
		}
		else {
			ChangeState(HIT);
		}
	}

	// ui update
	UIManager::Get().UpdateBossHP_Image(hp);

	// debug
	char hitBuffer[128];
	sprintf_s(hitBuffer, "# boss Hit! [hp] : %d\n", hp);
	OutputDebugStringA(hitBuffer);
}

void Boss::Death() 
{
	// fadeout 후 씬전환
	SceneManager::Get().ChangeScene(GameApp::MENU);
}


// debug
float b_debugtimer = 0;
float b_debugCooltime = 0.2f;

void Boss::BossDebug() 
{
	b_debugtimer += TimeManager::Get().GetDeltaTime();

	if (b_debugtimer >= b_debugCooltime)
	{
		OutputDebugStringA("---- Boss Debug ----\n");

		// State
		std::string stateInfo = std::string("[Boss State] ") + BossStateToString(curBossState) + "\n";
		OutputDebugStringA(stateInfo.c_str());

		// Hp
		char hpBuffer[123];
		sprintf_s(hpBuffer, "hp : %d\n", hp);
		OutputDebugStringA(hpBuffer);

		// hit count (jump)
		char hitBuffer[123];
		sprintf_s(hitBuffer, "hit count : %d\n", hitCount);
		OutputDebugStringA(hitBuffer);

		b_debugtimer = 0;
	}
}

const char* Boss::BossStateToString(BossState state)
{
	switch (state)
	{
	case IDLE: return "Idle";
	case RUN: return "RUN";
	case JUMP: return "Jump";
	case ATTACK: return "Attack";
	case HIT: return "Hit";
	case DIE: return "Die";
	default: return "Unknown";
	}
}