#include "Player.h"
#include "Globals.h"
#include <time.h>

Player::~Player()
{
}

Player::Player(int posX, int posY)
{
	m_playerLoc->m_x = posX;
	m_playerLoc->m_y = posY;
	m_health = 25.0f;
	m_defense = 12.0f;
}

Player::Player()
{
	m_playerLoc->m_x = 0;
	m_playerLoc->m_y = 0;
	m_health = 25.0f;
	m_defense = 12.0f;
	m_alive = true;
	m_inventory.push_back(new Weapon("fists"));
}

void Player::setPlayerLocation(MapLocation loc)
{
	m_playerLoc->m_x = loc.m_x;
	m_playerLoc->m_y = loc.m_y;
	m_health = 25.0f;
	m_defense = 12.0f;
	m_alive = true;
	m_inventory.push_back(new Weapon("fists"));
}

int Player::getPlayerLocX()
{
	return m_playerLoc->m_x;
}

int Player::getPlayerLocY()
{
	return m_playerLoc->m_y;
}

void Player::addItem(Item i)
{
	m_inventory.push_back(new Item(i.itemID()));
}

void Player::equip(MyString itemName)
{
	// Search inventory for this item
	int itemAtIndex = searchInventory(itemName);
	if (itemAtIndex == -1) { //Do not have this item
		std::cout << "You aren't currently holding this item." << std::endl;
	}
	else {
		if ((m_inventory.at(itemAtIndex))->itemType() == "weapon") {
			m_equippedItem = itemAtIndex;
		}
		else {
			std::cout << "You can't equip this item." << std::endl;
		}
	}
}

int Player::searchInventory(MyString itemName)
{
	int itemAtIndex = -1;
	for (unsigned int i = 0; i < m_inventory.size(); i++) {
		if (m_inventory.at(i)->itemID() == itemName) {
			itemAtIndex = i;
			break;
		}
	}
	return itemAtIndex;
}

float Player::getHealth()
{
	return m_health;
}

void Player::setHealth(float hp)
{
	m_health = hp;
	if (m_health <= 0) {
		killPlayer();
	}
}

float Player::getDefense()
{
	return m_defense;
}

void Player::setDefense(float def)
{
	if (def >= 0) {
		m_defense = def;
	}
	else {
		m_defense = 0;
	}
}

void Player::killPlayer()
{
	m_alive = false;
	std::cout << "You died!" << std::endl;
}

void Player::attack(Enemy * p)
{
	srand(time(NULL));
	float dmg;
	dmg = (1)*(m_attack / p->getDefense())*((m_inventory.at(m_equippedItem))->damage() + 2);
	p->setHealth(p->getHealth() - dmg);
	std::cout << "Enemy has " << p->getHealth() << " health left." << std::endl;
}

void Player::visitRoom(int posX, int posY, std::vector<Room*>& m)
{
	unsigned int roomToVisit = 0;
	roomToVisit = findRoomAt(posX, posY, m, maxRooms);
	setPlayerLocation(m.at(roomToVisit)->getCoordinate());
	//Print name of current room in a different text colour
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, 12);
	std::cout << (m.at(roomToVisit)->getAreaName()).stringOutput() << std::endl;
	SetConsoleTextAttribute(hColor, 7); //Resets text colour to white
										//Check if previously visited and display appropriate message
	if (m.at(roomToVisit)->discovered() == false) {
		//Discovering for the first time
		m.at(roomToVisit)->setDiscovered();
		std::cout << (m.at(roomToVisit)->discoverText()).stringOutput() << std::endl;
	}
	else {
		std::cout << (m.at(roomToVisit)->returnText()).stringOutput() << std::endl;
	}
}

unsigned int Player::findRoomAt(int posX, int posY, std::vector<Room*>& m, unsigned int maxRooms)
{
	//Using posX and posY, find which room exists with those coordinates
	unsigned int i = 0, resultRoom = 0;
	while (i < maxRooms) {
		if ((m.at(i)->getCoordX() == posX) && (m.at(i)->getCoordY() == posY)) {
			resultRoom = i;
			break;
		}
		i++;
	}
	return resultRoom; //Returns index of room
}

unsigned int Player::findCurrentRoom(std::vector<Room*>& m, unsigned int maxRooms)
{
	return findRoomAt(getPlayerLocX(), getPlayerLocY(), m, maxRooms);
}

void Player::move(MyString direction, std::vector<Room*>& m)
{
	int currentRoom = findRoomAt(getPlayerLocX(), getPlayerLocY(), m, maxRooms);
	if (direction == "north") {
		if (m.at(currentRoom)->canMoveNorth() == true) {
			if (m.at(findRoomAt(getPlayerLocX(), (getPlayerLocY() + 1), m, maxRooms))->locked() == false) {
				visitRoom(getPlayerLocX(), (getPlayerLocY() + 1), m);
			}
			else {
				std::cout << "Locked!" << std::endl;
			}
		}
		else {
			std::cout << "You can't go that way!" << std::endl;
		}
	}
	else if (direction == "east") {
		if (m.at(currentRoom)->canMoveEast() == true) {
			if (m.at(findRoomAt((getPlayerLocX() + 1), getPlayerLocY(), m, maxRooms))->locked() == false) {
				visitRoom((getPlayerLocX() + 1), getPlayerLocY(), m);
			}
			else {
				std::cout << "Locked!" << std::endl;
			}
		}
		else {
			std::cout << "You can't go that way!" << std::endl;
		}
	}
	else if (direction == "south") {
		if (m.at(currentRoom)->canMoveSouth() == true) {
			if (m.at(findRoomAt(getPlayerLocX(), (getPlayerLocY() - 1), m, maxRooms))->locked() == false) {
				visitRoom(getPlayerLocX(), (getPlayerLocY() - 1), m);
			}
			else {
				std::cout << "Locked!" << std::endl;
			}
		}
		else {
			std::cout << "You can't go that way!" << std::endl;
		}
	}
	else if (direction == "west") {
		if (m.at(currentRoom)->canMoveWest() == true) {
			if (m.at(findRoomAt((getPlayerLocX() - 1), getPlayerLocY(), m, maxRooms))->locked() == false) {
				visitRoom((getPlayerLocX() - 1), getPlayerLocY(), m);
			}
			else {
				std::cout << "Locked!" << std::endl;
			}
		}
		else {
			std::cout << "You can't go that way!" << std::endl;
		}
	}
	else {
		std::cout << "Try that again!" << std::endl;
	}
}

void Player::move(MapLocation mLoc, std::vector<Room*>& m)
{
	int destinationRoom = findRoomAt(mLoc.m_x, mLoc.m_y, m, maxRooms);
	if (m.at(destinationRoom)->locked() == false) {
		visitRoom(mLoc.m_x, mLoc.m_y, m);
	}
}
