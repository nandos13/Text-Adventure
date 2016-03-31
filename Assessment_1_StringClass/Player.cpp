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
	m_hitChance = 94;
	m_previousRoom = MapLocation(0, 0);
	m_name = "Player";
	m_type = "player";
	m_inventory.push_back(new Weapon("fists"));
}

Player::Player()
{
	m_playerLoc->m_x = 0;
	m_playerLoc->m_y = 0;
	m_health = 25.0f;
	m_defense = 12.0f;
	m_attack = 5.0f;
	m_alive = true;
	m_hitChance = 94;
	m_previousRoom = MapLocation(0, 0);
	m_name = "Player";
	m_type = "player";
	m_inventory.push_back(new Weapon("fists"));
}

void Player::setPlayerLocation(MapLocation loc)
{
	m_playerLoc->m_x = loc.m_x;
	m_playerLoc->m_y = loc.m_y;
}

int Player::getPlayerLocX()
{
	return m_playerLoc->m_x;
}

int Player::getPlayerLocY()
{
	return m_playerLoc->m_y;
}

MapLocation Player::getPreviousRoom()
{
	return m_previousRoom;
}

void Player::addItem(Item* i)
{
	m_inventory.push_back(i);
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
			std::cout << "You equipped: " << ((m_inventory.at(m_equippedItem))->itemName()).stringOutput() << std::endl;
		}
		else {
			std::cout << "You can't equip this item." << std::endl;
		}
	}
}

void Player::useItem(MyString itemName)
{
	// Search inventory for this item
	int itemAtIndex = searchInventory(itemName);
	if (itemAtIndex == -1) { //Do not have this item
		std::cout << "You aren't currently holding this item." << std::endl;
	}
	else {
		if ((m_inventory.at(itemAtIndex))->action() == "heal") {
			setHealth(getHealth() + ((m_inventory.at(itemAtIndex))->value()));
			std::cout << "You now have " << int(getHealth() + 1) << " health." << std::endl;
			m_inventory.erase((m_inventory.begin()+itemAtIndex));
		}
		else if ((m_inventory.at(itemAtIndex))->action() == "item") {
			if ((m_inventory.at(itemAtIndex))->itemID() == "water") {
				int keyAtIndex = searchInventory("webbedkey");
				if (keyAtIndex == -1) { //Do not have correct item
					std::cout << "You don't have anything to use this with." << std::endl;
				}
				else {
					m_inventory.erase((m_inventory.begin() + keyAtIndex)); //Removes web key from inventory
					Item *tempKeyItem = new Item("key");
					m_inventory.push_back(tempKeyItem);
					std::cout << "You cleaned the web covered key!" << std::endl;
				}
			}
		}
		else {
			std::cout << "You can't use this item right now." << std::endl;
		}
	}
}

unsigned int Player::inventorySize()
{
	return unsigned int(m_inventory.size());
}

int Player::equipped()
{
	return m_equippedItem;
}

bool Player::equippedWeapon()
{
	if ((m_inventory.at(m_equippedItem))->itemType() == "weapon") {
		return true;
	}
	else {
		return false;
	}
}

void Player::useAmmo(unsigned int i)
{
	(m_inventory.at(m_equippedItem))->useAmmo(i);
}

int Player::equippedAmmo()
{
	return ((m_inventory.at(m_equippedItem))->currentAmmo());
}

int Player::searchInventory(MyString itemName)
{
	int itemAtIndex = -1;
	for (unsigned int i = 0; i < m_inventory.size(); i++) {
		if ((m_inventory.at(i))->itemID() == itemName) {
			itemAtIndex = i;
			break;
		}
	}
	return itemAtIndex;
}

void Player::kill()
{
	m_alive = false;

	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, 12);
	std::cout << "You died!" << std::endl;
	SetConsoleTextAttribute(hColor, 7); //Resets text colour to white
	
	gamePlaying = false;
	Sleep(2000);
}

void Player::attack(Actor * p)
{
	float dmg;
	float modifier = 1;
	modifier = float(rand() % 36 + 95);
	modifier = float(modifier) / 100;
	dmg = (m_attack / p->getDefense())*((m_inventory.at(m_equippedItem))->damage() + 2) * modifier;
	if (unsigned int(rand() % 100 + 1) <= m_hitChance) {
		//Hit Attack

		//Check if fighting final boss
		if ((p->getType()) == "alienbroodmother") {
			//Check if weilding relic sword
			if ((m_inventory.at(m_equippedItem))->itemID() == "sword") {
				//Instant Kill
				std::cout << "Gripping the alien sword, you charge at the " << (p->name()).stringOutput() << ", piercing it's heart with great force. The " << (p->name()).stringOutput() << " shrieks in pain before collapsing on the cavern floor. It's body lay lifeless." << std::endl;
				p->setHealth(0);
			}
			else {
				//Normal Attack
				p->setHealth(p->getHealth() - dmg);
				if ((p->getHealth() > 0)) {
					std::cout << (p->name()).stringOutput() << " has " << int((p->getHealth()) + 1) << " health left." << std::endl;
				}
			}
		}
		else {
			//Normal Attack
			p->setHealth(p->getHealth() - dmg);
			if ((p->getHealth() > 0)) {
				std::cout << (p->name()).stringOutput() << " has " << int((p->getHealth()) + 1) << " health left." << std::endl;
			}
		}
	}
	else {
		//Miss Attack

		HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hColor, 2);
		std::cout << "You missed!" << std::endl;
		SetConsoleTextAttribute(hColor, 7); //Resets text colour to white
	}
}

void Player::visitRoom(int posX, int posY, std::vector<Room*>& m)
{
	//Store the room the player came from for when the user wishes to run from combat
	m_previousRoom.m_x = m_playerLoc->m_x;
	m_previousRoom.m_y = m_playerLoc->m_y;
	
	unsigned int roomToVisit = 0;
	roomToVisit = findRoomAt(posX, posY, m, maxRooms);
	setPlayerLocation(m.at(roomToVisit)->getCoordinate());
	//Print name of current room in a different text colour
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, 12);
	std::cout << ((m.at(roomToVisit)->getAreaName()).toUppercase()).stringOutput() << std::endl;
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
	m.at(findCurrentRoom(m, maxRooms))->doOnEnter(m, this);
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
	else {
		std::cout << "Locked!" << std::endl;
	}
}

void Player::winGame()
{
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, 14);
	std::cout << "*You won the game!*" << std::endl;
	SetConsoleTextAttribute(hColor, 7); //Resets text colour to white
	gamePlaying = false;
}
