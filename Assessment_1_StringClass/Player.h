#pragma once
#include "MapLocation.h"
#include <vector>
#include <Windows.h>
class Room;  //Forward-Declaration of class Room, prevents circular dependency
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
	void visitRoom(int posX, int posY, std::vector<Room*> &m) {
		const int maxRooms = 3; //TODO: FIGURE OUT BETTER WAY TO DECLARE MAX SIZE OF MAP VECTOR
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
	unsigned int findRoomAt(int posX, int posY, std::vector<Room*> &m, unsigned int maxRooms) {
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
	void move(MyString direction, std::vector<Room*> &m) {
		const int maxRooms = 3; //TODO: FIGURE OUT BETTER WAY TO DECLARE MAX SIZE OF MAP VECTOR
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
};