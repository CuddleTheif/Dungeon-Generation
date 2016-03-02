#pragma once
#include "Room.h"
#include "Path.h"
#include <vector>

class Dungeon
{
public:
	Dungeon(int width, int height);
	void printDungeon(bool* tiles);
	void generateDungeon(Room* possRooms, int numPossRooms);

private:
	std::vector<Path> paths;
	Room* rooms;
	unsigned int seed;
	int numRooms, numPaths, width, height;
	void printPath(Path path);
	void printRoom(Room room);
	void writeAt(System::String^ s, int x, int y);
	const int UNITS_PER_ROOM = 300;
};

