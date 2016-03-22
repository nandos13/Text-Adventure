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
	//Handle Input
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
			else if (str.subString(0, spaceLocation) == "equip") {
				MyString selectedWeapon = str.subString((spaceLocation + 1), (str.getLength() - (spaceLocation + 1)));
				p->equip(selectedWeapon);
			}
			else if (str.subString(0, spaceLocation) == "use") {
				MyString selectedItem = str.subString((spaceLocation + 1), (str.getLength() - (spaceLocation + 1)));
				p->useItem(selectedItem);
			}
		}
		else {
			std::cout << "Try that again!" << std::endl;
		}
	}
}

void Room::attackEnemy(std::vector<Room*>& m, Player * p)
{
	std::cout << "Nothing to attack here!" << std::endl;
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

LootRoom::LootRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, Item* itemLoot)
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

void LootRoom::loot(Item* i)
{
	m_loot = i;
}

void LootRoom::handleInput(MyString str, std::vector<Room*>& m, Player * p)
{
	if (str == "loot" || str == "pickup" || str == "pick up" || str == "equip") {
		//Check if this room has already been looted
		if (m_looted == true) {
			//No loot
			std::cout << "There is nothing to loot!" << std::endl;
		}
		else {
			//Add loot to player inventory and despawn loot in the room
			p->addItem(m_loot);
			std::cout << "You picked up: " << (m_loot->itemName()).stringOutput() << std::endl;
			//m_loot = new Item("empty");
			m_looted = true;
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

LootDoorRoom::LootDoorRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MapLocation toRoom, Item* itemLoot)
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
	else {
		Room::handleInput(str, m, p);
	}
}

CombatRoom::~CombatRoom()
{
}

CombatRoom::CombatRoom()
{
	m_roomType = "combat";
}

CombatRoom::CombatRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, Enemy * enemy)
{
	m_coord.m_x = posX;
	m_coord.m_y = posY;
	m_areaName = txtName;
	m_discoverText = txtDiscover;
	m_returnText = txtReturn;
	m_surroundingsText = txtSurroundings;
	m_roomType = "lootdoor";
	m_enemy.push_back(enemy);
}

bool CombatRoom::enemyIsAlive()
{
	return m_enemy.at(0)->alive();
}

void CombatRoom::handleInput(MyString str, std::vector<Room*>& m, Player * p)
{
	if (enemyIsAlive() == true) {
		if (str == "attack" || str == "hit") {
			if (enemyIsAlive() == true) {
				if ((p->equippedAmmo()) != 0) {
					p->attack(m_enemy.at(0));
					if ((p->equippedWeapon()) == true) {
						if ((p->equippedAmmo()) > 0) {
							p->useAmmo(1);
						}
					}
					(m_enemy.at(0))->attack(p);
				}
				else {
					std::cout << "*click* Out of ammo! Switch to another weapon, or use your fists." << std::endl;
				}
				//(m_enemy.at(0))->attack(p);
			}
		}
		else if (str == "run" || str == "flee") {
			p->move(p->getPreviousRoom(), m);
		}
		else {
			Room::handleInput(str, m, p);
		}
	}
	else {
		Room::handleInput(str, m, p);
	}
}

DoorCodeRoom::~DoorCodeRoom()
{
}

DoorCodeRoom::DoorCodeRoom()
{
	m_roomType = "doorcode";
	m_solution = "code";
	m_solution = randomizeCode(6);
}

DoorCodeRoom::DoorCodeRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MapLocation toRoom)
{
	m_coord.m_x = posX;
	m_coord.m_y = posY;
	m_areaName = txtName;
	m_discoverText = txtDiscover;
	m_returnText = txtReturn;
	m_surroundingsText = txtSurroundings;
	m_toRoom = toRoom;
	m_interior = false;
	m_solution = randomizeCode(6);
	m_roomType = "doorcode";
}

MyString DoorCodeRoom::randomizeCode(unsigned int digits)
{
	unsigned int i = digits;
	char c = 'a';
	MyString newSolution(digits + 1);
	while (i > 0) {
		int temp = (rand() % 43 + 48);
		if ((temp < 65) && (temp > 57)) { //Lies between ascii values for numerals and uppercase letters
			//Do nothing, repeat loop to generate new random character
		}
		else {
			//Use generated character
			c = temp;
			newSolution.setCharAtIndex((digits - i), c);
			newSolution.setCharAtIndex((digits - i) + 1, '\0');
			i--;
		}
	}
	return newSolution;
}

MyString DoorCodeRoom::code()
{
	return m_solution;
}
