#ifndef ENUMS_DATA_H
#define ENUMS_DATA_H

using namespace std;

enum PieceType{
	king, queen, bishop, knight, rook, pawn	
};

enum Color{
	black, white
};

enum Status{
	alive, dead
};

enum ConnectionType{
	host, client
};

enum Direction{
	up, down
};

struct Point{
	int x;
	int y;	
};

struct Detail{
	int x;
	int y;
	Color color;
	PieceType name;
};

struct Moves{
	Point p;
	string cell;
};

#endif
