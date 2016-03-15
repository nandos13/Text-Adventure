// Assessment_1_StringClass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyString.h"
#include "Room.h"
#include "Player.h"
#include "MapLocation.h"
#include "Inventory.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
using namespace std;


//GLOBAL VARIABLES
fstream file;
const unsigned int numberOfMapRooms = 3; // USED FOR ITERATING THROUGH ALL ROOMS ON THE MAP
bool gamePlaying;


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
		output << description << "\nFAILED!" << endl;
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
		classTest((s1.getLength()==14), "Member function getLength returns number of characters in string", countPass, countFail, file);
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
		classTest((c1 = "This is a test"), "Return as basic constant C-style string", countPass, countFail, file);
		classTest((s1.toLowercase() == "this is a test"), "Converting string to lowercase", countPass, countFail, file);
		classTest((s1.toUppercase() == "THIS IS A TEST"), "Converting string to uppercase", countPass, countFail, file);
		classTest((s1.find("est") == 11), "Find the position of a substring within a string", countPass, countFail, file);
		classTest((s1.find("is", 3) == 5), "Find the position of a substring, after a given position in the string", countPass, countFail, file);
		s4 = s1;
		s4 = s4.subReplace(7, 1, " not ");
		classTest((s4 == "This is not a test"), "Replace a substring at a given position with another string", countPass, countFail, file);
		
		file << endl;
		file << countPass << " of " << countPass + countFail << " tests passed. Pass rate: " << percentage(countPass, countPass + countFail) << "%" << endl;
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
	txtName = "OLD TREE";
	txtDiscover = "You awake under the shade of a large tree, head pounding and body weak. The air is still, almost silent. Concentrating, you notice a faint humming sound resonating from a nearby barn that sits just a few short paces North down an old stony path. To the East lay a small and peaceful looking garden abundant with vibrant flowers. To your West is a dense, dark forest which wraps around to meet a lake to your South. \nGripping a low branch to support yourself with your left hand, you painfully summon the strength to stand. ";
	txtReturn = "You return to the large tree. It casts shade over a lush patch of grass, and you feel at rest as you approach. It's not hard to see how you fell asleep in this comfortable spot.";
	txtSurroundings = "An old barn lies to your North. To the East is a vibrant garden, and to the West, a dense forest.";
	m.push_back(new Room(0, 0, txtName, txtDiscover, txtReturn, txtSurroundings));
	txtName = "GARDEN";
	txtDiscover = "A pleasant aroma overwhelms your senses as you approach the small garden. Between rows of assorted flowers lay a narrow gravel path lined with old bricks. Towards the East end of the garden, a heavy, rusted looking shovel is sticking out of the dirt. Beyond the shovel lies a shed, which you think might be worth exploring. The lake to your south still seems difficult to cross. Several meters to your North stands a sign post.";
	txtReturn = "You make your way back to the quaint garden.";
	txtSurroundings = "You can see a sign post to your North, an old shed to your East, and to your West lies the field where you woke up.";
	itemLoot = "shovel";
	m.push_back(new LootRoom(1, 0, txtName, txtDiscover, txtReturn, txtSurroundings, Item(itemLoot)));
	txtName = "SHED";
	txtDiscover = "The shed is decrepit and covered in spider webs. Left ajar, the tin door creaks in the wind. The interior is dark and you struggle to see what is inside. As you decide whether or not to enter, you survey your surroundings; Your South side is covered by a rocky hill which seems impossible to cross, and to your North you can see a small water well. The garden lies to your West.";
	txtReturn = "You return to the old shed.";
	txtSurroundings = "A small water well lies to your North. The garden sits to your West. Your South is covered by a steep rocky hill which looks too hard to climb. To your East is a large, bare paddock which stretches for a few kilometers at least. You don’t have the energy to walk that far.";
	m.push_back(new Room(2, 0, txtName, txtDiscover, txtReturn, txtSurroundings));

}
MyString getUserInput() {
	cout << "> ";
	char input[128];
	cin.getline(input,sizeof(input));
	MyString strInput = input;
	strInput = strInput.toLowercase();
	return strInput.stringOutput();
}


void startGame() {
	//Initialize all (restart the game)
	vector<Room*> map;
	//-----
	//-----
	initializeMap(map);
	Player* player = new Player();
	gamePlaying = true;
	//player->visitRoom(0, 0, map); // Spawns the player in Room at 0, 0 (The spawn room)
	//---------------------------------------------------------------------------------
	

	while (gamePlaying == true) {
		//TODO: **************************************************************************************************
		map[player->findRoomAt(player->getPlayerLocX(), player->getPlayerLocY(), map, numberOfMapRooms)]->handleInput(getUserInput(), map, player);
		//FINISH FUNCTION
		//interprit first word, up to space (eg move)
		// pass rest into appropriate function (eg Move West will take move and pass West into move specific function)
	}
}

int main()
{
	validateClass();
	startGame();

	cin.get();
    return 0;
}
//FUNCTION HANDLE INPUT (USING SPACES)
/*void handleInput(MyString str, vector<Room*> m, Player* p) {
MyString temp = str;
int spaceLocation = 0;
spaceLocation = temp.find(" ");
if (spaceLocation == -1) {
//No space found, treat as single word input
if (str == "north") {
(*p_movePlayer)("north", m, p);
}
else if (str == "east") {
(*p_movePlayer)("east", m, p);
}
else if (str == "south") {
(*p_movePlayer)("south", m, p);
}
else if (str == "west") {
(*p_movePlayer)("west", m, p);
}
else if (str == "look" || str == "surroundings" || str == "explore") {
cout << (m.at((*p_findRoomAt)(p->getPlayerLocX(), p->getPlayerLocY(), m))->surroundingsText()).stringOutput() << endl;
}
else if (str == "loot" || str == "pickup" || str == "pick up" || str == "equip") {
//Check if room is loot room subclass
if (m.at((*p_findRoomAt)(p->getPlayerLocX(), p->getPlayerLocY(), m))->roomType() == "loot") {
cout << "looting" << endl;
lootRoomAt((*p_findRoomAt)(p->getPlayerLocX(), p->getPlayerLocY(), m), m, p);
//TODO: Finish loot function
//IF: check loot has not already been picked up
//ADD PLAYER CLASS INVENTORY USING <VECTOR>
}
else {
cout << "Nothing to loot" << endl;
}
}
}
else {
//Find the first command word, eg "move"
//TODO: Finish this
if (str.subString(0, spaceLocation)=="move") {
str = str.subString(spaceLocation+1);
if (str == "north") {
(*p_movePlayer)("north", m, p);
}
else if (str == "east") {
(*p_movePlayer)("east", m, p);
}
else if (str == "south") {
(*p_movePlayer)("south", m, p);
}
else if (str == "west") {
(*p_movePlayer)("west", m, p);
}
else {
cout << "Try that again!" << endl;
}
}
else {
cout << "Try that again!" << endl;
}
}
}*/