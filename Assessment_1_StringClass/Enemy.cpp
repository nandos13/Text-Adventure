#include "Enemy.h"
#include "Player.h"
#include <time.h>

Enemy::~Enemy()
{
}

Enemy::Enemy()
{
	m_name = "Enemy";
	m_alive = true;
	m_health = 100;
	m_defense = 10;
	m_attack = 15;
	m_hitChance = 80;
	m_type = "enemy";
}

Enemy::Enemy(MyString name, float hp, float def, int dmg)
{
	m_name = name;
	m_alive = true;
	m_health = hp;
	m_defense = def;
	m_attack = dmg;
	m_hitChance = 80;
	m_type = "enemy";
}

void Enemy::kill()
{
	m_alive = false;
	std::cout << m_name.stringOutput() << " died!" << std::endl;
}

void Enemy::attack(Actor * p)
{
	float dmg;
	float modifier = 1;
	modifier = (rand() % 45 + 80);
	modifier = float(modifier) / 100;
	dmg = (m_attack / p->getDefense())*(2) * modifier;
	if ((rand () % 100 + 1) <= m_hitChance) {
		//Hit Attack
		p->setHealth(p->getHealth() - dmg);
		if ((p->getHealth() > 0)) {
			if (p->getType() == "player") {
				std::cout << "You have " << int((p->getHealth()) + 1) << " health left." << std::endl;
			}
			else {
				std::cout << m_name.stringOutput() << " has " << int((p->getHealth()) + 1) << " health left." << std::endl;
			}
			
		}
	}
	else {
		//Miss Attack

		//Print name of current room in a different text colour
		HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hColor, 2);
		std::cout << m_name.stringOutput() << "'s attack missed!" << std::endl;
		SetConsoleTextAttribute(hColor, 7); //Resets text colour to white
	}
}

Zombie::~Zombie()
{
}

Zombie::Zombie()
{
	m_name = "Zombie";
	m_alive = true;
	m_health = 45;
	m_defense = 8;
	m_attack = 21;
	m_hitChance = 80;
	m_chanceToHitSelf = 10;
	m_type = "zombie";
}

Zombie::Zombie(MyString name, float hp, float def, int dmg)
{
	m_name = name;
	m_alive = true;
	m_health = hp;
	m_defense = def;
	m_attack = dmg;
	m_hitChance = 65;
	m_chanceToHitSelf = 10;
	m_type = "zombie";
}

void Zombie::attack(Actor * p)
{
	if ((rand() % 100 + 1) <= m_chanceToHitSelf) {
		//Hit Self

		//Print name of current room in a different text colour
		HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hColor, 13);
		std::cout << m_name.stringOutput() << " is hitting itself." << std::endl;
		SetConsoleTextAttribute(hColor, 7); //Resets text colour to white
		
		Enemy::attack(this);
	}
	else {
		Enemy::attack(p);
	}
}

Spider::~Spider()
{
}

Spider::Spider()
{
	m_name = "Spider";
	m_alive = true;
	m_health = 90;
	m_defense = 6;
	m_attack = 29;
	m_hitChance = 80;
	m_chanceToDoubleHit = 10;
	m_type = "spider";
}

Spider::Spider(MyString name, float hp, float def, int dmg)
{
	m_name = name;
	m_alive = true;
	m_health = hp;
	m_defense = def;
	m_attack = dmg;
	m_hitChance = 65;
	m_chanceToDoubleHit = 10;
	m_type = "spider";
}

void Spider::attack(Actor * p)
{
	if ((rand() % 100 + 1) <= m_chanceToDoubleHit) {
		//Double Hit

		//Print name of current room in a different text colour
		HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hColor, 13);
		std::cout << m_name.stringOutput() << " hits you twice." << std::endl;
		SetConsoleTextAttribute(hColor, 7); //Resets text colour to white

		Enemy::attack(p);
		Enemy::attack(p);
	}
	else {
		//Only Attack Once
		Enemy::attack(p);
	}
}

MotherSpider::~MotherSpider()
{
}

MotherSpider::MotherSpider()
{
	m_name = "Mother Spider";
	m_alive = true;
	m_health = 120;
	m_defense = 10;
	m_attack = 37;
	m_hitChance = 82;
	m_chanceToDoubleHit = 16;
	m_chanceToHeal = 12;
	m_type = "motherspider";
}

MotherSpider::MotherSpider(MyString name, float hp, float def, int dmg)
{
	m_name = name;
	m_alive = true;
	m_health = hp;
	m_defense = def;
	m_attack = dmg;
	m_hitChance = 65;
	m_chanceToDoubleHit = 10;
	m_chanceToHeal = 12;
	m_type = "motherspider";
}

void MotherSpider::attack(Actor * p)
{
	if ((rand() % 100 + 1) <= m_chanceToHeal) {
		//Heal Self
		int healAmount = (m_health / 8) + 1;
		setHealth(getHealth() + healAmount);

		//Print name of current room in a different text colour
		HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hColor, 13);
		std::cout << m_name.stringOutput() << " healed itself for " << healAmount << " health." << std::endl;
		SetConsoleTextAttribute(hColor, 7); //Resets text colour to white
	}
	else {
		//Standard Attack
		Spider::attack(p);
	}
}
