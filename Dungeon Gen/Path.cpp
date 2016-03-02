#include "Path.h"
#include <stdlib.h>

// Creates a path with the given start and end
Path::Path(int startX, int startY, int endX, int endY)
{
	Path::startX = startX;
	Path::startY = startY;
	Path::endX = endX;
	Path::endY = endY;
	if(startX!=endX || startY!=endY)
		generatePath();
}

// Generates the path
void Path::generatePath() {

	// Create the vaeriables for number of segments in each direction and the direction of the path
		int xSeg = startX==endX ? 0 : rand() % (abs(startX - endX) / UNITS_PER_SEG) + 1,
			ySeg = startY==endY ? 0 : rand() % (abs(startY - endY) / UNITS_PER_SEG) + 1,
			curX = startX,
			curY = startY,
			dirX = startX<endX ? 1 : -1,
			dirY = startY<endY ? 1 : -1;
		numSeg = xSeg + ySeg;
		segments = new Segment[numSeg];

	// Create the segments with a random order
		for (int i = 0; i < numSeg; i++) {
			segments[i].startX = curX;
			segments[i].startY = curY;
			if ((rand() % 2 == 0 && xSeg>0) || ySeg<=0) {
				if (xSeg-- == 1)
					segments[i].distance = abs(curX - endX)*dirX;
				else
					segments[i].distance = (rand() % (abs(curX - endX) - xSeg + 1) + 1)*dirX;
				segments[i].direction = false;
				curX += segments[i].distance;
			}
			else {
				if (ySeg-- == 1)
					segments[i].distance = abs(curY - endY)*dirY;
				else
					segments[i].distance = (rand() % (abs(curY - endY) - ySeg + 1) + 1)*dirY;
				segments[i].direction = true;
				curY += segments[i].distance;
			}
		}	
}

// Returns the segments of the path
Segment* Path::getSegs() {
	return segments;
}

// Returns the number segments of the path
int Path::getNumSeg() {
	return numSeg;
}