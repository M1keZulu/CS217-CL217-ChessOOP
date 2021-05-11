#include<iostream>
#include<vector>
#include<fstream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<time.h>
#include<conio.h>
#include<sstream>
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
		virtual int numberMoves();
		
};

vector<Piece*> Piece::pieces;
Cell* Piece::cell;
Piece::Piece(Color m_color, PieceType m_name):color(m_color),name(m_name){pieces.push_back(this);moveCount=0;} //Piece Constructor
void Piece::setCellArray(Cell *m_cell){cell = m_cell;}
Color Piece::getColor(){return color;}
PieceType Piece::getName(){return name;}
void Piece::PieceMoved(){moveCount++;}
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
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getColor()==color && (cell+((currentPos.x-1)*GRID)+(currentPos.y))->getPiece()->getName()!=name){
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
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getColor()==color && (cell+((currentPos.x+1)*GRID)+(currentPos.y))->getPiece()->getName()!=name){
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
		else if((cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color && (cell+((currentPos.x)*GRID)+(currentPos.y+1))->getPiece()->getName()!=name){
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
		else if((cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color && (cell+((currentPos.x)*GRID)+(currentPos.y-1))->getPiece()->getName()!=name){
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
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color && (cell+((currentPos.x-1)*GRID)+(currentPos.y-1))->getPiece()->getName()!=name){
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
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color && (cell+((currentPos.x+1)*GRID)+(currentPos.y+1))->getPiece()->getName()!=name){
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
		else if((cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getColor()==color && (cell+((currentPos.x+1)*GRID)+(currentPos.y-1))->getPiece()->getName()!=name){
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
		else if((cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getColor()==color && (cell+((currentPos.x-1)*GRID)+(currentPos.y+1))->getPiece()->getName()!=name){
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
	Direction d;
	public:
		Pawn(Color m_color, Direction d);
		void generateMoves(Point currentPos);
};

Pawn::Pawn(Color m_color, Direction d):Piece(m_color, pawn){this->d=d;}
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
		if(moveCount==0){
			movesAvailable.push_back({currentPos.x-2,currentPos.y});
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
		if(moveCount==0){
			movesAvailable.push_back({currentPos.x+2,currentPos.y});
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
//	if(isUnderAttack({currentPos.x-1, currentPos.y})){
//		movesAvailable.push_back({currentPos.x-1, currentPos.y});
//	}
//	if(isUnderAttack({currentPos.x+1, currentPos.y})){
//		movesAvailable.push_back({currentPos.x+1, currentPos.y});
//	}
//	if(isUnderAttack({currentPos.x, currentPos.y+1})){
//		movesAvailable.push_back({currentPos.x, currentPos.y+1});
//	}
//	if(isUnderAttack({currentPos.x, currentPos.y-1})){
//		movesAvailable.push_back({currentPos.x, currentPos.y-1});
//	}
//	if(isUnderAttack({currentPos.x-1, currentPos.y+1})){
//		movesAvailable.push_back({currentPos.x-1, currentPos.y+1});
//	}
//	if(isUnderAttack({currentPos.x-1, currentPos.y-1})){
//		movesAvailable.push_back({currentPos.x-1, currentPos.y-1});
//	}
//	if(isUnderAttack({currentPos.x+1, currentPos.y+1})){
//		movesAvailable.push_back({currentPos.x+1, currentPos.y+1});
//	}
//	if(isUnderAttack({currentPos.x+1, currentPos.y-1})){
//		movesAvailable.push_back({currentPos.x+1, currentPos.y-1});
//	}
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
//Class King

//Class Board
class Board{
	private:
		Cell cells[GRID][GRID];
		Color move;
		void newMove();
		void changeMove();
		bool dummyMove(Point currentPos, Point newPos);
	public:
		Board(Color c);
		void movePiece(Point currentPos, Point newPos);
		void displayBoard();
		vector<Detail> getDetails();
		bool isCheckMate();
		Point getKing();
		bool isCheck();
		Color getMove();
		void promotePawn(Point currentPos, PieceType name);
};
Color Board::getMove(){return move;}
Board::Board(Color c){
	Color m;
	Direction d1=up,d2=down;
	if(c==white){
		m=black;
		Piece *ptr;
	ptr=new Pawn(c, d1);
	cells[6][7].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][6].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][5].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][4].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][3].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][2].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][1].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][0].setPiece(ptr);
	ptr=new Rook(c);
	cells[7][0].setPiece(ptr);
	ptr=new Rook(c);
	cells[7][7].setPiece(ptr);
	ptr=new Knight(c);
	cells[7][1].setPiece(ptr);
	ptr=new Knight(c);
	cells[7][6].setPiece(ptr);
	ptr=new Bishop(c);
	cells[7][2].setPiece(ptr);
	ptr=new Bishop(c);
	cells[7][5].setPiece(ptr);
	ptr=new Queen(c);
	cells[7][3].setPiece(ptr);
	ptr=new King(c);
	cells[7][4].setPiece(ptr);
	
	ptr=new Pawn(m, d2);
	cells[1][7].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][6].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][5].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][4].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][3].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][2].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][1].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][0].setPiece(ptr);
	ptr=new Rook(m);
	cells[0][0].setPiece(ptr);
	ptr=new Rook(m);
	cells[0][7].setPiece(ptr);
	ptr=new Knight(m);
	cells[0][1].setPiece(ptr);
	ptr=new Knight(m);
	cells[0][6].setPiece(ptr);
	ptr=new Bishop(m);
	cells[0][2].setPiece(ptr);
	ptr=new Bishop(m);
	cells[0][5].setPiece(ptr);
	ptr=new Queen(m);
	cells[0][3].setPiece(ptr);
	ptr=new King(m);
	cells[0][4].setPiece(ptr);
	}
	else if(c==black){
		m=white;
		Piece *ptr;
	ptr=new Pawn(c, d1);
	cells[6][7].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][6].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][5].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][4].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][3].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][2].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][1].setPiece(ptr);
	ptr=new Pawn(c, d1);
	cells[6][0].setPiece(ptr);
	ptr=new Rook(c);
	cells[7][0].setPiece(ptr);
	ptr=new Rook(c);
	cells[7][7].setPiece(ptr);
	ptr=new Knight(c);
	cells[7][1].setPiece(ptr);
	ptr=new Knight(c);
	cells[7][6].setPiece(ptr);
	ptr=new Bishop(c);
	cells[7][2].setPiece(ptr);
	ptr=new Bishop(c);
	cells[7][5].setPiece(ptr);
	ptr=new Queen(c);
	cells[7][4].setPiece(ptr);
	ptr=new King(c);
	cells[7][3].setPiece(ptr);
	
	ptr=new Pawn(m, d2);
	cells[1][7].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][6].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][5].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][4].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][3].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][2].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][1].setPiece(ptr);
	ptr=new Pawn(m, d2);
	cells[1][0].setPiece(ptr);
	ptr=new Rook(m);
	cells[0][0].setPiece(ptr);
	ptr=new Rook(m);
	cells[0][7].setPiece(ptr);
	ptr=new Knight(m);
	cells[0][1].setPiece(ptr);
	ptr=new Knight(m);
	cells[0][6].setPiece(ptr);
	ptr=new Bishop(m);
	cells[0][2].setPiece(ptr);
	ptr=new Bishop(m);
	cells[0][5].setPiece(ptr);
	ptr=new Queen(m);
	cells[0][4].setPiece(ptr);
	ptr=new King(m);
	cells[0][3].setPiece(ptr);
	}
	move=white; //can implement random player start functionality
	
	Piece::setCellArray(&cells[0][0]);
	newMove();
}
void Board::promotePawn(Point currentPos, PieceType name){	//does not have validation checks because it excepts incoming data to be already validated
	
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
					cells[currentPos.x][currentPos.y].getPiece()->PieceMoved();
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
				vector<Point> data = cells[x][y].getPiece()->getAvailableMoves();
				for(int i=0;i<data.size();i++){
					if(dummyMove({x, y}, data[i])){
						cells[x][y].getPiece()->addMove(data[i]);
						cout<<x<<y<<endl;
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
bool Board::isCheckMate(){
	int sum=0;
	for(int x=0;x<GRID;x++){
		for(int y=0;y<GRID;y++){
			if(cells[x][y].getPiece()!=NULL){
				if(cells[x][y].getPiece()->getColor()==move){
					sum+=cells[x][y].getPiece()->numberMoves();
				}
			}
		}
	}
	if(sum==0){
		return true;
	}
	else{
		return false;
	}
}
Point Board::getKing(){
	for(int x=0;x<GRID;x++){
		for(int y=0;y<GRID;y++){
			if(cells[x][y].getPiece()!=NULL){
				if(cells[x][y].getPiece()->getColor()==move && cells[x][y].getPiece()->getName()==king){
					return {x, y};
				}
			}
		}
	}
}
//Class Board

//Class Network
class Network{
	private:
		sf::IpAddress ip;
		sf::TcpSocket socket;
		char connectionType, mode;
		int x;
		size_t received;
		string text;
	public:
		Network(string s){
			ip=sf::IpAddress(s);
			sf::Socket::Status status = socket.connect(ip, 2000);
				if (status != sf::Socket::Done){
				    cout<<"Error! Can't connect";
				}
				else{
					cout<<"Connected";
				}
			socket.setBlocking(false);
		}
		Network(){
			sf::TcpListener listener;
			listener.listen(2000);
			listener.accept(socket);
			socket.setBlocking(false);
		}
	public:
		void send(int a, int b, int c, int d){
			ostringstream s;
			s.str("");
			s<<a<<b<<c<<d;
			string temp;
			temp += s.str();
			socket.send(temp.c_str(), temp.length() + 1);
			cout<<"@Data Sent - "<<temp<<" @"<<endl;
		}
		string receive(){
			char buffer[20000];
			if(socket.receive(buffer, sizeof(buffer), received)==sf::Socket::Done){
				socket.receive(buffer, sizeof(buffer), received);
				cout<<"@Data Received - "<<buffer<<" @"<<endl;
				return buffer;
			}
			else{
				cout<<"@Data Received - "<<buffer<<" @"<<endl;
				return "";
			}
		}
};
//Class Network

class GUI{
	private:
		Board *b;
		Network *n;
		vector<Detail> dat;
	public:
		GUI(const ConnectionType type){
			  if(type==host){
			  	n=new Network;
			  	b=new Board(white);
			  }
			  else if(type==client){
			  	n=new Network("192.168.100.88");
			  	b=new Board(black);
			  }
			  Point curPos;
			  curPos.x=-1;
			  curPos.y=-1;
			  Point newPos;
			  sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Chess");
			  sf::Event event;
			  sf::Image image;
			  image.loadFromFile("board1.png");
			  sf::Texture texture;
			  texture.loadFromImage(image);
			  sf::Sprite sprite(texture);
			  
			  sf::RectangleShape border;
			  border.setSize(sf::Vector2f(100,100));
			  border.setOutlineColor(sf::Color::Blue);
			  border.setOutlineThickness(5);
			  border.setFillColor(sf::Color::Transparent);
			  
			  sf::RectangleShape checkmate;
			  checkmate.setSize(sf::Vector2f(100,100));
			  checkmate.setOutlineColor(sf::Color::Red);
			  checkmate.setFillColor(sf::Color::Red);
			  checkmate.setPosition(-10000,-10000);
			  
			  sf::RectangleShape check;
			  check.setSize(sf::Vector2f(100,100));
			  check.setOutlineColor(sf::Color::Yellow);
			  check.setFillColor(sf::Color::Yellow);
			  check.setPosition(-10000,-10000);
			  
			  while(renderWindow.isOpen()){
			  	border.setPosition(curPos.x*100, curPos.y*100);
				if(!b->isCheck()){
					renderWindow.setTitle("Chess - Check");
			  		Point p = b->getKing();
			  		check.setPosition(p.y*100, p.x*100);
				}
				else{
					renderWindow.setTitle("Chess");
					check.setPosition(-10000, -10000);
				}
				if(b->isCheckMate()){
			  		renderWindow.setTitle("Chess - Checkmate");
			  		Point p = b->getKing();
			  		checkmate.setPosition(p.y*100, p.x*100);
				}
				if(type==host && b->getMove()==black){
					string s=n->receive();
					cout<<s<<endl;
					b->movePiece({s[0]-'0',s[1]-'0'},{s[2]-'0', s[3]-'0'});
				}
				else if(type==client && b->getMove()==white){
					string s=n->receive();
					cout<<s<<endl;
					b->movePiece({s[0]-'0',s[1]-'0'},{s[2]-'0', s[3]-'0'});
				}
			    while(renderWindow.pollEvent(event)){
			    	if(type==host && b->getMove()==white){
				        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				    		curPos.x = sf::Mouse::getPosition(renderWindow).x/(renderWindow.getSize().x/8);
				            curPos.y = sf::Mouse::getPosition(renderWindow).y/(renderWindow.getSize().y/8);
				    	}
				    	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
							newPos.x = sf::Mouse::getPosition(renderWindow).x/(renderWindow.getSize().x/8);
				            newPos.y = sf::Mouse::getPosition(renderWindow).y/(renderWindow.getSize().y/8);
							b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
							n->send(7-curPos.y, 7-curPos.x, 7-newPos.y, 7-newPos.x);
						}
					}
					else if(type==client && b->getMove()==black){
						if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				    		curPos.x = sf::Mouse::getPosition(renderWindow).x/(renderWindow.getSize().x/8);
				            curPos.y = sf::Mouse::getPosition(renderWindow).y/(renderWindow.getSize().y/8);
				    	}
				    	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
							newPos.x = sf::Mouse::getPosition(renderWindow).x/(renderWindow.getSize().x/8);
				            newPos.y = sf::Mouse::getPosition(renderWindow).y/(renderWindow.getSize().y/8);
							b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
							n->send(7-curPos.y, 7-curPos.x, 7-newPos.y, 7-newPos.x);
						}
					}
			      if (event.type == sf::Event::Closed)
			            renderWindow.close();
			    }
			    renderWindow.clear();
			    renderWindow.draw(sprite);
			    renderWindow.draw(border);
			    renderWindow.draw(check);
			    renderWindow.draw(checkmate);
			    dat=b->getDetails();
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
		GUI(){
			  b=new Board(white);
			  Point curPos;
			  curPos.x=-1;
			  curPos.y=-1;
			  Point newPos;
			  sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Chess");
			  sf::Event event;
			  sf::Image image;
			  image.loadFromFile("board1.png");
			  sf::Texture texture;
			  texture.loadFromImage(image);
			  sf::Sprite sprite(texture);
			  sf::RectangleShape border;
			  border.setSize(sf::Vector2f(100,100));
			  border.setOutlineColor(sf::Color::Blue);
			  border.setOutlineThickness(5);
			  border.setFillColor(sf::Color::Transparent);
			  
			  sf::RectangleShape checkmate;
			  checkmate.setSize(sf::Vector2f(100,100));
			  checkmate.setOutlineColor(sf::Color::Red);
			  checkmate.setFillColor(sf::Color::Red);
			  checkmate.setPosition(-10000,-10000);
			  
			  sf::RectangleShape check;
			  check.setSize(sf::Vector2f(100,100));
			  check.setOutlineColor(sf::Color::Yellow);
			  check.setFillColor(sf::Color::Yellow);
			  check.setPosition(-10000,-10000);
			  
			  while(renderWindow.isOpen()){
			  	border.setPosition(curPos.x*100, curPos.y*100);
				if(!b->isCheck()){
					renderWindow.setTitle("Chess - Check");
			  		Point p = b->getKing();
			  		check.setPosition(p.y*100, p.x*100);
				}
				else{
					renderWindow.setTitle("Chess");
					check.setPosition(-10000, -10000);
				}
				if(b->isCheckMate()){
			  		renderWindow.setTitle("Chess - Checkmate");
			  		Point p = b->getKing();
			  		checkmate.setPosition(p.y*100, p.x*100);
				}
			    while(renderWindow.pollEvent(event)){
			        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			    		curPos.x = sf::Mouse::getPosition(renderWindow).x/(renderWindow.getSize().x/8);
			            curPos.y = sf::Mouse::getPosition(renderWindow).y/(renderWindow.getSize().y/8);
			    	}
			    	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
						newPos.x = sf::Mouse::getPosition(renderWindow).x/(renderWindow.getSize().x/8);
			            newPos.y = sf::Mouse::getPosition(renderWindow).y/(renderWindow.getSize().y/8);
						b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
					}
			      if (event.type == sf::Event::Closed)
			            renderWindow.close();
			    }
			    renderWindow.clear();
			    renderWindow.draw(sprite);
			    renderWindow.draw(border);
			    renderWindow.draw(check);
			    renderWindow.draw(checkmate);
			    dat=b->getDetails();
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
	char c;
	cout<<"what do you want to do?";
	cin>>c;
	if(c=='s'){
		GUI g(host);
	}
	else if(c=='c'){
		GUI g(client);
	}
}
