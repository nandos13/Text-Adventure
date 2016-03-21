#pragma once
#include "MyString.h"

class Item {
protected:
	MyString m_itemID = "";
	MyString m_itemName = "";
	MyString m_description = "";
	MyString m_itemType = "item";
public:
	virtual ~Item() {

	}
	Item() {

	}
	Item(MyString c) {
		m_itemID = c.toLowercase();
		if (m_itemID == "empty") {
			m_itemName = "";
			m_description = "";
		}
		else if (m_itemID =="raft") {
			m_itemName = "Old Raft";
			m_description = "An old wooden raft";
		}
		else if (m_itemID =="key") {
			m_itemName = "Key";
			m_description = "A small, old fashioned key";
		}
		else if (m_itemID =="water") {
			m_itemName = "Water Bottle";
			m_description = "A half empty bottle of water";
		}
	}

	MyString itemID() {
		return m_itemID;
	}
	MyString itemName() {
		return m_itemName;
	}
	MyString itemType() {
		return m_itemType;
	}
	virtual float damage() {
		return 0.0f;
	}
};
class Weapon : public Item {
protected:
	int m_ammo;
	float m_damage;
public:
	virtual ~Weapon() {

	}
	Weapon() {
		m_itemType = "weapon";
	}
	Weapon(MyString c) {
		m_itemType = "weapon";
		m_itemID = c.toLowercase();
		if (m_itemID == "empty") {
			m_itemName = "";
			m_description = "";
			m_ammo = 0;
			m_damage = 0;
		}
		else if (m_itemID == "fists") {
			m_itemName = "Your hands";
			m_description = "You were born with these";
			m_ammo = -1;
			m_damage = 3;
		}
		else if (m_itemID == "shovel") {
			m_itemName = "Garden Shovel";
			m_description = "A sturdy garden shovel";
			m_ammo = -1;
			m_damage = 15;
		}
		else if (m_itemID == "shotgun") {
			m_itemName = "Shotgun";
			m_description = "A double-barrel shotgun";
			m_ammo = 2;
			m_damage = 45;
		}
	}
	virtual float damage() {
		return m_damage;
	}
};