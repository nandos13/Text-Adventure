#pragma once
#include "Player.h"
class Enemy {
protected:
	float health;
	float defense;
	int attackDamage;
	bool alive;
public:
	~Enemy();
	Enemy(float hp, float def, int dmg);
	float getHealth();
	void setHealth(float hp);
	float getDefense();
	void setDefense(float def);
	virtual void attack(Player* p);
};