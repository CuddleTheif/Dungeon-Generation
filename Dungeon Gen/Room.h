#pragma once
#include "Path.h"

class Room
{
public:
	Room(int x=0, int y=0, int width=0, int height=0);
	bool isIntersectingRoom(Room room);
	bool isInRoom(int x, int y);
	Path createPathTo(Room room);
	int X, Y, Width, Height, NumPaths;
};

