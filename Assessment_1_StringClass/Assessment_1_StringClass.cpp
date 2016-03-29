// Assessment_1_StringClass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include "Globals.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
using namespace std;


//GLOBAL VARIABLES
fstream file;
bool gamePlaying = true;
bool devMode = false;


//STRING CLASS VALIDATION
void createFile(char* a) {
	file.open(a, ios_base::out);
	file.close();
}
void classTest(bool test, const char* description, unsigned int& passes, unsigned int& fails, ostream& output) {
	if (test==true) {
		output << description << "\nPASSED!" << endl;
		passes++;
	}
	else {
		output << description << "\n** FAILED!" << endl;
		fails++;
	}
}
float percentage(float a, float b) {
	float result = 0;
	result = (a / b);
	result = result * 100;
	return result;
}
void validateClass() {
	createFile("log.txt");
	unsigned int countPass = 0; unsigned int countFail = 0;

	file.open("log.txt", ios_base::app | ios_base::_Nocreate);
	if (file.is_open()) {
		//ALL TESTS GO HERE
		//classTest((true), "description", countPass, countFail, file);
		MyString s1("This is a test");
		classTest((s1.getLength() == 14), "Member function getLength returns number of characters in string", countPass, countFail, file);
		classTest((s1 == "This is a test"), "Constructor with const char* parameter test", countPass, countFail, file);
		MyString s2 = s1;
		classTest((s2 == s1), "Equal operator overloader", countPass, countFail, file);
		classTest((s1.getCharAtIndex(5)=='i'), "Get a character at any point in the string class", countPass, countFail, file);
		classTest((s1.subString(2, 5) == "is is"), "Get a substring from any point in the string class", countPass, countFail, file);
		MyString s3 = s1.stringAppend(", or is it?");
		classTest((s3 == "This is a test, or is it?"), "Append one string with another", countPass, countFail, file);
		MyString s4 = s1.stringPrepend("Did you know: ");
		classTest((s4 == "Did you know: This is a test"), "Prepend one string with another", countPass, countFail, file);
		const char* c1 = s1.stringOutput();
		classTest((c1 == s1.stringOutput()), "Return as basic constant C-style string", countPass, countFail, file);
		classTest((s1.toLowercase() == "this is a test"), "Converting string to lowercase", countPass, countFail, file);
		classTest((s1.toUppercase() == "THIS IS A TEST"), "Converting string to uppercase", countPass, countFail, file);
		classTest((s1.find("est") == 11), "Find the position of a substring within a string", countPass, countFail, file);
		classTest((s1.find("is", 3) == 5), "Find the position of a substring, after a given position in the string", countPass, countFail, file);
		s4 = s1;
		s4 = s4.subReplace(7, 1, " not ");
		classTest((s4 == "This is not a test"), "Replace a substring at a given position with another string", countPass, countFail, file);
		
		file << endl;
		file << countPass << " of " << countPass + countFail << " tests passed. Pass rate: " << percentage(float(countPass), float(countPass + countFail)) << "%" << endl;
		file.close();
	}
	else {
		cout << "Error opening log file" << endl;
	}
}

//TEXT ADVENTURE FUNCTIONS HERE
void initializeMap(vector<Room*> &m) {
	MyString txtName;
	MyString txtDiscover;
	MyString txtReturn;
	MyString txtSurroundings;
	MyString itemLoot;
	{ //1
		txtName = "Old Tree";
		txtDiscover = "You awake under the shade of a large tree, head pounding and body weak. The air is still, almost silent. Concentrating, you notice a faint humming sound resonating from a nearby barn that sits just a few short paces North down an old stony path. To the East lay a small and peaceful looking garden abundant with vibrant flowers. To your West is a dense, dark forest which wraps around to meet a lake to your South. \nGripping a low branch to support yourself with your left hand, you painfully summon the strength to stand. ";
		txtReturn = "You return to the large tree. It casts shade over a lush patch of grass, and you feel at rest as you approach. It's not hard to see how you fell asleep in this comfortable spot.";
		txtSurroundings = "An old barn lies to your North. To the East is a vibrant garden, and to the West, a dense forest. There is a large lake to your South.";
		m.push_back(new Room(0, 0, txtName, txtDiscover, txtReturn, txtSurroundings));
	}
	{ //2
		txtName = "Garden";
		txtDiscover = "A pleasant aroma overwhelms your senses as you approach the small garden. Between rows of assorted flowers lay a narrow gravel path lined with old bricks. Towards the East end of the garden, a heavy, rusted looking shovel is sticking out of the dirt. Beyond the shovel lies a shed, which you think might be worth exploring. The lake to your south still seems difficult to cross. Several meters to your North stands a sign post.";
		txtReturn = "You make your way back to the quaint garden.";
		txtSurroundings = "You can see a sign post to your North, an old shed to your East, and to your West lies the field where you woke up. There is a large lake to your South.";
		itemLoot = "shovel";
		Weapon *item = new Weapon(itemLoot);
		m.push_back(new LootRoom(1, 0, txtName, txtDiscover, txtReturn, txtSurroundings, item));
	}
	{ //3
		txtName = "Shed";
		txtDiscover = "The shed is decrepit and covered in spider webs. Left ajar, the tin door creaks in the wind. The interior is dark and you struggle to see what is inside. As you decide whether or not to enter, you survey your surroundings; Your South side is covered by a rocky hill which seems impossible to cross, and to your North you can see a small water well. The garden lies to your West.";
		txtReturn = "You return to the old shed.";
		txtSurroundings = "A small water well lies to your North. The garden sits to your West. Your South is covered by a steep rocky hill which looks too hard to climb. To your East is a large, bare paddock which stretches for a few kilometers at least. You don’t have the energy to walk that far.";
		DoorRoom *tempShedRoom = new DoorRoom(2, 0, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(3, 0));
		tempShedRoom->canMoveEast(false);
		tempShedRoom->canMoveSouth(false);
		tempShedRoom->interior(false);
		m.push_back(tempShedRoom);
	}
	{ //4
		txtName = "Inside Shed";
		txtDiscover = "As you open the door and step inside, sunlight shines through and reveals a dusty old raft propped up against the far wall of the shed. This might be useful.";
		txtReturn = "You again step inside the old shed.";
		txtSurroundings = "You peek out the window. Outside the shed, the small garden lies to the East. You can't see much else.";
		itemLoot = "raft";
		Item *item = new Item(itemLoot);
		LootDoorRoom *tempShedInteriorRoom = new LootDoorRoom(3, 0, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(2, 0), item);
		tempShedInteriorRoom->canMoveNorth(false);
		tempShedInteriorRoom->canMoveEast(false);
		tempShedInteriorRoom->canMoveSouth(false);
		tempShedInteriorRoom->canMoveWest(false);
		tempShedInteriorRoom->interior(true);
		m.push_back(tempShedInteriorRoom);
	}
	{ //5
		txtName = "Lake"; //Lake 1, under Spawn
		txtDiscover = "You sail out on to the lake. There's a small island in the center, which you could probably dock your raft at.";
		txtReturn = "You return to the lake.";
		txtSurroundings = "On the Northern shore you can see the large old tree you woke up under, and the garden.";
		DoorRoom *tempLakeRoom = new DoorRoom(0, -1, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(2, -2));
		tempLakeRoom->canMoveEast(false);
		tempLakeRoom->canMoveSouth(false);
		tempLakeRoom->canMoveWest(false);
		tempLakeRoom->interior(false);
		tempLakeRoom->locked(true);
		m.push_back(tempLakeRoom);
	}
	{ //6
		txtName = "Lake"; //Lake 2, under Garden
		txtDiscover = "You sail out on to the lake. There's a small island in the center, which you could probably dock your raft at.";
		txtReturn = "You return to the lake.";
		txtSurroundings = "On the Northern shore you can see the large old tree you woke up under, and the garden.";
		DoorRoom *tempLakeRoom = new DoorRoom(1, -1, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(2, -2));
		tempLakeRoom->canMoveEast(false);
		tempLakeRoom->canMoveSouth(false);
		tempLakeRoom->canMoveWest(false);
		tempLakeRoom->interior(false);
		tempLakeRoom->locked(true);
		m.push_back(tempLakeRoom);
	}
	{ //7
		txtName = "Island"; 
		txtDiscover = "The island is small and barren. A lonely timber table sits in the middle by some rocks. On the table is a bottle of strange glowing liquid, and a label that reads 'Health Potion'.";
		txtReturn = "You return to the Island.";
		txtSurroundings = "You should get back on your raft and leave this island once you're done here.";
		itemLoot = "potion";
		UseableItem *item = new UseableItem(itemLoot);
		LootDoorRoom *tempIslandRoom = new LootDoorRoom(2, -2, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(0, 0), item);
		tempIslandRoom->canMoveNorth(false);
		tempIslandRoom->canMoveEast(false);
		tempIslandRoom->canMoveSouth(false);
		tempIslandRoom->canMoveWest(false);
		tempIslandRoom->interior(true);
		m.push_back(tempIslandRoom);
	}
	{ //8
		txtName = "Barn Entrance";
		txtDiscover = "The barn stands tall and is very weathered. You try the front door: Locked! But there is a key hole in the front. You can still hear the humming coming from inside.";
		txtReturn = "TODO: return to Barn";
		txtSurroundings = "TODO: surroundings";
		DoorRoom *tempBarnRoom = new DoorRoom(0, 1, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(0, 2));
		tempBarnRoom->canMoveNorth(false);
		tempBarnRoom->canMoveWest(false);
		tempBarnRoom->interior(false);
		m.push_back(tempBarnRoom);
	}
	{ //9
		txtName = "Barn South";
		txtDiscover = "TODO: Inside Barn / Humming is louder";
		txtReturn = "TODO: return to Inside Barn";
		txtSurroundings = "TODO: surroundings";
		DoorRoom *tempInsideBarnRoom = new DoorRoom(0, 2, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(0, 1));
		tempInsideBarnRoom->canMoveEast(false);
		tempInsideBarnRoom->canMoveSouth(false);
		tempInsideBarnRoom->canMoveWest(false);
		tempInsideBarnRoom->interior(true);
		tempInsideBarnRoom->locked(true);
		m.push_back(tempInsideBarnRoom);
	}
	{ //10
		txtName = "Signpost";
		txtDiscover = "TODO: signpost";
		txtReturn = "TODO: return to signpost";
		txtSurroundings = "TODO: surroundings signpost";
		m.push_back(new Room(1, 1, txtName, txtDiscover, txtReturn, txtSurroundings));
	}
	{ //11
		txtName = "Field";
		txtDiscover = "A broken old water well stands in this field. As you approach, you see a plastic bottle of water sitting in the well's bucket. \nThe shed is to your South, the Signpost to your West, and there lies a very ominous looking hill to your North. A long and bare paddock stretches to your East. It's not worth going that way.";
		txtReturn = "TODO: return to field";
		txtSurroundings = "TODO: surroundings";
		itemLoot = "water";
		UseableItem *item = new UseableItem(itemLoot);
		LootRoom *tempFieldRoom = new LootRoom(2, 1, txtName, txtDiscover, txtReturn, txtSurroundings, item);
		tempFieldRoom->canMoveEast(false);
		m.push_back(tempFieldRoom);
	}
	{ //12
		txtName = "Corpse Hill";
		txtDiscover = "As you approach the hill, you notice a body slumped against an old barrel. Getting closer, the corpse's head jolts up, and the thing looks you in the eyes. Suddenly it is standing upright and shambling towards you. You prepare yourself for a fight.";
		txtReturn = "You return to the hill. Your first encounter with a zombie.";
		txtSurroundings = "TODO: Might be something useful behind the hill to the North.";
		Zombie *ptrEnemy = new Zombie();
		CombatRoom *tempCombatRoom = new CombatRoom(2, 2, txtName, txtDiscover, txtReturn, txtSurroundings, ptrEnemy);
		tempCombatRoom->canMoveEast(false);
		m.push_back(tempCombatRoom);
	}
	{ //13
		txtName = "Behind Corpse Hill";
		txtDiscover = "TODO: Theres a shotgun here";
		txtReturn = "TODO";
		txtSurroundings = "TODO";
		itemLoot = "shotgun";
		Weapon *item = new Weapon(itemLoot);
		LootRoom *tempLootRoom = new LootRoom(2, 3, txtName, txtDiscover, txtReturn, txtSurroundings, item);
		tempLootRoom->canMoveNorth(false);
		tempLootRoom->canMoveEast(false);
		tempLootRoom->canMoveWest(false);
		m.push_back(tempLootRoom);
	}
	{ //14
		txtName = "Spider Forest";
		txtDiscover = "TODO: Spider enemy approaches you. Fight.";
		txtReturn = "TODO";
		txtSurroundings = "TODO";
		Spider *ptrEnemy = new Spider();
		CombatRoom *tempCombatRoom = new CombatRoom(-1, 0, txtName, txtDiscover, txtReturn, txtSurroundings, ptrEnemy);
		tempCombatRoom->canMoveNorth(false);
		m.push_back(tempCombatRoom);
	}
	{ //15
		txtName = "Webbed Thicket";
		txtDiscover = "TODO";
		txtReturn = "TODO";
		txtSurroundings = "TODO";
		MotherSpider *ptrEnemy = new MotherSpider();
		CombatRoom *tempCombatRoom = new CombatRoom(-1, -1, txtName, txtDiscover, txtReturn, txtSurroundings, ptrEnemy);
		tempCombatRoom->canMoveEast(false);
		tempCombatRoom->canMoveWest(false);
		m.push_back(tempCombatRoom);
	}
	{ //16
		txtName = "Spider Lair";
		txtDiscover = "TODO";
		txtReturn = "TODO";
		txtSurroundings = "TODO";
		itemLoot = "webbedkey";
		Item *item = new Item(itemLoot);
		LootRoom *tempLootRoom = new LootRoom(-1, -2, txtName, txtDiscover, txtReturn, txtSurroundings, item);
		tempLootRoom->canMoveEast(false);
		tempLootRoom->canMoveWest(false);
		tempLootRoom->canMoveSouth(false);
		m.push_back(tempLootRoom);
	}
	{ //17
		txtName = "Mysterious Rock";
		txtDiscover = "A large, perfectly square boulder sits infront of you. A small seat is carved into the front face, and on it sits a bottle filled with a glowing pink liquid. A nearby tag reads 'Health Potion'";
		txtReturn = "TODO";
		txtSurroundings = "TODO";
		itemLoot = "potion";
		UseableItem *item = new UseableItem(itemLoot);
		LootRoom *tempLootRoom = new LootRoom(-2, 0, txtName, txtDiscover, txtReturn, txtSurroundings, item);
		tempLootRoom->canMoveNorth(false);
		tempLootRoom->canMoveWest(false);
		tempLootRoom->canMoveSouth(false);
		m.push_back(tempLootRoom);
	}
	{ //18
		txtName = "Cellar Entrance";
		txtDiscover = "TODO";
		txtReturn = "TODO";
		txtSurroundings = "TODO";
		DoorRoom *tempCryptExterior = new DoorRoom(1, 2, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(1, 3));
		tempCryptExterior->canMoveNorth(false);
		tempCryptExterior->canMoveWest(false);
		tempCryptExterior->interior(false);
		m.push_back(tempCryptExterior);
	}
	{ //19
		txtName = "Barn North";
		txtDiscover = "TODO: Do you have the code?";
		txtReturn = "TODO";
		txtSurroundings = "TODO";
		MyString txtUnlockMessage;
		txtUnlockMessage = "You hear a rumbling through the North wall. Slowly, rocks begin to fall from the wall, revealing a hidden passageway. ";
		DoorCodeRoom *tempBarnNorth = new DoorCodeRoom(0, 3, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(0, 4), txtUnlockMessage);
		tempBarnNorth->canMoveNorth(false);
		tempBarnNorth->canMoveEast(false);
		tempBarnNorth->canMoveWest(false);
		tempBarnNorth->interior(false);
		m.push_back(tempBarnNorth);
	}
	{ //20
		txtName = "Cellar";
		txtDiscover = "TODO: Etched into wall: A random 6 digit code is generated here. This will be used to pass the final part of the barn and finish the game";
		txtReturn = "TODO";
		txtSurroundings = "TODO: Give code";
		MyString txtInfoToDisplay = (m.at(18)->code());
		DoorRoom *tempCellar = new InfoDoorRoom(1, 3, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(1, 2), txtInfoToDisplay);
		tempCellar->canMoveNorth(false);
		tempCellar->canMoveSouth(false);
		tempCellar->canMoveEast(false);
		tempCellar->canMoveWest(false);
		tempCellar->interior(true);
		m.push_back(tempCellar);
	}
	{ //21
		txtName = "Tunnel";
		txtDiscover = "TODO: You fall";
		txtReturn = "You shouldn't be able to get back here";
		txtSurroundings = "Nothing";
		TeleportRoom *tempTunnel = new TeleportRoom(0, 4, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(5, 8));
		tempTunnel->canMoveNorth(false);
		tempTunnel->canMoveEast(false);
		tempTunnel->canMoveWest(false);
		tempTunnel->locked(true);
		m.push_back(tempTunnel);
	}
	{ //22
		txtName = "Cave Entrance";
		txtDiscover = "TODO: no going back";
		txtReturn = "You shouldn't be able to get back here";
		txtSurroundings = "Nothing";
		Room *tempCaveEntrance = new Room(5, 8, txtName, txtDiscover, txtReturn, txtSurroundings);
		m.push_back(tempCaveEntrance);
	}
	{

	}
}
MyString getUserInput() {
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, 10);
	cout << "> ";
	char input[128];
	cin.getline(input,sizeof(input));
	SetConsoleTextAttribute(hColor, 7);
	MyString strInput = input;
	strInput = strInput.toLowercase();
	return strInput.stringOutput();
}

void checkLockedRooms(vector<Room*> &m, Player* p) {
	for (unsigned int i = 0; i < (p->inventorySize()); i++) {
		if ((p->searchInventory("key")) != -1) { //Unlocks Barn if player is holding key
			m.at((p->findRoomAt(0, 2, m, maxRooms)))->locked(false);
		}
		if ((p->searchInventory("raft")) != -1) { //Unlocks Lake if player is holding raft
			m.at((p->findRoomAt(0, -1, m, maxRooms)))->locked(false);
			m.at((p->findRoomAt(1, -1, m, maxRooms)))->locked(false);
		}
	}
}

void startGame() {
	//Initialize all (restart the game)
	srand(unsigned int(time(NULL)));
	vector<Room*> map;
	//-----
	//-----
	initializeMap(map);
	Player* player = new Player();
	//Print name of current room in a different text colour
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	player->visitRoom(0, 0, map); // Spawns the player in Room at 0, 0 (The spawn room)
	//---------------------------------------------------------------------------------
	
	while (gamePlaying == true) {
		checkLockedRooms(map, player);		//Unlock rooms if criteria met
		map.at(player->findCurrentRoom(map, maxRooms))->handleInput(getUserInput(), map, player);
	}

	// Game over

	//HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE); //Change text colour
	SetConsoleTextAttribute(hColor, 12);
	cout << "Would you like to play again?" << endl;
	SetConsoleTextAttribute(hColor, 7); //Resets text colour to white

	//TODO: CLEAR MEMORY (GET DESTRUCTORS WORKING)

	{
		MyString input = getUserInput();
		if (input == "yes") {
			gamePlaying = true;
			startGame();
		}
		else {
			cout << "Thanks for playing!" << endl;
			Sleep(2000);
		}
	}
}

int main()
{
	validateClass();
	startGame();
    return 0;
}
