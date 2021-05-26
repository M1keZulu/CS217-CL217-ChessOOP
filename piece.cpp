#include<iostream>
#include<vector>
#include "cell.h"
#include "enums_data.h"
#define GRID 8
#include "piece.h"

using namespace std;

vector<Point> Piece::getPossibleMoves(){return movesAvailable;}
vector<Piece*> Piece::pieces;
void Piece::clearPieces(){pieces.clear();}
Cell* Piece::cell;
Piece::Piece(Color m_color, PieceType m_name):color(m_color),name(m_name){pieces.push_back(this);moveCount=0;} //Piece Constructor
vector<Piece*> Piece::getPieces(){return pieces;}
void Piece::setCellArray(Cell *m_cell){cell = m_cell;}
bool Piece::enPassant(Piece *ptr){cout<<"Garbage";}
void Piece::AddenPassant(Piece *ptr){cout<<"Garbage";}
Color Piece::getColor(){return color;}
PieceType Piece::getName(){return name;}
Direction Piece::getPawnDirection(){cout<<"Garbage";}
void Piece::PieceMoved(){moveCount++;}
int Piece::getCount(){return moveCount;}
void Piece::generateMoves(Point currentPos){}
int Piece::numberMoves(){return movesAvailable.size();}
void Piece::addMove(Point pos){
	movesAvailable.push_back({pos.x, pos.y});
}
bool Piece::isUnderAttack(Point currentPos){
	int cx=currentPos.x;
	int cy=currentPos.y;
	bool flag = true;
	
	while(inLimits({currentPos.x-1,currentPos.y})){
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getColor()!=color){
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getName()==queen || (cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getName()==rook){
				flag=false;
			}
			break;
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x--;	// up
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x+1,currentPos.y})){
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getColor()!=color){
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getName()==queen || (cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getName()==rook){
				flag=false;
			}
			break;
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x++;	// down
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x,currentPos.y+1})){
		if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
		}
		else if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getName()==queen || (cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getName()==rook){
				flag=false;
			}
			break;
		}
		else if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.y++;	// right
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x,currentPos.y-1})){
		if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
		}
		else if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getName()==queen || (cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getName()==rook){
				flag=false;
			}
			break;
		}
		else if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.y--;	// left
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x-1,currentPos.y-1})){
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getName()==queen || (cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getName()==bishop){
				flag=false;
			}
			break;
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x--;
		currentPos.y--;	// diagonal 1
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x+1,currentPos.y+1})){
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getName()==queen || (cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getName()==bishop){
				flag=false;
			}
			break;
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x++;
		currentPos.y++;	// diagonal 2
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x+1,currentPos.y-1})){
		if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getName()==queen || (cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getName()==bishop){
				flag=false;
			}
			break;
		}
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x++;
		currentPos.y--;	// diagonal 3
	}
	currentPos.x=cx;
	currentPos.y=cy;
	while(inLimits({currentPos.x-1,currentPos.y+1})){
		if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color){
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getName()==queen || (cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getName()==bishop){
				flag=false;
			}
			break;
		}
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color){
			break;
		}
		currentPos.x--;
		currentPos.y++;	// diagonal 4
	}
	currentPos.x=cx;
	currentPos.y=cy;
	if(color==white){
		if(inLimits({currentPos.x-1,currentPos.y+1})){
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color && (cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getName()==pawn){
				flag=false;
			}	
		}
		if(inLimits({currentPos.x-1,currentPos.y-1})){
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color && (cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getName()==pawn){
				flag=false;
			}	
		}
	}
	else if(color==black){
		if(inLimits({currentPos.x+1,currentPos.y-1})){
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color && (cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getName()==pawn){
				flag=false;
			}	
		}
		if(inLimits({currentPos.x+1,currentPos.y+1})){
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color && (cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getName()==pawn){
				flag=false;
			}	
		}
	}	//pawn special attack case
	//knight special attack case
	if(inLimits({currentPos.x-2,currentPos.y-1})){
			if((cell+((currentPos.x-2)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x-2)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color && (cell+((currentPos.x-2)*GRID)+(currentPos.y-1))->getPiece()->getName()==knight){
				flag=false;
			}	
	}	//(x-2,y-1)
	if(inLimits({currentPos.x+2,currentPos.y-1})){
			if((cell+((currentPos.x+2)*GRID)+(currentPos.y-1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x+2)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color && (cell+((currentPos.x+2)*GRID)+(currentPos.y-1))->getPiece()->getName()==knight){
				flag=false;
			}	
	}	//(x+2,y-1)
	if(inLimits({currentPos.x+2,currentPos.y+1})){
			if((cell+((currentPos.x+2)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x+2)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color && (cell+((currentPos.x+2)*GRID)+(currentPos.y+1))->getPiece()->getName()==knight){
				flag=false;
			}	
	}	//(x+2,y+1)
	if(inLimits({currentPos.x-2,currentPos.y+1})){
			if((cell+((currentPos.x-2)*GRID)+(currentPos.y+1))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x-2)*GRID)+(currentPos.y+1))->getPiece()->getColor()!=color && (cell+((currentPos.x-2)*GRID)+(currentPos.y+1))->getPiece()->getName()==knight){
				flag=false;
			}	
	}	//(x-2,y+1)
	if(inLimits({currentPos.x+1,currentPos.y+2})){
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y+2))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x+1)*GRID)+(currentPos.y+2))->getPiece()->getColor()!=color && (cell+((currentPos.x+1)*GRID)+(currentPos.y+2))->getPiece()->getName()==knight){
				flag=false;
			}	
	}	//(x+1,y+2)
	if(inLimits({currentPos.x+1,currentPos.y-2})){
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y-2))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x+1)*GRID)+(currentPos.y-2))->getPiece()->getColor()!=color && (cell+((currentPos.x+1)*GRID)+(currentPos.y-2))->getPiece()->getName()==knight){
				flag=false;
			}	
	}	//(x+1,y-2)
	if(inLimits({currentPos.x-1,currentPos.y+2})){
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y+2))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x-1)*GRID)+(currentPos.y+2))->getPiece()->getColor()!=color && (cell+((currentPos.x-1)*GRID)+(currentPos.y+2))->getPiece()->getName()==knight){
				flag=false;
			}	
	}	//(x-1,y+2)
	if(inLimits({currentPos.x-1,currentPos.y-2})){
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y-2))->getPiece()==NULL){
			//do nothing - this is important to avoid segmentation fault when calling the getPiece() fucntion
			}
			else if((cell+((currentPos.x-1)*GRID)+(currentPos.y-2))->getPiece()->getColor()!=color && (cell+((currentPos.x-1)*GRID)+(currentPos.y-2))->getPiece()->getName()==knight){
				flag=false;
			}	
	}	//(x-1,y-2)
		
	return flag;
}
int Piece::isMoveLegal(Point newPos){
	for(int i=0;i<movesAvailable.size();i++){
		if(movesAvailable[i].x==newPos.x&&movesAvailable[i].y==newPos.y){
			return 1;
		}
	}
	return 0;
}
int Piece::inLimits(Point checkPos){
	if(checkPos.x>=0&&checkPos.x<8&&checkPos.y>=0&&checkPos.y<8){
		return 1;
	}
	else{
		return 0;
	}
}
vector<Point> Piece::getAvailableMoves(){
	vector<Point> ret = movesAvailable;
	movesAvailable.clear();
	return ret;
}
