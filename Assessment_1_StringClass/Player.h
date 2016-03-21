#pragma once
#include "MapLocation.h"
#include <vector>
#include <Windows.h>
#include "Room.h"
class Player {
private:
	MapLocation *m_playerLoc = new MapLocation(0, 0);
	std::vector<Item*> m_inventory;
	float m_health;
	float m_defense;
	float m_attack;
	bool m_alive;
	int m_equippedItem = 0;
public:
	~Player();
	Player(int posX, int posY);
	Player();

	void setPlayerLocation(MapLocation loc); 

	int getPlayerLocX();
	int getPlayerLocY();
	void addItem(Item* i);
	void equip(MyString itemName);
	int searchInventory(MyString itemName);
	float getHealth();
	void setHealth(float hp);
	float getDefense();
	void setDefense(float def);
	void killPlayer();
	void attack(Enemy* p);
	void visitRoom(int posX, int posY, std::vector<Room*> &m);
	unsigned int findRoomAt(int posX, int posY, std::vector<Room*> &m, unsigned int maxRooms);
	unsigned int findCurrentRoom(std::vector<Room*>& m, unsigned int maxRooms);
	void move(MyString direction, std::vector<Room*> &m);
	void move(MapLocation mLoc, std::vector<Room*> &m);
};