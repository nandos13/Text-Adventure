#pragma once
#include "MyString.h"
#include "MapLocation.h"
#include "Inventory.h"
#include "Player.h"
class Room {
protected:
	MyString m_areaName = ""; //Name of the area
	MyString m_discoverText = ""; //Text displayed upon initial visit to Room
	MyString m_returnText = ""; //Text displayed upon returning to an already visited Room
	MyString m_surroundingsText = ""; //Text displayed when looking at surroundings
	MyString m_roomType = "default";
	bool m_discovered = false;
	bool m_canMoveNorth = true;
	bool m_canMoveSouth = true;
	bool m_canMoveEast = true;
	bool m_canMoveWest = true;
	bool m_locked = false;
	MapLocation m_coord;
public:
	~Room() {
		//DESTRUCTOR
	}
	Room() {
		//DEFAULT CONSTRUCTOR
	}
	Room(MapLocation loc) {
		m_coord.m_x = loc.m_x;
		m_coord.m_y = loc.m_y;
	}
	Room(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings) {
		m_coord.m_x = posX;
		m_coord.m_y = posY;
		m_areaName = txtName;
		m_discoverText = txtDiscover;
		m_returnText = txtReturn;
		m_surroundingsText = txtSurroundings;
	}
	void setName(MyString n) {
		m_areaName = n;
	}
	void setDiscoverText(MyString t) {
		m_discoverText = t;
	}
	void setReturnText(MyString t) {
		m_returnText = t;
	}
	void setSurroundingsText(MyString t) {
		m_surroundingsText = t;
	}
	void setDiscovered() {
		m_discovered = true;
	}
	bool discovered() {
		return m_discovered;
	}
	MyString discoverText() {
		return m_discoverText;
	}
	MyString returnText() {
		return m_returnText;
	}
	MyString surroundingsText() {
		return m_surroundingsText;
	}
	int getCoordX() {
		return m_coord.m_x;
	}
	int getCoordY() {
		return m_coord.m_y;
	}
	MapLocation getCoordinate() {
		return m_coord;
	}
	MyString getAreaName() {
		return m_areaName;
	}
	bool canMoveNorth() {
		return m_canMoveNorth;
	}
	bool canMoveEast() {
		return m_canMoveEast;
	}
	bool canMoveSouth() {
		return m_canMoveSouth;
	}
	bool canMoveWest() {
		return m_canMoveWest;
	}
	bool locked() {
		return m_locked;
	}
	MyString roomType() {
		return m_roomType;
	}
};

//SUBCLASSES------------------------------------------------------------------

class LootRoom : public Room {
private:
	Item m_loot;
	//ItemCLASS
public:
	//loot function
	~LootRoom() {

	}
	LootRoom() {
		//DEFAULT CONSTRUCTOR
		m_roomType = "loot";
	}
	LootRoom(MapLocation loc) {
		m_coord.m_x = loc.m_x;
		m_coord.m_y = loc.m_y;
		m_roomType = "loot";
	}
	LootRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, Item itemLoot) {
		m_coord.m_x = posX;
		m_coord.m_y = posY;
		m_areaName = txtName;
		m_discoverText = txtDiscover;
		m_returnText = txtReturn;
		m_surroundingsText = txtSurroundings;
		m_loot = itemLoot;
		m_roomType = "loot";
	}
	void loot(Item i) {
		m_loot = i;
	}
};
class DoorRoom : public Room {
private:
	MapLocation m_toRoom ;
public:

};