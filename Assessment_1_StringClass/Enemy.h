#pragma once
#include "Actor.h"
class Player;
class Enemy : public Actor {
protected:

	
public:
	virtual  ~Enemy();
	Enemy();
	Enemy(float hp, float def, int dmg);
	virtual void kill();
	virtual void attack(Actor* p);
};

class Zombie : public Enemy {
protected:
	unsigned int m_chanceToHitSelf;
public:
	virtual ~Zombie();
	Zombie();
	Zombie(float hp, float def, int dmg);
	virtual void attack(Actor* p);
};

class Spider : public Enemy {
protected:
	unsigned int m_chanceToDoubleHit;
public:
	virtual ~Spider();
	Spider();
	Spider(float hp, float def, int dmg);
	virtual void attack(Actor* p);
};