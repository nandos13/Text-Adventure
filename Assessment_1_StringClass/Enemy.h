#pragma once
#include "Player.h"
class Enemy {
protected:
	int health;
	bool alive;
public:
	~Enemy();
	Enemy(int hp);
	virtual void attack(Player* p);
};