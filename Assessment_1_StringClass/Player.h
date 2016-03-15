#pragma once
#include "MapLocation.h"
#include "Room.h"
#include <vector>
class Player {
private:
	bool m_alive = true;
	bool m_carryingShovel = false;
	bool m_carryingRaft = false;
	MapLocation m_playerLoc;
	std::vector<Item*> m_inventory;
public:
	~Player() {

	}
	Player(int posX, int posY) {
		m_playerLoc.m_x = posX;
		m_playerLoc.m_y = posY;
	}
	Player() {
		m_playerLoc.m_x = 0;
		m_playerLoc.m_y = 0;
	}

	void setPlayerLocation(MapLocation loc) {
		m_playerLoc.m_x = loc.m_x;
		m_playerLoc.m_y = loc.m_y;
	}
	int getPlayerLocX() {
		return m_playerLoc.m_x;
	}
	int getPlayerLocY() {
		return m_playerLoc.m_y;
	}
	void addItem(Item i) {
		m_inventory.push_back(new Item(i.itemID()));
	}
	void move(MyString direction) {
		
	}
};