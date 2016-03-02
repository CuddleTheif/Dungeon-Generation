#include "Dungeon.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

Dungeon::Dungeon(int width, int height)
{
	seed = time(NULL);
	srand(seed);
	Dungeon::width = width;
	Dungeon::height = height;
}

// Generates the dungeon
void Dungeon::generateDungeon(Room* possRooms, int numPossRooms) {

	bool* tiles = new bool[width*height];
	for (int i = 0; i < width*height; i++)
		tiles[i] = false;

	numRooms = width*height / UNITS_PER_ROOM;
	rooms = new Room[numRooms];
	for (int i = 0; i < numRooms; i++) {
		rooms[i] = *new Room(possRooms[rand() % numPossRooms]);
		bool intersects = true;
		while (intersects) {
			intersects = false;
			rooms[i].X = rand() % width;
			rooms[i].Y = rand() % height;
			for (int j = 0; j < numRooms; j++)
				if (j!=i && rooms[j].isIntersectingRoom(rooms[i]))
					intersects = true;
		}
		for (int x = rooms[i].X; x <= rooms[i].X+rooms[i].Width; x++)
			for (int y = rooms[i].Y; y <= rooms[i].Y+rooms[i].Height; y++)
				tiles[x*height + y] = true;
	}
	paths.clear();
	numPaths = 0;
	bool emptyRoom = true;
	while (emptyRoom) {
		int room1 = rand() % numRooms, room2 = room1;
		while (rooms[room1].NumPaths >= 2)room1 = rand() % numRooms;
		while (room1 == room2 || rooms[room2].NumPaths >= 3)room2 = rand() % numRooms;
		Path newPath = rooms[room1].createPathTo(rooms[room2]);
		paths.push_back(newPath);
		numPaths++;

		for (int i = 0; i < newPath.getNumSeg(); i++) {
			for (int j = 0; abs(j) < abs(newPath.getSegs()[i].distance); newPath.getSegs()[i].distance > 0 ? j++ : j--) {
				int x, y;
				if (newPath.getSegs()[i].direction) {
					x = newPath.getSegs()[i].startX;
					y = newPath.getSegs()[i].startY + j;
				}
				else {
					x = newPath.getSegs()[i].startX + j;
					y = newPath.getSegs()[i].startY;
				}
				tiles[x*height + y] = true;
			}
		}

		emptyRoom = false;
		for (int i = 0; i < numRooms && !emptyRoom; i++)
			if (rooms[i].NumPaths == 0)
				emptyRoom = true;
	}

	printDungeon(tiles);
}

using namespace System;

// Prints the dungeon to the console
void Dungeon::printDungeon(bool* tiles) {
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			if (tiles[x*height + y])
				writeAt("O", x, y);
	for (int i = 0; i < numRooms; i++)
		printRoom(rooms[i]);
	for (int i = 0; i < numPaths; i++)
		printPath(paths[i]);
	for (int i = 0; i < width*height; i++)
		writeAt(tiles[i].ToString()+i*5/Console::BufferWidth, i * 5 % Console::BufferWidth, height + 3);
}

void Dungeon::printPath(Path path) {
	for (int i = 0; i < path.getNumSeg(); i++) {
		for (int j = 0; abs(j) < abs(path.getSegs()[i].distance); path.getSegs()[i].distance>0 ? j++ : j--) {
			int x, y;
			if (path.getSegs()[i].direction) {
				x = path.getSegs()[i].startX;
				y = path.getSegs()[i].startY + j;
			}
			else {
				x = path.getSegs()[i].startX + j;
				y = path.getSegs()[i].startY;
			}
			bool inRoom = false;
			for (int i = 0; i < numRooms; i++)
				if (rooms[i].isInRoom(x, y))
					inRoom = true;
			if (!inRoom)
				writeAt("#", x, y);
		}
	}
}

void Dungeon::printRoom(Room room) {
	for (int x = room.X; x <= room.Width + room.X; x++){
		writeAt("X", x, room.Y);
		writeAt("X", x, room.Y + room.Height);
	}
	for (int y = room.Y; y <= room.Height + room.Y; y++) {
		writeAt("X", room.X, y);
		writeAt("X", room.X + room.Width, y);
	}
}


void Dungeon::writeAt(String ^s, int x, int y) {
	Console::SetCursorPosition(x, y);
	Console::Write(s);
}