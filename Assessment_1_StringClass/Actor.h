#pragma once
#include "MyString.h"
class Actor {
protected:
	float m_health;
	float m_defense;
	float m_attack;
	bool m_alive;
	MyString m_type;
	unsigned int m_hitChance;
public:
	virtual ~Actor();
	Actor();
	float getDefense();
	float getHealth();
	MyString getType();
	void setHealth(float hp);
	bool alive();
	void setDefense(float def);
	virtual void kill();
};