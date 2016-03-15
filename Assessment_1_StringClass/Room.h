#pragma once
#include "MyString.h"
#include "MapLocation.h"
#include "Inventory.h"
#include <vector>
class Player;		//Forward-Declaration of class Room, prevents circular dependency issue
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
	~Room();
	Room();
	Room(MapLocation loc);
	Room(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings);
	void setName(MyString n);
	void setDiscoverText(MyString t);
	void setReturnText(MyString t);
	void setSurroundingsText(MyString t);
	void setDiscovered();
	bool discovered();
	MyString discoverText();
	MyString returnText();
	MyString surroundingsText();
	int getCoordX();
	int getCoordY();
	MapLocation getCoordinate();
	MyString getAreaName();
	bool canMoveNorth();
	void canMoveNorth(bool b);
	bool canMoveEast();
	void canMoveEast(bool b);
	bool canMoveSouth();
	void canMoveSouth(bool b);
	bool canMoveWest();
	void canMoveWest(bool b);
	bool locked();
	MyString roomType();
	
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
	
};

//SUBCLASSES------------------------------------------------------------------

class LootRoom : public Room {
private:
	Item m_loot;
	//ItemCLASS
public:
	//loot function
	~LootRoom();
	LootRoom();
	LootRoom(MapLocation loc);
	LootRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, Item itemLoot);
	void loot(Item i);

	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);

};
class DoorRoom : public Room {
private:
	MapLocation m_toRoom;
	bool m_interior;
public:
	bool interior();
	void interior(bool b);
	~DoorRoom();
	DoorRoom();
	DoorRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MapLocation toRoom);
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
};