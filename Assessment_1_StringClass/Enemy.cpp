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

Enemy::Enemy(MyString name, float hp, float def, float dmg)
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
	modifier = float(rand() % 45 + 80);
	modifier = float(modifier) / 100;
	dmg = (m_attack / p->getDefense())*(2) * modifier;
	if ((unsigned int(rand () % 100 + 1)) <= m_hitChance) {
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

Zombie::Zombie(MyString name, float hp, float def, float dmg)
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
	if ((unsigned int(rand() % 100 + 1)) <= m_chanceToHitSelf) {
		//Hit Self

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

Spider::Spider(MyString name, float hp, float def, float dmg)
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
	if ((unsigned int(rand() % 100 + 1)) <= m_chanceToDoubleHit) {
		//Double Hit

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

MotherSpider::MotherSpider(MyString name, float hp, float def, float dmg)
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
	if ((unsigned int(rand() % 100 + 1)) <= m_chanceToHeal) {
		//Heal Self
		int healAmount = ((int(m_health)) / 8) + 1;
		setHealth(getHealth() + healAmount);

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

Alien::~Alien()
{
}

Alien::Alien()
{
	m_name = "Sectoid";
	m_alive = true;
	m_health = 100;
	m_defense = 12;
	m_attack = 41;
	m_hitChance = 87;
	m_chanceToShoot = 16;
	m_type = "alien";
}

Alien::Alien(MyString name, float hp, float def, float dmg)
{
	m_name = name;
	m_alive = true;
	m_health = hp;
	m_defense = def;
	m_attack = dmg;
	m_hitChance = 87;
	m_chanceToShoot = 16;
	m_type = "alien";
}

void Alien::attack(Actor * p)
{
	if ((unsigned int(rand() % 100 + 1)) <= m_chanceToShoot) {
		//Shoot gun

		HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hColor, 13);
		std::cout << m_name.stringOutput() << " shoots a blast of plasma at you." << std::endl;
		SetConsoleTextAttribute(hColor, 7); //Resets text colour to white

		//Set higher damage, attack, and reset damage
		float temp = m_attack;
		m_attack = (m_attack * 1.5f);
		Enemy::attack(p);
		m_attack = temp;
	}
	else {
		Enemy::attack(p);
	}
}

AlienBroodmother::~AlienBroodmother()
{
}

AlienBroodmother::AlienBroodmother()
{
	m_name = "Broodmother";
	m_alive = true;
	m_health = 175;
	m_defense = 14;
	m_attack = 52;
	m_hitChance = 90;
	m_chanceToShoot = 16;
	m_chanceToImpale = 9;
	m_type = "alienbroodmother";
}

AlienBroodmother::AlienBroodmother(MyString name, float hp, float def, float dmg)
{
	m_name = name;
	m_alive = true;
	m_health = hp;
	m_defense = def;
	m_attack = dmg;
	m_hitChance = 90;
	m_chanceToShoot = 16;
	m_chanceToImpale = 9;
	m_type = "alienbroodmother";
}

void AlienBroodmother::attack(Actor * p)
{
	if ((unsigned int(rand() % 100 + 1)) <= m_chanceToImpale) {
		//Impale target

		HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hColor, 13);
		std::cout << m_name.stringOutput() << " lunges toward you and impales you through the chest!" << std::endl;
		SetConsoleTextAttribute(hColor, 7); //Resets text colour to white

		//Instantly kill target
		p->setHealth(0);
	}
	else {
		Alien::attack(p);
	}
}
