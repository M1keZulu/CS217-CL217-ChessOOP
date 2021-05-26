#include<iostream>
#include<vector>
#define GRID 8
#include "enums_data.h"
#include "cell.h"
#include "piece.h"
#include "king.h"

using namespace std;

King::King(Color m_color):Piece(m_color, king){}

void King::generateMoves(Point currentPos){
	movesAvailable.clear();
	if(inLimits({currentPos.x-1, currentPos.y})){
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x-1, currentPos.y});
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-1, currentPos.y});
		}
	}
	if(inLimits({currentPos.x+1, currentPos.y})){
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x+1, currentPos.y});
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x+1, currentPos.y});
		}
	}
	if(inLimits({currentPos.x, currentPos.y+1})){
		if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x, currentPos.y+1});
		}
		else if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x, currentPos.y+1});
		}
	}
	if(inLimits({currentPos.x, currentPos.y-1})){
		if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x, currentPos.y-1});
		}
		else if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x, currentPos.y-1});
		}
	}
	if(inLimits({currentPos.x-1, currentPos.y+1})){
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x-1, currentPos.y+1});
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-1, currentPos.y+1});
		}
	}
	if(inLimits({currentPos.x-1, currentPos.y-1})){
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x-1, currentPos.y-1});
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-1, currentPos.y-1});
		}
	}
	if(inLimits({currentPos.x+1, currentPos.y+1})){
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x+1, currentPos.y+1});
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x+1, currentPos.y+1});
		}
	}
	if(inLimits({currentPos.x+1, currentPos.y-1})){
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			movesAvailable.push_back({currentPos.x+1, currentPos.y-1});
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x+1, currentPos.y-1});
		}
	}
}
