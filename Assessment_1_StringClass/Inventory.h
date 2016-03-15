#pragma once
#include "MyString.h"

class Item {
private:
	MyString m_itemID = "";
	MyString m_itemName = "";
	MyString m_description = "";
public:
	Item() {

	}
	Item(MyString c) {
		m_itemID = c.toLowercase();
		if (m_itemID =="shovel") {
			m_itemName = "Garden Shovel";
			m_description = "A sturdy garden shovel";
		}
		else if (m_itemID =="raft") {
			m_itemName = "Old Raft";
			m_description = "An old wooden raft";
		}
		else if (m_itemID =="key") {
			m_itemName = "Key";
			m_description = "A small, old fashioned key";
		}
		else if (m_itemID =="") {
			
		}
	}

	MyString itemID() {
		return m_itemID;
	}
	MyString itemName() {
		return m_itemName;
	}
};