#include "Room.h"
#include "Player.h"
#include "Globals.h"

Room::~Room()
{
}

Room::Room()
{
}

Room::Room(MapLocation loc)
{
	m_coord.m_x = loc.m_x;
	m_coord.m_y = loc.m_y;
}

Room::Room(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings)
{
	m_coord.m_x = posX;
	m_coord.m_y = posY;
	m_areaName = txtName;
	m_discoverText = txtDiscover;
	m_returnText = txtReturn;
	m_surroundingsText = txtSurroundings;
}

void Room::setName(MyString n)
{
	m_areaName = n;
}

void Room::setDiscoverText(MyString t)
{
	m_discoverText = t;
}

void Room::setReturnText(MyString t)
{
	m_returnText = t;
}

void Room::setSurroundingsText(MyString t)
{
	m_surroundingsText = t;
}

void Room::setDiscovered()
{
	m_discovered = true;
}

bool Room::discovered()
{
	return m_discovered;
}

MyString Room::discoverText()
{
	return m_discoverText;
}

MyString Room::returnText()
{
	return m_returnText;
}

MyString Room::surroundingsText()
{
	return m_surroundingsText;
}

int Room::getCoordX()
{
	return m_coord.m_x;
}

int Room::getCoordY()
{
	return m_coord.m_y;
}

MapLocation Room::getCoordinate()
{
	return m_coord;
}

MyString Room::getAreaName()
{
	return m_areaName;
}

bool Room::canMoveNorth()
{
	return m_canMoveNorth;
}

void Room::canMoveNorth(bool b)
{
	m_canMoveNorth = b;
}

bool Room::canMoveEast()
{
	return m_canMoveEast;
}

void Room::canMoveEast(bool b)
{
	m_canMoveEast = b;
}

bool Room::canMoveSouth()
{
	return m_canMoveSouth;
}

void Room::canMoveSouth(bool b)
{
	m_canMoveSouth = b;
}

bool Room::canMoveWest()
{
	return m_canMoveWest;
}

void Room::canMoveWest(bool b)
{
	m_canMoveWest = b;
}

bool Room::locked()
{
	return m_locked;
}

void Room::locked(bool b)
{
	m_locked = b;
}

MyString Room::roomType()
{
	return m_roomType;
}

void Room::handleInput(MyString str, std::vector<Room*>& m, Player * p)
{
	// Default room code goes here
	if (str == "north" || str == "east" || str == "south" || str == "west") {
		p->move(str, m);
	}
	else if (str == "look" || str == "surroundings" || str == "explore") {
		std::cout << (m.at(p->findCurrentRoom(m, maxRooms))->surroundingsText()).stringOutput() << std::endl;
	}
	else if (str == "loot" || str == "pickup" || str == "pick up" || str == "equip") {
		std::cout << "There is nothing to loot!" << std::endl;
	}
	else {
		//Check for two-word commands (Eg. Move North)
		int spaceLocation = str.find(" "); //Locates the first space between words
		if (spaceLocation >= 0) {
			if (str.subString(0, spaceLocation) == "move" || str.subString(0, spaceLocation) == "walk") { //TODO: FINISH THIS FUNCTION
				MyString direction = str.subString((spaceLocation + 1), (str.getLength() - (spaceLocation + 1)));
				p->move(direction, m);
			}
		}
		else {
			std::cout << "Try that again!" << std::endl;
		}
	}
}

LootRoom::~LootRoom()
{
}

LootRoom::LootRoom()
{
	//DEFAULT CONSTRUCTOR
	m_roomType = "loot";
}

LootRoom::LootRoom(MapLocation loc)
{
	m_coord.m_x = loc.m_x;
	m_coord.m_y = loc.m_y;
	m_roomType = "loot";
}

LootRoom::LootRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, Item itemLoot)
{
	m_coord.m_x = posX;
	m_coord.m_y = posY;
	m_areaName = txtName;
	m_discoverText = txtDiscover;
	m_returnText = txtReturn;
	m_surroundingsText = txtSurroundings;
	m_loot = itemLoot;
	m_roomType = "loot";
}

void LootRoom::loot(Item i)
{
	m_loot = i;
}

void LootRoom::handleInput(MyString str, std::vector<Room*>& m, Player * p)
{
	if (str == "loot" || str == "pickup" || str == "pick up" || str == "equip") {
		//Check if this room has already been looted
		if (m_loot.itemID() == "empty") {
			//No loot
			std::cout << "There is nothing to loot!"  << std::endl;
		}
		else {
			//Add loot to player inventory and despawn loot in the room
			p->addItem(m_loot);
			if (m_loot.itemID() == "raft") { //Unlock Lake for sailing with boat
				m.at(4)->locked(false);
				m.at(5)->locked(false);
			}
			std::cout << "You picked up: " << (m_loot.itemName()).stringOutput() << std::endl;
			m_loot = Item("empty");
		}
	}
	else {
		//Call superclass methods
		Room::handleInput(str, m, p);
	}
}

bool DoorRoom::interior()
{
	return m_interior;
}

void DoorRoom::interior(bool b)
{
	m_interior = b;
}

DoorRoom::~DoorRoom()
{
}

DoorRoom::DoorRoom()
{
	m_roomType = "door";
}

DoorRoom::DoorRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MapLocation toRoom)
{
	m_coord.m_x = posX;
	m_coord.m_y = posY;
	m_areaName = txtName;
	m_discoverText = txtDiscover;
	m_returnText = txtReturn;
	m_surroundingsText = txtSurroundings;
	m_toRoom = toRoom;
	m_interior = false;
	m_roomType = "door";
}

void DoorRoom::handleInput(MyString str, std::vector<Room*>& m, Player * p)
{
	if ((m.at(p->findCurrentRoom(m, maxRooms))->getAreaName()).toLowercase() == "lake") {
		if (str == "south" || str == "enter" || str == "dock") {
			p->move(m_toRoom, m);
		}
		else {
			Room::handleInput(str, m, p);
		}
	}
	else {
		if ((m_interior == true && str == "leave") || (m_interior == false && str == "enter")) {
			p->move(m_toRoom, m);
		}
		else {
			Room::handleInput(str, m, p);
		}
	}
}

LootDoorRoom::~LootDoorRoom()
{
}

LootDoorRoom::LootDoorRoom()
{
	m_roomType = "lootdoor";
}

LootDoorRoom::LootDoorRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MapLocation toRoom, Item itemLoot)
{
	m_coord.m_x = posX;
	m_coord.m_y = posY;
	m_areaName = txtName;
	m_discoverText = txtDiscover;
	m_returnText = txtReturn;
	m_surroundingsText = txtSurroundings;
	m_toRoom = toRoom;
	m_interior = false;
	m_loot = itemLoot;
	m_roomType = "lootdoor";
}

void LootDoorRoom::handleInput(MyString str, std::vector<Room*>& m, Player * p)
{
	if (str == "loot" || str == "pickup" || str == "pick up" || str == "equip") {
		LootRoom::handleInput(str, m, p);
	}
	else if ((m_interior == true && str == "leave") || (m_interior == false && str == "enter")) {
		DoorRoom::handleInput(str, m, p);
	}
}
