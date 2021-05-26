#include<iostream>
#include<vector>
#define GRID 8
#include "enums_data.h"
#include "cell.h"
#include "piece.h"
#include "bishop.h"

using namespace std;

Bishop::Bishop(Color m_color):Piece(m_color, bishop){}
void Bishop::generateMoves(Point currentPos){
	movesAvailable.clear();
	int cx=currentPos.x;
	int cy=currentPos.y;
	while(inLimits({currentPos.x-1,currentPos.y-1})){
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x-1, currentPos.y-1});
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-1, currentPos.y-1});
			break;
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x--;
		currentPos.y--;
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x+1,currentPos.y+1})){
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x+1, currentPos.y+1});
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x+1, currentPos.y+1});
			break;
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x++;
		currentPos.y++;
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x+1,currentPos.y-1})){
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x+1, currentPos.y-1});
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x+1, currentPos.y-1});
			break;
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x++;
		currentPos.y--;
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x-1,currentPos.y+1})){
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x-1, currentPos.y+1});
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-1, currentPos.y+1});
			break;
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x--;
		currentPos.y++;
	}
}

