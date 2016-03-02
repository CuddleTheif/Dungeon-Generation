#pragma once

struct Segment
{
	int startX, startY, distance;
	bool direction;
};

class Path
{
public:
	Path(int startX=0, int startY=0, int endX=0, int endY=0);
	Segment* getSegs();
	int getNumSeg();

private:
	int startX, startY, endX, endY;
	void generatePath();
	Segment* segments;
	const int UNITS_PER_SEG = 1;
	int numSeg;
};

