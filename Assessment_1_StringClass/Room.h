#pragma once
#include "MyString.h"
#include "MapLocation.h"
#include "Inventory.h"
#include "Enemy.h"
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
	virtual ~Room();
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
	void locked(bool b);
	MyString roomType();
	
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
	virtual void attackEnemy(std::vector<Room*>& m, Player* p);
	virtual MyString code();
	virtual void doOnEnter(std::vector<Room*>& m, Player * p);
	
};

//SUBCLASSES------------------------------------------------------------------

class LootRoom : public virtual Room {
protected:
	Item* m_loot;
	bool m_looted = false;
	//ItemCLASS
public:
	//loot function
	virtual ~LootRoom();
	LootRoom();
	LootRoom(MapLocation loc);
	LootRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, Item* itemLoot);
	void loot(Item* i);

	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);

};

class DoorRoom : public virtual Room {
protected:
	MapLocation m_toRoom;
	bool m_interior;
public:
	bool interior();
	void interior(bool b);
	virtual ~DoorRoom();
	DoorRoom();
	DoorRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MapLocation toRoom);
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
};

class LootDoorRoom : public LootRoom, public DoorRoom {
protected:

public:
	virtual ~LootDoorRoom();
	LootDoorRoom();
	LootDoorRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MapLocation toRoom, Item* itemLoot);
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player *p);
};

class CombatRoom : public virtual Room {
protected:
	std::vector<Enemy*> m_enemy;
public:
	virtual ~CombatRoom();
	CombatRoom();
	CombatRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, Enemy* enemy);
	bool enemyIsAlive();
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
};

class DoorCodeRoom : public DoorRoom {
protected:
	MyString m_solution;
	MyString m_unlockMessage;
public:
	virtual ~DoorCodeRoom();
	DoorCodeRoom();
	DoorCodeRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MapLocation toRoom, MyString txtUnlockMessage);
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
	MyString randomizeCode(unsigned int digits);
	virtual MyString code();
};

class InfoRoom : public virtual Room {
protected:
	MyString m_infoToDisplay;
public:
	virtual ~InfoRoom();
	InfoRoom();
	InfoRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MyString txtInfoToDisplay);
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
};

class InfoDoorRoom : public InfoRoom, public DoorRoom {
protected:

public:
	virtual ~InfoDoorRoom();
	InfoDoorRoom();
	InfoDoorRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MapLocation toRoom, MyString txtInfoToDisplay);
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
};

class TeleportRoom : public virtual Room {
protected:
	MapLocation m_toRoom;
public:
	virtual ~TeleportRoom();
	TeleportRoom();
	TeleportRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MapLocation toRoom);
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
	virtual void doOnEnter(std::vector<Room*>& m, Player * p);
};

class TrapRoom : public virtual Room {
protected:
	MyString m_action;
	MyString m_correctSolution;
	MyString m_actionMessage;
	MyString m_solutionMessage;
	bool m_neutralized;
	virtual void action(Player * p, MyString act);
public:
	virtual ~TrapRoom();
	TrapRoom();
	TrapRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MyString txtCorrectSolution, MyString txtAction, MyString txtActionMessage, MyString txtSolutionMessage);
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
};

class EndGameRoom : public TrapRoom {
protected:
	MyString m_incorrectSolution;
	MyString m_winAction;
	unsigned int m_tryCount;
public:
	virtual ~EndGameRoom();
	EndGameRoom();
	EndGameRoom(int posX, int posY, MyString txtName, MyString txtDiscover, MyString txtReturn, MyString txtSurroundings, MyString txtCorrectSolution, MyString txtAction, MyString txtActionMessage, MyString txtSolutionMessage, MyString txtIncorrectSolution, MyString txtWinAction);
	virtual void handleInput(MyString str, std::vector<Room*>& m, Player* p);
};