#include<iostream>
#include<vector>
#include<fstream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<time.h>
#define GRID 8

using namespace std;

//Data Types
enum PieceType{
	king, queen, bishop, knight, rook, pawn	
};

enum Color{
	black, white
};

enum Status{
	alive, dead
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
//DataTypes

//Forward Decleration for Circular Dependency
class Cell;
class Piece;
class Board;
class GUI;

//Class Cell
class Cell{
	protected:
		Piece *piece;
	public:
		Cell();
		void setNull();
		void setPiece(Piece *m_piece);
		Piece* getPiece();
};

Cell::Cell(){piece=NULL;}
void Cell::setNull(){piece=NULL;}
void Cell::setPiece(Piece *m_piece){piece=m_piece;}
Piece* Cell::getPiece(){return piece;}
//Class Cell

//Class Piece
class Piece{
	protected:
		const PieceType name;
		static Cell	*cell;
		const Color color;
		static vector<Piece*> pieces;
		int moveCount;
	
	public:
		vector<Point> movesAvailable; //restore to protected -- debugging comment
		Piece(Color m_color, PieceType name);
		static void setCellArray(Cell *m_cell);
		virtual Color getColor();
		virtual PieceType getName();
		virtual void PieceMoved();
		virtual vector<Point> getAvailableMoves();
		int inLimits(Point checkPos);
		virtual void generateMoves(Point currentPos);
		virtual int isMoveLegal(Point newPos);
		virtual bool isUnderAttack(Point currentPos);
		virtual void addMove(Point pos);
		
};

vector<Piece*> Piece::pieces;
Cell* Piece::cell;
Piece::Piece(Color m_color, PieceType m_name):color(m_color),name(m_name){pieces.push_back(this);moveCount=0;} //Piece Constructor
void Piece::setCellArray(Cell *m_cell){cell = m_cell;}
Color Piece::getColor(){return color;}
PieceType Piece::getName(){return name;}
void Piece::PieceMoved(){moveCount++;}
void Piece::generateMoves(Point currentPos){}
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
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getColor()==color && (cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getName()!=king){
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
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getColor()==color && (cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getName()!=king){
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
		else if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color && (cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getName()!=king){
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
		else if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color && (cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getName()!=king){
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
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color && (cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getName()!=king){
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
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color && (cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getName()!=king){
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
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color && (cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getName()!=king){
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
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color && (cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getName()!=king){
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
//Class Piece

//Class Pawn
class Pawn:public Piece{
	public:
		Pawn(Color m_color);
		void generateMoves(Point currentPos);
};

Pawn::Pawn(Color m_color):Piece(m_color, pawn){}
void Pawn::generateMoves(Point currentPos){
	movesAvailable.clear();
	if(color==white){
		if(inLimits({currentPos.x-1, currentPos.y})){									//(x-1)(y)
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()==NULL){
				movesAvailable.push_back({currentPos.x-1, currentPos.y});
			}
		}
		if(inLimits({currentPos.x-1, currentPos.y-1})){									//(x-1)(y-1)
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()!=NULL && (cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getColor()==black){
				movesAvailable.push_back({currentPos.x-1, currentPos.y-1});
			}
		}
		if(inLimits({currentPos.x-1, currentPos.y+1})){									//(x-1)(y+1)
			if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()!=NULL && (cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getColor()==black){
				movesAvailable.push_back({currentPos.x-1, currentPos.y+1});
			}
		}
	}
	else if(color==black){
		if(inLimits({currentPos.x+1, currentPos.y})){									//(x+1)(y)
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()==NULL){
				movesAvailable.push_back({currentPos.x+1, currentPos.y});
			}
		}
		if(inLimits({currentPos.x+1, currentPos.y+1})){									//(x+1)(y+1)
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()!=NULL && (cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getColor()==white){
				movesAvailable.push_back({currentPos.x+1, currentPos.y+1});
			}
		}
		if(inLimits({currentPos.x+1, currentPos.y-1})){									//(x+1)(y-1)
			if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()!=NULL && (cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getColor()==white){
				movesAvailable.push_back({currentPos.x+1, currentPos.y-1});
			}
		}
	}
}
//Class Pawn

//Class Knight
class Knight:public Piece{
	public:
		Knight(Color m_color);
		void generateMoves(Point currentPos);
};

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
//Class Knight

//Class Rook
class Rook:public Piece{
	public:
		Rook(Color m_color);
		void generateMoves(Point currentPos);
};

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
//Class Rook

//Class Bishop
class Bishop:public Piece{
	public:
		Bishop(Color m_color);
		void generateMoves(Point currentPos);
};

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
//Class Bishop

//Class Queen
class Queen:public Piece{
	public:
		Queen(Color m_color);
		void generateMoves(Point currentPos);
};

Queen::Queen(Color m_color):Piece(m_color, queen){}
void Queen::generateMoves(Point currentPos){
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
	currentPos.x=cx;
	currentPos.y=cy;
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
//Class Queen

//Class King
class King:public Piece{
	public:
		King(Color m_color);
		void generateMoves(Point currentPos);
};

King::King(Color m_color):Piece(m_color, king){}

void King::generateMoves(Point currentPos){
	movesAvailable.clear();
	if(isUnderAttack({currentPos.x-1, currentPos.y})){
		movesAvailable.push_back({currentPos.x-1, currentPos.y});
	}
	if(isUnderAttack({currentPos.x+1, currentPos.y})){
		movesAvailable.push_back({currentPos.x+1, currentPos.y});
	}
	if(isUnderAttack({currentPos.x, currentPos.y+1})){
		movesAvailable.push_back({currentPos.x, currentPos.y+1});
	}
	if(isUnderAttack({currentPos.x, currentPos.y-1})){
		movesAvailable.push_back({currentPos.x, currentPos.y-1});
	}
	if(isUnderAttack({currentPos.x-1, currentPos.y+1})){
		movesAvailable.push_back({currentPos.x-1, currentPos.y+1});
	}
	if(isUnderAttack({currentPos.x-1, currentPos.y-1})){
		movesAvailable.push_back({currentPos.x-1, currentPos.y-1});
	}
	if(isUnderAttack({currentPos.x+1, currentPos.y+1})){
		movesAvailable.push_back({currentPos.x+1, currentPos.y+1});
	}
	if(isUnderAttack({currentPos.x+1, currentPos.y-1})){
		movesAvailable.push_back({currentPos.x+1, currentPos.y-1});
	}
}
//Class King

//Class Board
class Board{
	private:
		Cell cells[GRID][GRID];
		Color move;
		void newMove();
		bool isCheck();
		void changeMove();
		bool dummyMove(Point currentPos, Point newPos);
	public:
		Board();
		void movePiece(Point currentPos, Point newPos);
		void displayBoard();
		vector<Detail> getDetails();
};
Board::Board(){
	move=white; //can implement random player start functionality
	Piece *ptr;
	ptr=new Pawn(white);
	cells[6][7].setPiece(ptr);
	ptr=new Pawn(white);
	cells[6][6].setPiece(ptr);
	ptr=new Pawn(white);
	cells[6][5].setPiece(ptr);
	ptr=new Pawn(white);
	cells[6][4].setPiece(ptr);
	ptr=new Pawn(white);
	cells[6][3].setPiece(ptr);
	ptr=new Pawn(white);
	cells[6][2].setPiece(ptr);
	ptr=new Pawn(white);
	cells[6][1].setPiece(ptr);
	ptr=new Pawn(white);
	cells[6][0].setPiece(ptr);
	ptr=new Rook(white);
	cells[7][0].setPiece(ptr);
	ptr=new Rook(white);
	cells[7][7].setPiece(ptr);
	ptr=new Knight(white);
	cells[7][1].setPiece(ptr);
	ptr=new Knight(white);
	cells[7][6].setPiece(ptr);
	ptr=new Bishop(white);
	cells[7][2].setPiece(ptr);
	ptr=new Bishop(white);
	cells[7][5].setPiece(ptr);
	ptr=new Queen(white);
	cells[7][3].setPiece(ptr);
	ptr=new King(white);
	cells[7][4].setPiece(ptr);
	
	ptr=new Pawn(black);
	cells[1][7].setPiece(ptr);
	ptr=new Pawn(black);
	cells[1][6].setPiece(ptr);
	ptr=new Pawn(black);
	cells[1][5].setPiece(ptr);
	ptr=new Pawn(black);
	cells[1][4].setPiece(ptr);
	ptr=new Pawn(black);
	cells[1][3].setPiece(ptr);
	ptr=new Pawn(black);
	cells[1][2].setPiece(ptr);
	ptr=new Pawn(black);
	cells[1][1].setPiece(ptr);
	ptr=new Pawn(black);
	cells[1][0].setPiece(ptr);
	ptr=new Rook(black);
	cells[0][0].setPiece(ptr);
	ptr=new Rook(black);
	cells[0][7].setPiece(ptr);
	ptr=new Knight(black);
	cells[0][1].setPiece(ptr);
	ptr=new Knight(black);
	cells[0][6].setPiece(ptr);
	ptr=new Bishop(black);
	cells[0][2].setPiece(ptr);
	ptr=new Bishop(black);
	cells[0][5].setPiece(ptr);
	ptr=new Queen(black);
	cells[0][3].setPiece(ptr);
	ptr=new King(black);
	cells[0][4].setPiece(ptr);
	
	
	Piece::setCellArray(&cells[0][0]);
	newMove();
}
bool Board::dummyMove(Point currentPos, Point newPos){
	Piece *curP=cells[currentPos.x][currentPos.y].getPiece();
	Piece *newP=cells[newPos.x][newPos.y].getPiece();
	Piece *k;
	bool flag;
	cells[newPos.x][newPos.y].setPiece(curP);
	cells[currentPos.x][currentPos.y].setNull();
	flag = isCheck();
	cells[newPos.x][newPos.y].setPiece(newP);
	cells[currentPos.x][currentPos.y].setPiece(curP);
	return flag;
}
void Board::movePiece(Point currentPos, Point newPos){
		if(currentPos.x>=0&&currentPos.x<8&&currentPos.y>=0&&currentPos.y<8){
			if(cells[currentPos.x][currentPos.y].getPiece()!=NULL){
				if(cells[currentPos.x][currentPos.y].getPiece()->isMoveLegal(newPos) && cells[currentPos.x][currentPos.y].getPiece()->getColor()==move){
					cells[newPos.x][newPos.y].setPiece(cells[currentPos.x][currentPos.y].getPiece());
					cells[currentPos.x][currentPos.y].setNull();
					changeMove();
					newMove();
				}
			}
		}
}
void Board::changeMove(){
	if(move==white){
		move=black;
	}
	else if(move==black){
		move=white;
	}
}
void Board::displayBoard(){
	for(int x=0;x<GRID;x++){
		for(int y=0;y<GRID;y++){
			if(cells[x][y].getPiece()==NULL){
				cout<<". ";
			}
			else if(cells[x][y].getPiece()->getName()==pawn){
				cout<<"P ";
			}
			else if(cells[x][y].getPiece()->getName()==knight){
				cout<<"K ";
			}
		}
		cout<<endl;
	}
}
vector<Detail> Board::getDetails(){
	vector<Detail> data;
	for(int x=0;x<GRID;x++){
		for(int y=0;y<GRID;y++){
			if(cells[x][y].getPiece()!=NULL){
				data.push_back({x,y,cells[x][y].getPiece()->getColor(),cells[x][y].getPiece()->getName()});
			}
		}
	}
	return data;
}
void Board::newMove(){
	for(int x=0;x<GRID;x++){
		for(int y=0;y<GRID;y++){
			if(cells[x][y].getPiece()!=NULL){
				cells[x][y].getPiece()->generateMoves({x,y});
			}
		}
	}
	for(int x=0;x<GRID;x++){
		for(int y=0;y<GRID;y++){
			if(cells[x][y].getPiece()!=NULL){
				if(cells[x][y].getPiece()->getName()==king){
					continue;
				}
				vector<Point> data = cells[x][y].getPiece()->getAvailableMoves();
				for(int i=0;i<data.size();i++){
					if(dummyMove({x, y}, data[i])){
						cells[x][y].getPiece()->addMove(data[i]);
					}
				}
			}
		}
	}
}
bool Board::isCheck(){
	for(int x=0;x<GRID;x++){
		for(int y=0;y<GRID;y++){
			if(cells[x][y].getPiece()!=NULL){
				if(cells[x][y].getPiece()->getName()==king && cells[x][y].getPiece()->getColor()==move){
					if(cells[x][y].getPiece()->isUnderAttack({x, y})==false){
						return false;
					}
				}
			}
		}
	}
	return true;
}
//Class Board

class GUI{
	private:
		Board b;
		vector<Detail> dat;
	public:
		GUI(){
			  Point curPos;
			  curPos.x=-1;
			  curPos.y=-1;
			  Point newPos;
			  sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Chess");
			  sf::Event event;
			  sf::Image image;
			  image.create(800, 800, sf::Color::Black);
			  
			  bool isBlackPixel = false;
			  sf::Color blackPixel(241,217,181,255);
			  sf::Color whitePixel(181,136,99,255);
			  
			  for (int y = 0; y < 800; y++){
			    for (int x = 0; x < 800; x++){
			      if (isBlackPixel)
			        image.setPixel(x, y, blackPixel);
			      else
			        image.setPixel(x, y, whitePixel);
			      if (!(x % 100))
			        isBlackPixel = !isBlackPixel;
			    }
			    if(!(y%100))
			      isBlackPixel = !isBlackPixel;
			  }
			  sf::Texture texture;
			  texture.loadFromImage(image);
			  sf::Sprite sprite(texture);
			  sf::RectangleShape border;
			  border.setSize(sf::Vector2f(100,100));
			  border.setOutlineColor(sf::Color::Blue);
			  border.setOutlineThickness(5);
			  border.setFillColor(sf::Color::Transparent);
			  while (renderWindow.isOpen()){
			  	border.setPosition(curPos.x*100, curPos.y*100);
			    while (renderWindow.pollEvent(event)){
			        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			    		curPos.x = sf::Mouse::getPosition(renderWindow).x/100;
			            curPos.y = sf::Mouse::getPosition(renderWindow).y/100;
			    	}
			    	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
						newPos.x = sf::Mouse::getPosition(renderWindow).x/100;
			            newPos.y = sf::Mouse::getPosition(renderWindow).y/100;
						b.movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
					}
			      if (event.type == sf::Event::Closed)
			            renderWindow.close();
			    }
			    renderWindow.clear();
			    renderWindow.draw(sprite);
			    renderWindow.draw(border);
			    dat=b.getDetails();
			    for(int i=0;i<dat.size();i++){
			    	if(dat[i].name==pawn&&dat[i].color==white){
			    		int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("w_pawn.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(13+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==pawn&&dat[i].color==black){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("b_pawn.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(13+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==knight&&dat[i].color==white){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("w_knight.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(13+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==knight&&dat[i].color==black){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("b_knight.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(13+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==rook&&dat[i].color==white){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("w_rook.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(13+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==rook&&dat[i].color==black){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("b_rook.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(13+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==bishop&&dat[i].color==white){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("w_bishop.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(13+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==bishop&&dat[i].color==black){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("b_bishop.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(13+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==queen&&dat[i].color==white){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("w_queen.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(2+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==queen&&dat[i].color==black){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("b_queen.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(2+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==king&&dat[i].color==white){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("w_king.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(8+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
					else if(dat[i].name==king&&dat[i].color==black){
						int x =dat[i].x;
			    		int y =dat[i].y;
			    		sf::Image i;
			    		i.loadFromFile("b_king.png");
			    		sf::Texture t;
			    		t.loadFromImage(i);
			    		sf::Sprite s;
			    		s.setTexture(t);
			    		s.setScale(0.7,0.7);
			    		s.setPosition(8+y*100,5+x*100);
			    		renderWindow.draw(s);
					}
				}
			    renderWindow.display();
			  }
		}
};

int main(){
	GUI g;
}
