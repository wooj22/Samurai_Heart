#include "Boss.h"
#include "Player.h"

void Boss::Start() 
{
	SpriteInit();
	AnimationInit();
	FSMInt();

	collider.SetTag(this->tag);
}

void Boss::Update() 
{
	UpdateTimer();
	UpdateSize();
	UpdateScreenPos();
	UpdatePlayerDist();
	UpdateDirection();

	// fsm update
	curState->ChangeStateLogic();
	curState->UpdateLogic();

	// rigidbody
	UpdateGravity();
	position += rigidbody.GetVelocity() * TimeManager::Get().GetDeltaTime();

	// collider
	collider.UpdateCollider(position, width, height);
	collider.UpdateScreenCollider(screenPosition, width, height);
}

void Boss::Render() 
{
	collider.DrawCollider();

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
	dieAnimation.SetFrameDuration(0.1f);

	// attack
	attack01Animation.LoadFrameDataFromFile("../Resource/Boss/Attack01.txt");
	attack01Animation.SetFrameDuration(0.1f);

	attack02Animation.LoadFrameDataFromFile("../Resource/Boss/Attack02.txt");
	attack02Animation.SetFrameDuration(0.1f);
}


/*-------------------- FSM --------------------*/
void Boss::FSMInt() {
	// fsm state class 등록
	stateArr[IDLE] = new BossIdle(this);
	stateArr[RUN] = new BossRun(this);
	stateArr[JUMP] = new BossJump(this);
	stateArr[ATTACK] = new BossAttack(this);

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
void Boss::UpdateTimer() 
{
	attackTimer += TimeManager::Get().GetDeltaTime();
}

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
	curDist = this->position.Distance(player->GetPosition());
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
			rigidbody.SetVelocityY(0);
		}
		else {
			this->isGround = false;
		}

		return isGround;
	}

	return this->collider.isCollision(other);
}

void Boss::TakeDamage(int damage) 
{
	// hit 상태인동안은 무적 (HIT STATE 제어)
	if (!isHit) {
		this->hp -= damage;
		isHit = true;

		if (this->hp <= 0)
		{
			hp = 0;
			isDie = true;
			this->Death();
			//ChangeState(DIE);
		}
		else {
			//ChangeState(HIT);
		}

		// debug
		char hitBuffer[128];
		sprintf_s(hitBuffer, "# boss Hit! [hp] : %d\n", hp);
		OutputDebugStringA(hitBuffer);
	}
}

void Boss::Death() 
{

}