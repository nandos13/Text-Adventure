#pragma once
#include "Actor.h"
class Player;
class Enemy : public Actor {
protected:
	
public:
	virtual  ~Enemy();
	Enemy();
	Enemy(MyString name, float hp, float def, float dmg);
	
	virtual void kill();
	virtual void attack(Actor* p);
};

class Zombie : public Enemy {
protected:
	unsigned int m_chanceToHitSelf;
public:
	virtual ~Zombie();
	Zombie();
	Zombie(MyString name, float hp, float def, float dmg);
	virtual void attack(Actor* p);
};

class Spider : public Enemy {
protected:
	unsigned int m_chanceToDoubleHit;
public:
	virtual ~Spider();
	Spider();
	Spider(MyString name, float hp, float def, float dmg);
	virtual void attack(Actor* p);
};

class MotherSpider : public Spider {
protected:
	unsigned int m_chanceToHeal;
public:
	virtual ~MotherSpider();
	MotherSpider();
	MotherSpider(MyString name, float hp, float def, float dmg);
	virtual void attack(Actor* p);
};