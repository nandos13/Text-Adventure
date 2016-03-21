#include "Enemy.h"
#include "Player.h"
#include <time.h>

Enemy::~Enemy()
{
}

Enemy::Enemy(float hp, float def, int dmg)
{
	m_alive = true;
	m_health = hp;
	m_defense = def;
	m_attack = dmg;
}

float Enemy::getHealth()
{
	return m_health;
}

void Enemy::setHealth(float hp)
{
	m_health = hp;
	if (m_health <= 0) {
		killEnemy();
	}
}

float Enemy::getDefense()
{
	return m_defense;
}

void Enemy::setDefense(float def)
{
	if (def >= 0) {
		m_defense = def;
	}
	else {
		m_defense = 0;
	}
}

void Enemy::killEnemy()
{
	m_alive = false;
	std::cout << "You died!" << std::endl;
}

bool Enemy::alive()
{
	return m_alive;
}

void Enemy::attack(Player * p)
{
	srand(time(NULL));
	float dmg;
	dmg = (30 / 250)*(m_attack / p->getDefense())*(2);
}
