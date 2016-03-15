#include "Room.h"
#include "Player.h"
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

bool Room::canMoveEast()
{
	return m_canMoveEast;
}

bool Room::canMoveSouth()
{
	return m_canMoveSouth;
}

bool Room::canMoveWest()
{
	return m_canMoveWest;
}

bool Room::locked()
{
	return m_locked;
}

MyString Room::roomType()
{
	return m_roomType;
}

void Room::handleInput(MyString str, std::vector<Room*>& m, Player * p)
{
	// Default room code goes here
	unsigned int maxRooms = 3;
	if (str == "north" || str == "east" || str == "south" || str == "west") {
		p->move(str, m);
	}
	else if (str == "look" || str == "surroundings" || str == "explore") {
		std::cout << (m.at(p->findCurrentRoom(m, maxRooms))->surroundingsText()).stringOutput() << std::endl;
	}
	else if (str == "loot" || str == "pickup" || str == "pick up" || str == "equip") {
		std::cout << "There is nothing to loot!" << std::endl;
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
		if ((m_loot.itemID()).stringOutput()=="") { //TODO: FIX THIS
			//No loot
			std::cout << "There is nothing to loot!"  << std::endl;
		}
		else {
			p->addItem(m_loot);
			std::cout << "You picked up: " << (m_loot.itemName()).stringOutput() << std::endl;
			m_loot = Item("");
		}
	}
	else {
		// Call superclass methods
		Room::handleInput(str, m, p);
	}
}