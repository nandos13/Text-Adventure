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
		txtReturn = "You stand outside the barn door.";
		txtSurroundings = "The old tree sits proudly to your South. There's a sign post to your East.";
		DoorRoom *tempBarnRoom = new DoorRoom(0, 1, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(0, 2));
		tempBarnRoom->canMoveNorth(false);
		tempBarnRoom->canMoveWest(false);
		tempBarnRoom->interior(false);
		m.push_back(tempBarnRoom);
	}
	{ //9
		txtName = "Barn South";
		txtDiscover = "The heavy barn door creaks as you push it open and step inside. The floor is littered with hay, but the rest of the barn is mostly barren. You can see something on the Northern wall of the barn. At the moment, it's too far away to read.";
		txtReturn = "You stand inside the barn, by the door.";
		txtSurroundings = "There isn't much to do at this end of the barn. The Northern end has something written on the wall. You can also leave the barn if you wish.";
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
		txtDiscover = "A lonely signpost stands on a small patch of grass. One sign points North, down a gravel path to a wine cellar. Another points to the well to your East, and another points you in the direction of the garden to your South.";
		txtReturn = "You stand beneath the signpost. Take a look to see what is around you.";
		txtSurroundings = "Theres a cellar to your North, a barn to your West, an old water well to your East, and a garden to your South.";
		m.push_back(new Room(1, 1, txtName, txtDiscover, txtReturn, txtSurroundings));
	}
	{ //11
		txtName = "Water Well";
		txtDiscover = "A broken old water well stands in this field. As you approach, you see a plastic bottle of water sitting in the well's bucket. \nThe shed is to your South, the Signpost to your West, and there lies a very ominous looking hill to your North. A long and bare paddock stretches to your East. It's not worth going that way.";
		txtReturn = "You make your way back to the water well.";
		txtSurroundings = "There is a signpost to your West and an old shed to your South. The paddock to your East seems endless and isn't worth exploring. To your North is a spooky hill.";
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
		txtSurroundings = "The water well sits to your South, and the cellar is to your West. The hill to your North might also be worth exploring.";
		Zombie *ptrEnemy = new Zombie();
		CombatRoom *tempCombatRoom = new CombatRoom(2, 2, txtName, txtDiscover, txtReturn, txtSurroundings, ptrEnemy);
		tempCombatRoom->canMoveEast(false);
		m.push_back(tempCombatRoom);
	}
	{ //13
		txtName = "Behind Corpse Hill";
		txtDiscover = "Amongst more rotting corpses you find a double-barrel shotgun.";
		txtReturn = "You return to the pile of corpses.";
		txtSurroundings = "You are surrounded by dense forest. You can only go South from here.";
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
		txtDiscover = "You make your way to a clearing in the forest. You tread carefully, as thick silky webs cover the trees and a majority of the floor you are walking on. A faint cracking of twigs behind you catches your attention and you turn to face the source of the sound. A horrifyingly large, hairy spider stares back at you, it's eyes black as night. It pauses for a moment, as if shocked you were able to hear it's approach, then suddenly lurches toward you with an awful shrill hiss. You ready yourself to fight.";
		txtReturn = "You return to the forest where a giant spider had taken you by surprise.";
		txtSurroundings = "Through the dense overgrowth around you, you can make out the farmiliar old tree to your East. A massive boulder to your West looks very out of place, you think. The webs around the trees to your South seem to get even thicker; even more uninviting.";
		Spider *ptrEnemy = new Spider();
		CombatRoom *tempCombatRoom = new CombatRoom(-1, 0, txtName, txtDiscover, txtReturn, txtSurroundings, ptrEnemy);
		tempCombatRoom->canMoveNorth(false);
		m.push_back(tempCombatRoom);
	}
	{ //15
		txtName = "Webbed Thicket";
		txtDiscover = "You trudge through the thick webs littering the ground. You struggle to move as swiftly as before, as you focus on keeping your feet from becoming stuck. Making your way towards the mouth of a dark cave infront of you, an unnerving feeling of paranoia takes over you. You look up just in time to see another disgusting spider, much larger than the last, lowering itself from the treetops. You ready yourself for combat as the creature starts toward you.";
		txtReturn = "You make your way back to the web covered thicket.";
		txtSurroundings = "There's a cave to your South, and the clearing in the forest lies to your North.";
		MotherSpider *ptrEnemy = new MotherSpider();
		CombatRoom *tempCombatRoom = new CombatRoom(-1, -1, txtName, txtDiscover, txtReturn, txtSurroundings, ptrEnemy);
		tempCombatRoom->canMoveEast(false);
		tempCombatRoom->canMoveWest(false);
		m.push_back(tempCombatRoom);
	}
	{ //16
		txtName = "Spider Lair";
		txtDiscover = "You hesitantly step into the cave. There isn't much to be found aside from a few disgusting spider egg sacs. Webbed to the wall, you spot something small and metal, but can't quite make out what it is.";
		txtReturn = "You return to the creepy spider lair. You don't want to stay here for long.";
		txtSurroundings = "You should leave the cave once you are done here.";
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
		txtReturn = "You return to the large square boulder.";
		txtSurroundings = "The forest clearing is to your East. There isn't anywhere else to go.";
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
		txtDiscover = "You walk up to the cellar door. A gravel path leads back to a signpost to your South, and there is a hill to your East. Shivers run down your spine as you look at the hill.";
		txtReturn = "You return to the cellar's entrance.";
		txtSurroundings = "There is a signpost to your South, and a creepy hill to your East. You can also head inside the cellar.";
		DoorRoom *tempCryptExterior = new DoorRoom(1, 2, txtName, txtDiscover, txtReturn, txtSurroundings, MapLocation(1, 3));
		tempCryptExterior->canMoveNorth(false);
		tempCryptExterior->canMoveWest(false);
		tempCryptExterior->interior(false);
		m.push_back(tempCryptExterior);
	}
	{ //19
		txtName = "Barn North";
		txtDiscover = "The humming noise seems even louder at this end of the barn. Engraved into the barn wall there is a message. Strange symbols unlike any language you've seen before. As you concentrate on these symbols, in a way you can't possibly describe, you understand what they mean. In your head, you hear the words \n'You've done well so far \nNow speak the code \nAnd if you're worthy \nYou'll find the road'.";
		txtReturn = "You return to the strange symbols on the barn wall. You're going to need to say the code if you wish to go any further.";
		txtSurroundings = "The barn's exit is to your South.";
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
		txtDiscover = "In the center of the room, a strange, glowing stone pillar is sticking out of the floor. There is a code engraved in the top of the pillar.";
		txtReturn = "You return to the cellar and stand by the pillar, in which a code is engraved.";
		txtSurroundings = "You should leave the cellar once you're done here.";
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
		txtDiscover = "Stepping through the collapsed wall, you mistakenly put your weight on a loose rock. The floor beneath you gives way and you tumble down into a tight cavern.";
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
		txtName = "Sinkhole";
		txtDiscover = "Looking up, you must have fallen a good 15 meters. You rest for a moment, then struggle painfully to sit up. Your sense of direction feels muddled after the fall, but there is a tight entrace in the rock to your East, which you might be able to crawl through. The humming sound echoes through a wider tunnel to your South.";
		txtReturn = "You return to the sinkhole. There's no getting out, it's too deep.";
		txtSurroundings = "A tiny crawlspace to your East, and a wider tunnel to your South. The humming seems to be originating from down the larger tunnel.";
		Room *tempCaveEntrance = new Room(5, 8, txtName, txtDiscover, txtReturn, txtSurroundings);
		tempCaveEntrance->canMoveNorth(false);
		tempCaveEntrance->canMoveWest(false);
		m.push_back(tempCaveEntrance);
	}
	{ //23
		txtName = "Crawlspace";
		txtDiscover = "As you crawl through to the opening, you lose your footing and kick a loose rock as you slip. The wall infront of you gives way and a large boulder begins to crash down towards you.";
		txtReturn = "You crawl back to the claustrophobic clearing. After the boulder fell, there's even less room to move around.";
		txtSurroundings = "Through a man-sized crack in the stone to your South, you can see a strange, unnatural shimmering light shining through. Through the crawlspace and to your West is the sinkhole you previously fell through.";
		MyString txtCorrectSolution = "dodge";
		MyString txtAction = "killplayer";
		MyString txtActionMessage = "The boulder hits you, crushing you against the wall. The dim cave fades to complete darkness as you lose all feeling below your neck. You take one last sharp, painful breath in as you lose all consciousness.";
		MyString txtSolutionMessage = "You manage to hug up against the wall just in time, barely avoiding certain death. The boulder collides with the wall with a deafening crash. The opening now feels even more cramped than before.";
		TrapRoom *tempTrapRoom = new TrapRoom(6, 8, txtName, txtDiscover, txtReturn, txtSurroundings, txtCorrectSolution, txtAction, txtActionMessage, txtSolutionMessage);
		tempTrapRoom->canMoveEast(false);
		tempTrapRoom->canMoveNorth(false);
		m.push_back(tempTrapRoom);
	}
	{ //24
		txtName = "Iridescent Cavern"; // loot room, relic to win boss fight
		txtDiscover = "You manage to crawl through the claustrophobic tunnel and flop out into a small space. Embedded into the far wall is a series of glowing pillars which seem to change colour as you move around them. It's unlike anything you've ever seen! \nBetween these pillars lay a strange artifact, not of this world. The artifact, clearly meant to be a sword or something similar, has glowing symbols etched into the side. Once again, in your head you understand the symbols, and know it reads 'Slayer of Mothers'.";
		txtReturn = "You return to the glowing cave where you found the strange sword.";
		txtSurroundings = "You should crawl through the space to the North once you're done here.";
		itemLoot = "sword";
		Weapon *item = new Weapon(itemLoot);
		LootRoom *tempLootRoom = new LootRoom(6, 7, txtName, txtDiscover, txtReturn, txtSurroundings, item);
		tempLootRoom->canMoveEast(false);
		tempLootRoom->canMoveWest(false);
		tempLootRoom->canMoveSouth(false);
		m.push_back(tempLootRoom);
	}
	{ //25
		txtName = "Alien Tunnel"; 
		txtDiscover = "Following the strange humming sound, you follow the tunnel South. As you walk further, you begin to hear a horrible sloshing sound over the humming. The tunnel reaches a ledge and drops infront of you, and as you peek your head to look over the edge, you see a figure hunched over the remains of an old farmer. The figure, no larger than a small child, looks up at you, blood dripping from its mouth. \nThe alien's skin is pale and its eyes take up most of its head. Without breaking eye contact, it reaches to its side and picks up a pulsing purple rifle. With a deafening screech, the alien jumps to its feet.";
		txtReturn = "You return to the narrow tunnel. The corpse of a farmer, the alien's previous snack, still lays at the base of the ledge.";
		txtSurroundings = "At the Northern end of the tunnel is the sinkhole you fell into. Further South, the tunnel seems to open up to the wreckage of an alien ship.";
		Alien *ptrEnemy = new Alien();
		CombatRoom *tempCombatRoom = new CombatRoom(5, 7, txtName, txtDiscover, txtReturn, txtSurroundings, ptrEnemy);
		tempCombatRoom->canMoveEast(false);
		tempCombatRoom->canMoveWest(false);
		m.push_back(tempCombatRoom);
	}
	{ //26
		txtName = "Mothership Wreck";
		txtDiscover = "You approach a huge opening in the cave. The wreckage of what appears to have been an alien ship is scattered throughout the area. A number of egg sacs are growing around the site. As you walk closer, a deafening roar shakes the ground around you as a huge figure emerges from the wreckage. Much like the previous alien, only thrice the size and seemingly plated in some kind of natural armour, this monster charges towards you on all fours, shaking the whole cave with each step.";
		txtReturn = "You return to the crash site, where the mother alien had been laying in wait.";
		txtSurroundings = "The tunnel to the North leads back to the sinkhole. The humming sound seems to be coming from inside the wreckage, to the West.";
		AlienBroodmother *ptrEnemy = new AlienBroodmother();
		CombatRoom *tempCombatRoom = new CombatRoom(5, 6, txtName, txtDiscover, txtReturn, txtSurroundings, ptrEnemy);
		tempCombatRoom->canMoveEast(false);
		tempCombatRoom->canMoveSouth(false);
		m.push_back(tempCombatRoom);
	}
	{ //27
		txtName = "Engine Room";
		txtDiscover = "You reach the engine room of the alien ship. The humming sound is almost deafening now. You can feel the engine draining your energy and you know you will need to act quickly. The engine seems to be controlled by a complex alien dashboard of buttons and switches to your right. You don't undertstand anything written on the board, but you notice an obvious red button in the center of the console. Next to the button, a red switch is flicked to the top. On the verge of losing consciousness, you need to make a decision fast. Should you use the button or the switch?";
		txtReturn = "TODO";
		txtSurroundings = "";
		MyString txtCorrectSolution = "switch";
		MyString txtIncorrectSolution = "button";
		MyString txtWinAction = "wingame";
		MyString txtAction = "killplayer";
		MyString txtActionMessage = "You slam the button down with all the strength left in you. A loud buzzing alarm starts to go off above the engine, and steam begins to be exhausted as hoses to the engine detatch and fall to the floor. The floor shakes violently and you feel the room's temperature drasically rise. The last thing you see is the top of the engine go flying before a devastating explosion rips through your body.";
		MyString txtSolutionMessage = "You quickly flick the switch to the downwards position. Green lights around the engine turn on, and the humming sound starts to fade. You can already feel yourself regaining some of your strength. As the engine shuts down, you leave the wreckage of the ship and head back to the sinkhole. \nYou manage to work your way up the rubble and return to the old tree. You feel like you are ready for your next adventure, but for now, you decide to lay down in the soft grass and take a well deserved nap...";
		EndGameRoom *tempRoom = new EndGameRoom(4, 6, txtName, txtDiscover, txtReturn, txtSurroundings, txtCorrectSolution, txtAction, txtActionMessage, txtSolutionMessage, txtIncorrectSolution, txtWinAction);
		tempRoom->canMoveNorth(false);
		tempRoom->canMoveWest(false);
		tempRoom->canMoveSouth(false);
		m.push_back(tempRoom);
	}
}
MyString getUserInput() {
	HANDLE hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, 10);
	cout << "\n> ";
	char input[128];
	cin.getline(input,sizeof(input));
	SetConsoleTextAttribute(hColor, 7);
	MyString strInput = input;
	strInput = strInput.toLowercase();
	cout << "\n";
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
