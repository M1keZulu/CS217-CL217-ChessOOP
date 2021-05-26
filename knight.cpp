#include<iostream>
#include<vector>
#define GRID 8
#include "enums_data.h"
#include "cell.h"
#include "piece.h"
#include "knight.h"

using namespace std;

Knight::Knight(Color m_color):Piece(m_color, knight){}
void Knight::generateMoves(Point currentPos){
	movesAvailable.clear();
	if(inLimits({currentPos.x-2, currentPos.y-1})){		//(x-2,y-1)
		if((cell+((currentPos.x-2)*GRID)+(currentPos.y-1))->getPiece()==NULL || (cell+((currentPos.x-2)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-2, currentPos.y-1});
		}
	}
	if(inLimits({currentPos.x+2, currentPos.y-1})){		//(x+2,y-1)
		if((cell+((currentPos.x+2)*GRID)+(currentPos.y-1))->getPiece()==NULL || (cell+((currentPos.x+2)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x+2, currentPos.y-1});
		}
	}
	if(inLimits({currentPos.x+2, currentPos.y+1})){		//(x+2,y+1)
		if((cell+((currentPos.x+2)*GRID)+(currentPos.y+1))->getPiece()==NULL || (cell+((currentPos.x+2)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x+2, currentPos.y+1});
		}
	}
	if(inLimits({currentPos.x-2, currentPos.y+1})){		//(x-2,y+1)
		if((cell+((currentPos.x-2)*GRID)+(currentPos.y+1))->getPiece()==NULL || (cell+((currentPos.x-2)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-2, currentPos.y+1});
		}
	}
	if(inLimits({currentPos.x+1, currentPos.y+2})){		//(x+1,y+2)
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y+2))->getPiece()==NULL || (cell+((currentPos.x+1)*GRID)+(currentPos.y+2))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x+1, currentPos.y+2});
		}
	}
	if(inLimits({currentPos.x+1, currentPos.y-2})){		//(x+1,y-2)
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y-2))->getPiece()==NULL || (cell+((currentPos.x+1)*GRID)+(currentPos.y-2))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x+1, currentPos.y-2});
		}
	}
	if(inLimits({currentPos.x-1, currentPos.y+2})){		//(x-1,y+2)
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y+2))->getPiece()==NULL || (cell+((currentPos.x-1)*GRID)+(currentPos.y+2))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-1, currentPos.y+2});
		}
	}
	if(inLimits({currentPos.x-1, currentPos.y-2})){		//(x-1,y-2)
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y-2))->getPiece()==NULL || (cell+((currentPos.x-1)*GRID)+(currentPos.y-2))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-1, currentPos.y-2});
		}
	}
}
