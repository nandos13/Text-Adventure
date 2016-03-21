#include "Player.h"
#include "Globals.h"

Player::~Player()
{
}

Player::Player(int posX, int posY)
{
	m_playerLoc->m_x = posX;
	m_playerLoc->m_y = posY;
	health = 25.0f;
	defense = 12.0f;
}

Player::Player()
{
	m_playerLoc->m_x = 0;
	m_playerLoc->m_y = 0;
	health = 25.0f;
	defense = 12.0f;
	alive = true;
}

void Player::setPlayerLocation(MapLocation loc)
{
	m_playerLoc->m_x = loc.m_x;
	m_playerLoc->m_y = loc.m_y;
	alive = true;
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

float Player::getHealth()
{
	return health;
}

void Player::setHealth(float hp)
{
	health = hp;
	if (health <= 0) {
		killPlayer();
	}
}

float Player::getDefense()
{
	return defense;
}

void Player::setDefense(float def)
{
	if (def >= 0) {
		defense = def;
	}
	else {
		defense = 0;
	}
}

void Player::killPlayer()
{
	alive = false;
	std::cout << "You died!" << std::endl;
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
