#include "Room.h"
#include <stdlib.h> 

Room::Room(int x, int y, int width, int height) {
	X = x;
	Y = y;
	Width = width;
	Height = height;
	NumPaths = 0;
}

// Checks if this room is intersecting the given room
bool Room::isIntersectingRoom(Room room) {
	return X <= room.X+room.Width && X+Width >= room.X && Y <= room.Y+room.Height && Y+Height >= room.Y;
}

// Checks if the given coords are in this room (including walls)
bool Room::isInRoom(int x, int y) {
	return x >= X && x <= X + Width && y >= Y && y <= Y + Height;
}

// Creates and returns a path from this room to the given room
Path Room::createPathTo(Room room) {

	int dir1 = rand() % 2, dir2 = rand() % 2;
	int startX, startY, endX, endY;
	if (rand() % 2 ==0) {
		startX = X + (rand() % 2)*Width;
		startY = Y + rand() % (Height-2) + 1;
	}
	else {
		startX = X + rand() % (Width-2) + 1;
		startY = Y + (rand() % 2)*Height;
	}
	if (rand() % 2 == 0) {
		endX = room.X + (rand() % 2)*room.Width;
		endY = room.Y + rand() % (room.Height-2) + 1;
	}
	else {
		endX = room.X + rand() % (room.Width-2) + 1;
		endY = room.Y + (rand() % 2)*room.Height;
	}
	NumPaths++;
	room.NumPaths++;
	return *new Path(startX, startY, endX, endY);
}