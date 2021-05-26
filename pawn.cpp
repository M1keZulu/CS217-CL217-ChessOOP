#include<iostream>
#include<vector>
#define GRID 8
#include "enums_data.h"
#include "cell.h"
#include "piece.h"
#include "pawn.h"

using namespace std;

Pawn::Pawn(Color m_color, Direction d):Piece(m_color, pawn){this->d=d;}
bool Pawn::enPassant(Piece *ptr){
	for(int x=0; x<pawnLocation.size(); x++){
		if(pawnLocation[x]==ptr){
			return false;
		}
	}
	return true;
}
void Pawn::AddenPassant(Piece *ptr){
	pawnLocation.push_back(ptr);
}
Direction Pawn::getPawnDirection(){return d;}
void Pawn::generateMoves(Point currentPos){
	movesAvailable.clear();
	if(d==up){
		if(inLimits({currentPos.x-1, currentPos.y})){									//(x-1)(y)
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()==NULL){
				movesAvailable.push_back({currentPos.x-1, currentPos.y});
			}
		}
		if(inLimits({currentPos.x-1, currentPos.y-1})){									//(x-1)(y-1)
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()!=NULL && (cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
				movesAvailable.push_back({currentPos.x-1, currentPos.y-1});
			}
		}
		if(inLimits({currentPos.x-1, currentPos.y+1})){									//(x-1)(y+1)
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()!=NULL && (cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
				movesAvailable.push_back({currentPos.x-1, currentPos.y+1});
			}
		}
		if(inLimits({currentPos.x-2, currentPos.y}) && moveCount==0){
			if((cell+((currentPos.x-2)*GRID)+(currentPos.y))->getPiece()==NULL){
				movesAvailable.push_back({currentPos.x-2, currentPos.y});
			}
		}
	}
	else if(d==down){
		if(inLimits({currentPos.x+1, currentPos.y})){									//(x+1)(y)
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()==NULL){
				movesAvailable.push_back({currentPos.x+1, currentPos.y});
			}
		}
		if(inLimits({currentPos.x+1, currentPos.y+1})){									//(x+1)(y+1)
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()!=NULL && (cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
				movesAvailable.push_back({currentPos.x+1, currentPos.y+1});
			}
		}
		if(inLimits({currentPos.x+1, currentPos.y-1})){									//(x+1)(y-1)
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()!=NULL && (cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
				movesAvailable.push_back({currentPos.x+1, currentPos.y-1});
			}
		}
		if(inLimits({currentPos.x+2, currentPos.y}) && moveCount==0){
			if((cell+((currentPos.x+2)*GRID)+(currentPos.y))->getPiece()==NULL){
				movesAvailable.push_back({currentPos.x+2, currentPos.y});
			}
		}
	}
}
