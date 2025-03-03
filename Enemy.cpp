#include "Enemy.h"
#include "./Stage.h"
#include "globals.h"
#include "Player.h"

Enemy::Enemy()
	:pos_({ CHA_WIDTH * 19,CHA_HEIGHT * 9 }), isAlive_(true)
{
	nextPos_ = pos_;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Point move = { 0,0 };

	Player* p = (Player*)FindGameObject<Player>();
	Point pPos = p->GetPos();

	if (nextPos_.x == pos_.x && nextPos_.y == pos_.y)
	{
		movePattern = rand() % 10;
		direction = rand() % 5;
	}
	
	int chipX = pos_.x / CHA_WIDTH;
	int chipY = pos_.y / CHA_HEIGHT;

	if (movePattern == 0)
	{
		if (pPos.x > pos_.x)
		{
			if (!HitToChip(pos_.x + CHA_WIDTH, pos_.y + CHA_HEIGHT / 2))
			{
				nextPos_ = { (chipX + 1) * CHA_WIDTH,chipY * CHA_HEIGHT };
				move = { 1,0 };
				return;
			}
		}
		else
		{
			if (!HitToChip(pos_.x - 1, pos_.y + CHA_HEIGHT / 2))
			{
				nextPos_ = { chipX * CHA_WIDTH,chipY * CHA_HEIGHT };
				move = { -1,0 };
				return;
			}
		}

		if (pPos.y > pos_.y)
		{
			if (!HitToChip(pos_.x + CHA_WIDTH / 2, pos_.y + CHA_HEIGHT))
			{
				nextPos_ = { chipX * CHA_WIDTH,(chipY + 1) * CHA_HEIGHT };
				move = { 0,1 };
				return;
			}
		}
		else
		{
			if (!HitToChip(pos_.x + CHA_WIDTH / 2, pos_.y - 1))
			{
				nextPos_ = { chipX * CHA_WIDTH,chipY * CHA_HEIGHT };
				move = { 0,-1 };
				return;
			}
		}
	}

	else
	{
		switch (direction)
		{
		case 1:
			if (!HitToChip(pos_.x + CHA_WIDTH, pos_.y + CHA_HEIGHT / 2))
			{
				nextPos_ = { (chipX + 1) * CHA_WIDTH,chipY * CHA_HEIGHT };
				move = { 1,0 };
			}
			break;
		case 2:
			if (!HitToChip(pos_.x + CHA_WIDTH / 2, pos_.y + CHA_HEIGHT) && pPos.y > pos_.y)
			{
				nextPos_ = { chipX * CHA_WIDTH,(chipY + 1) * CHA_HEIGHT };
				move = { 0,1 };
			}
			break;
		case 3:
			if (!HitToChip(pos_.x - 1, pos_.y + CHA_HEIGHT / 2))
			{
				nextPos_ = { chipX * CHA_WIDTH,chipY * CHA_HEIGHT };
				move = { -1,0 };
			}
			break;
		case 4:
			if (!HitToChip(pos_.x + CHA_WIDTH / 2, pos_.y - 1) && pPos.y <= pos_.y)
			{
				nextPos_ = { chipX * CHA_WIDTH,chipY * CHA_HEIGHT };
				move = { 0,-1 };
			}
			break;
		default:
			break;
		}
	}
	
	/*switch (direction)
	{
	case 1:
		if (!HitToChip(pos_.x + CHA_WIDTH,pos_.y + CHA_HEIGHT / 2))
		{
			nextPos_ = { (chipX + 1) * CHA_WIDTH,chipY * CHA_HEIGHT };
			move = { 1,0 };
		}
		break;
	case 2:
		if(!HitToChip(pos_.x + CHA_WIDTH / 2, pos_.y + CHA_HEIGHT) && pPos.y > pos_.y)
		{
			nextPos_ = { chipX * CHA_WIDTH,(chipY + 1) * CHA_HEIGHT };
			move = { 0,1 };
		}
		break;
	case 3:
		if (!HitToChip(pos_.x - 1, pos_.y + CHA_HEIGHT / 2))
		{
			nextPos_ = { chipX * CHA_WIDTH,chipY * CHA_HEIGHT };
			move = { -1,0 };
		}
		break;
	case 4:
		if(!HitToChip(pos_.x + CHA_WIDTH / 2, pos_.y - 1) && pPos.y <= pos_.y)
		{
			nextPos_ = { chipX * CHA_WIDTH,chipY * CHA_HEIGHT };
			move = { 0,-1 };
		}
		break;
	default:
		break;
	}*/

    pos_ = { pos_.x + move.x, pos_.y + move.y };

}

void Enemy::Draw()
{
	DrawBox(pos_.x, pos_.y, pos_.x + CHA_WIDTH, pos_.y + CHA_HEIGHT, GetColor(80, 89, 10), TRUE);
}

bool Enemy::CheckHit(const Rect& me, const Rect& other)
{

	return false;
}

bool Enemy::HitToChip(int _x, int _y)
{
	int chipX = _x / CHA_WIDTH;
	int chipY = _y / CHA_HEIGHT;


	Stage stage;
	Stage* stg = &stage;

	switch (stg->GetStageData(chipX, chipY))
	{
	case STAGE_OBJ::WALL:
		return true;
	default:
		break;
	}

	return false;
}
