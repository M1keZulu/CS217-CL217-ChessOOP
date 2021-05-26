#include<iostream>
#include<vector>
#define GRID 8
#include "enums_data.h"
#include "cell.h"
#include "piece.h"
#include "rook.h"

using namespace std;

Rook::Rook(Color m_color):Piece(m_color, rook){}
void Rook::generateMoves(Point currentPos){
	movesAvailable.clear();
	int cx=currentPos.x;
	int cy=currentPos.y;
	while(inLimits({currentPos.x-1,currentPos.y})){
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x-1, currentPos.y});
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-1, currentPos.y});
			break;
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x--;
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x+1,currentPos.y})){
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x+1, currentPos.y});
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x+1, currentPos.y});
			break;
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x++;
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x,currentPos.y-1})){
		if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x, currentPos.y-1});
		}
		else if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x, currentPos.y-1});
			break;
		}
		else if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.y--;
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x,currentPos.y+1})){
		if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x, currentPos.y+1});
		}
		else if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x, currentPos.y+1});
			break;
		}
		else if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.y++;
	}
}
