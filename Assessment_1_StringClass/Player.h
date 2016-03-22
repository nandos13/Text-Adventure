#pragma once
#include "MapLocation.h"
#include <vector>
#include <Windows.h>
#include "Room.h"
#include "Actor.h"
class Player : public Actor{
private:
	MapLocation *m_playerLoc = new MapLocation(0, 0);
	std::vector<Item*> m_inventory;
	int m_equippedItem = 0;
	MapLocation m_previousRoom;
public:
	~Player();
	Player(int posX, int posY);
	Player();

	void setPlayerLocation(MapLocation loc); 

	int getPlayerLocX();
	int getPlayerLocY();
	MapLocation getPreviousRoom();
	void addItem(Item* i);
	void equip(MyString itemName);
	void useItem(MyString itemName);
	unsigned int inventorySize();
	int equipped();
	bool equippedWeapon();
	void useAmmo(unsigned int i);
	int equippedAmmo();
	int searchInventory(MyString itemName);
	virtual void kill();
	virtual void attack(Actor* p);
	void visitRoom(int posX, int posY, std::vector<Room*> &m);
	unsigned int findRoomAt(int posX, int posY, std::vector<Room*> &m, unsigned int maxRooms);
	unsigned int findCurrentRoom(std::vector<Room*>& m, unsigned int maxRooms);
	void move(MyString direction, std::vector<Room*> &m);
	void move(MapLocation mLoc, std::vector<Room*> &m);
};