#include "Actor.h"

Actor::~Actor()
{
}

Actor::Actor()
{
	m_alive = true;
	m_health = 100;
	m_defense = 0;
	m_attack = 0;
	m_hitChance = 100;
	m_type = "actor";
}

float Actor::getDefense()
{
	return m_defense;
}

float Actor::getHealth()
{
	return m_health;
}

MyString Actor::getType()
{
	return m_type;
}

void Actor::setHealth(float hp)
{
	m_health = hp;
	if (m_health <= 0) {
		kill();
	}
}

bool Actor::alive()
{
	return m_alive;
}

void Actor::setDefense(float def)
{
	if (def >= 0) {
		m_defense = def;
	}
	else {
		m_defense = 0;
	}
}

void Actor::kill()
{
	m_alive = false;
}

