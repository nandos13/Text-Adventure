#include "Enemy.h"
#include <time.h>

Enemy::~Enemy()
{
}

Enemy::Enemy(float hp, float def, int dmg)
{
	alive = true;
	health = hp;
	defense = def;
	attackDamage = dmg;
}

void Enemy::attack(Player * p)
{
	srand(time(NULL));
	float damage;
	damage = (30/250)*()*attackDamage;
}
