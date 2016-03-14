#pragma once

class MapLocation {
public:
	int m_x;
	int m_y;
	MapLocation() {

	}
	MapLocation(int posX, int posY) {
		m_x = posX;
		m_y = posY;
	}
};