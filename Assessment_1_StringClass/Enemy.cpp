#include "Enemy.h"

Enemy::~Enemy()
{
}

Enemy::Enemy(int hp)
{
	alive = true;
	health = hp;
}

void Enemy::attack(Player * p)
{

}
