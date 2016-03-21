#pragma once
class Player;
class Enemy {
protected:
	float m_health;
	float m_defense;
	int m_attack;
	bool m_alive;
public:
	~Enemy();
	Enemy(float hp, float def, int dmg);
	float getHealth();
	void setHealth(float hp);
	float getDefense();
	void setDefense(float def);
	void killEnemy();
	bool alive();
	virtual void attack(Player* p);
};