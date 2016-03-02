#include "Dungeon.h"
#include <stdlib.h>
#include <time.h>
using namespace System;

int main()
{
	while (true) {
		srand(time(NULL));
		Dungeon dungeon(50, 30);
		Room rooms[10];
		for (int i = 0; i < 10; i++)
			rooms[i] = *new Room(0, 0, rand() % 5 + 3, rand() % 5 + 3);
		dungeon.generateDungeon(rooms, 10);
		Console::SetCursorPosition(0, 0);
		String^ input = Console::ReadLine();
		Console::Clear();
		if (input != "")
			return 0;
	}
	return 0;
}