/*
	Name: Chess-OOP
	Author:	Muhammad Zain Ul Abiddin
	Description: Chess game made using OOP principles for Semester Project
	Date: 24/05/2021
*/

#include<iostream>
#include<vector>
#include<fstream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<time.h>
#include<windows.h>
#include<string>
#include<algorithm>
#include<conio.h>
#include<string.h>
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

struct Moves{
	Point p;
	string cell;
};
//Data Types

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
		vector<Point> movesAvailable;
		vector<Piece*> pawnLocation;
	public:
		Piece(Color m_color, PieceType name);
		static void setCellArray(Cell *m_cell);
		static vector<Piece*> getPieces();
		static void clearPieces();
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
		virtual int getCount();
		virtual Direction getPawnDirection();
		virtual bool enPassant(Piece *ptr);
		virtual void AddenPassant(Piece *ptr);
		vector<Point> getPossibleMoves();
};
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
//Class Piece

//Class Pawn
class Pawn:public Piece{
	Direction d;
	public:
		Pawn(Color m_color, Direction d);
		void generateMoves(Point currentPos);
		Direction getPawnDirection();
		bool enPassant(Piece *ptr);
		void AddenPassant(Piece *ptr);
};

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
		sf::Music move_sound;
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
		bool isStaleMate();
		vector<Moves> getMoves(Point curPos);
		~Board();
};
Board::~Board(){
	vector<Piece*> destroy = Piece::getPieces();
	Piece *ptr;
	cout<<destroy.size()<<endl;
	for(int i=0;i<destroy.size();i++){
		ptr = destroy[i];
		delete ptr;
	}
	Piece::clearPieces();
}
vector<Moves> Board::getMoves(Point curPos){
	vector<Point> temp;
	vector<Moves> ret;
	if(curPos.x>=0 && curPos.x<8 && curPos.y>=0 && curPos.y<8){
		if(cells[curPos.x][curPos.y].getPiece()!=NULL){
			if(cells[curPos.x][curPos.y].getPiece()->getColor()==move){
				temp = cells[curPos.x][curPos.y].getPiece()->getPossibleMoves();
				for(int i=0;i<temp.size();i++){
					if(cells[temp[i].x][temp[i].y].getPiece()==NULL){
						ret.push_back({{temp[i].x, temp[i].y}, "NULL"});
					}
					else{
						ret.push_back({{temp[i].x, temp[i].y}, ""});
					}
				}
			}
			
		}	
	}
	return ret;
}
Color Board::getMove(){return move;}
Board::Board(Color c){
	Color m;
	Direction d1=up,d2=down;
	if(c==white){
		m=black;
		Piece *ptr;
	ptr=new Pawn(c, d1);
	move_sound.openFromFile("move_sound.wav");
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
void Board::promotePawn(Point currentPos, PieceType name){
	if(cells[currentPos.x][currentPos.y].getPiece()!=NULL){
		if(cells[currentPos.x][currentPos.y].getPiece()->getName()==pawn){
			if(name==queen){
				Piece *ptr=new Queen(cells[currentPos.x][currentPos.y].getPiece()->getColor());
				cells[currentPos.x][currentPos.y].setPiece(ptr);
			}
			else if(name==rook){
				Piece *ptr=new Rook(cells[currentPos.x][currentPos.y].getPiece()->getColor());
				cells[currentPos.x][currentPos.y].setPiece(ptr);
			}
			else if(name==bishop){
				Piece *ptr=new Bishop(cells[currentPos.x][currentPos.y].getPiece()->getColor());
				cells[currentPos.x][currentPos.y].setPiece(ptr);
			}
			else if(name==knight){
				Piece *ptr=new Knight(cells[currentPos.x][currentPos.y].getPiece()->getColor());
				cells[currentPos.x][currentPos.y].setPiece(ptr);
			}
			newMove();
		}
	}
}
bool Board::dummyMove(Point currentPos, Point newPos){
	Piece *curP=cells[currentPos.x][currentPos.y].getPiece();
	Piece *newP=cells[newPos.x][newPos.y].getPiece();
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
				move_sound.play();
				changeMove();
				newMove();
				return; //if bugs remove this line - debugging comment
			}
			else if(cells[currentPos.x][currentPos.y].getPiece()->getName()==king && cells[currentPos.x][currentPos.y].getPiece()->getCount()==0 && cells[currentPos.x][currentPos.y].getPiece()->getColor()==move){
				if(newPos.x==currentPos.x && newPos.y==currentPos.y+2){
					if(cells[currentPos.x][currentPos.y+3].getPiece()!=NULL){
						if(cells[currentPos.x][currentPos.y+3].getPiece()->getName()==rook && cells[currentPos.x][currentPos.y+3].getPiece()->getCount()==0){
							if(cells[currentPos.x][currentPos.y+1].getPiece()==NULL && cells[currentPos.x][currentPos.y+2].getPiece()==NULL){
								if(isCheck() && cells[currentPos.x][currentPos.y].getPiece()->isUnderAttack({currentPos.x, currentPos.y+1}) && cells[currentPos.x][currentPos.y].getPiece()->isUnderAttack({currentPos.x, currentPos.y+2})){
									cells[currentPos.x][currentPos.y+2].setPiece(cells[currentPos.x][currentPos.y].getPiece());
									cells[currentPos.x][currentPos.y].setNull();
									cells[currentPos.x][currentPos.y+1].setPiece(cells[currentPos.x][currentPos.y+3].getPiece());
									cells[currentPos.x][currentPos.y+3].setNull();
									move_sound.play();
									changeMove();
									newMove();
									return;
								}
							}
						}
					}
				}
				if(newPos.x==currentPos.x && newPos.y==currentPos.y-2){
					if(cells[currentPos.x][currentPos.y-3].getPiece()!=NULL){
						if(cells[currentPos.x][currentPos.y-3].getPiece()->getName()==rook && cells[currentPos.x][currentPos.y-3].getPiece()->getCount()==0){
							if(cells[currentPos.x][currentPos.y-1].getPiece()==NULL && cells[currentPos.x][currentPos.y-2].getPiece()==NULL){
								if(isCheck() && cells[currentPos.x][currentPos.y].getPiece()->isUnderAttack({currentPos.x, currentPos.y-1}) && cells[currentPos.x][currentPos.y].getPiece()->isUnderAttack({currentPos.x, currentPos.y-2})){
									cells[currentPos.x][currentPos.y-2].setPiece(cells[currentPos.x][currentPos.y].getPiece());
									cells[currentPos.x][currentPos.y].setNull();
									cells[currentPos.x][currentPos.y-1].setPiece(cells[currentPos.x][currentPos.y-3].getPiece());
									cells[currentPos.x][currentPos.y-3].setNull();
									move_sound.play();
									changeMove();
									newMove();
									return;
								}
							}
						}
					}
				}
				if(newPos.x==currentPos.x && newPos.y==currentPos.y-2){
					if(cells[currentPos.x][currentPos.y-4].getPiece()!=NULL){
						if(cells[currentPos.x][currentPos.y-4].getPiece()->getName()==rook && cells[currentPos.x][currentPos.y-4].getPiece()->getCount()==0){
							if(cells[currentPos.x][currentPos.y-1].getPiece()==NULL && cells[currentPos.x][currentPos.y-2].getPiece()==NULL){
								if(isCheck() && cells[currentPos.x][currentPos.y].getPiece()->isUnderAttack({currentPos.x, currentPos.y-1}) && cells[currentPos.x][currentPos.y].getPiece()->isUnderAttack({currentPos.x, currentPos.y-2})){
									cells[currentPos.x][currentPos.y-2].setPiece(cells[currentPos.x][currentPos.y].getPiece());
									cells[currentPos.x][currentPos.y].setNull();
									cells[currentPos.x][currentPos.y-1].setPiece(cells[currentPos.x][currentPos.y-4].getPiece());
									cells[currentPos.x][currentPos.y-4].setNull();
									move_sound.play();
									changeMove();
									newMove();
									return;
								}
							}
						}
					}
				}
				if(newPos.x==currentPos.x && newPos.y==currentPos.y+2){
					if(cells[currentPos.x][currentPos.y+4].getPiece()!=NULL){
						if(cells[currentPos.x][currentPos.y+4].getPiece()->getName()==rook && cells[currentPos.x][currentPos.y+4].getPiece()->getCount()==0){
							if(cells[currentPos.x][currentPos.y+1].getPiece()==NULL && cells[currentPos.x][currentPos.y+2].getPiece()==NULL){
								if(isCheck() && cells[currentPos.x][currentPos.y].getPiece()->isUnderAttack({currentPos.x, currentPos.y+1}) && cells[currentPos.x][currentPos.y].getPiece()->isUnderAttack({currentPos.x, currentPos.y+2})){
									cells[currentPos.x][currentPos.y+2].setPiece(cells[currentPos.x][currentPos.y].getPiece());
									cells[currentPos.x][currentPos.y].setNull();
									cells[currentPos.x][currentPos.y+1].setPiece(cells[currentPos.x][currentPos.y+4].getPiece());
									cells[currentPos.x][currentPos.y+4].setNull();
									move_sound.play();
									changeMove();
									newMove();
									return;
								}
							}
						}
					}
				}
			}
			else if(cells[currentPos.x][currentPos.y].getPiece()->getName()==pawn && cells[currentPos.x][currentPos.y].getPiece()->getColor()==move){
				if(cells[currentPos.x][currentPos.y].getPiece()->getPawnDirection()==up){
					if(cells[currentPos.x][currentPos.y+1].getPiece()!=NULL){
						if(cells[currentPos.x][currentPos.y+1].getPiece()->getName()==pawn && cells[currentPos.x][currentPos.y+1].getPiece()->getColor()!=move && currentPos.x==3 && newPos.x==currentPos.x-1 && newPos.y==currentPos.y+1 && cells[currentPos.x][currentPos.y+1].getPiece()->getCount()==1 && cells[currentPos.x][currentPos.y+1].getPiece()->enPassant(cells[currentPos.x][currentPos.y].getPiece())){
							Piece *temp = cells[currentPos.x][currentPos.y+1].getPiece();
							cells[newPos.x][newPos.y].setPiece(cells[currentPos.x][currentPos.y].getPiece());
							cells[currentPos.x][currentPos.y].setNull();
							cells[currentPos.x][currentPos.y+1].setNull();
							if(!isCheck()){
								cells[currentPos.x][currentPos.y].setPiece(cells[newPos.x][newPos.y].getPiece());
								cells[newPos.x][newPos.y].setNull();
								cells[currentPos.x][currentPos.y+1].setPiece(temp);
							}
							else{
								cells[newPos.x][newPos.y].getPiece()->PieceMoved();
								move_sound.play();
								changeMove();
								newMove();
							}
							return; //if bugs remove this line - debugging comment
						}
					}
				    if(cells[currentPos.x][currentPos.y-1].getPiece()!=NULL){
						if(cells[currentPos.x][currentPos.y-1].getPiece()->getName()==pawn && cells[currentPos.x][currentPos.y-1].getPiece()->getColor()!=move && currentPos.x==3 && newPos.x==currentPos.x-1 && newPos.y==currentPos.y-1 && cells[currentPos.x][currentPos.y-1].getPiece()->getCount()==1 && cells[currentPos.x][currentPos.y-1].getPiece()->enPassant(cells[currentPos.x][currentPos.y].getPiece())){
							Piece *temp = cells[currentPos.x][currentPos.y-1].getPiece();
							cells[newPos.x][newPos.y].setPiece(cells[currentPos.x][currentPos.y].getPiece());
							cells[currentPos.x][currentPos.y].setNull();
							cells[currentPos.x][currentPos.y-1].setNull();
							if(!isCheck()){
								cells[currentPos.x][currentPos.y].setPiece(cells[newPos.x][newPos.y].getPiece());
								cells[newPos.x][newPos.y].setNull();
								cells[currentPos.x][currentPos.y-1].setPiece(temp);
							}
							else{
								cells[newPos.x][newPos.y].getPiece()->PieceMoved();
								move_sound.play();
								changeMove();
								newMove();
							}
							return; //if bugs remove this line - debugging comment
						}
					}
					
				}
				else if(cells[currentPos.x][currentPos.y].getPiece()->getPawnDirection()==down){
					if(cells[currentPos.x][currentPos.y+1].getPiece()!=NULL){
						if(cells[currentPos.x][currentPos.y+1].getPiece()->getName()==pawn && cells[currentPos.x][currentPos.y+1].getPiece()->getColor()!=move && currentPos.x==4 && newPos.x==currentPos.x+1 && newPos.y==currentPos.y+1 && cells[currentPos.x][currentPos.y+1].getPiece()->getCount()==1 && cells[currentPos.x][currentPos.y+1].getPiece()->enPassant(cells[currentPos.x][currentPos.y].getPiece())){
							Piece *temp = cells[currentPos.x][currentPos.y+1].getPiece();
							cells[newPos.x][newPos.y].setPiece(cells[currentPos.x][currentPos.y].getPiece());
							cells[currentPos.x][currentPos.y].setNull();
							cells[currentPos.x][currentPos.y+1].setNull();
							if(!isCheck()){
								cells[currentPos.x][currentPos.y].setPiece(cells[newPos.x][newPos.y].getPiece());
								cells[newPos.x][newPos.y].setNull();
								cells[currentPos.x][currentPos.y+1].setPiece(temp);
							}
							else{
								cells[newPos.x][newPos.y].getPiece()->PieceMoved();
								move_sound.play();
								changeMove();
								newMove();
							}
							return; //if bugs remove this line - debugging comment
						}
					}
					if(cells[currentPos.x][currentPos.y-1].getPiece()!=NULL){
						if(cells[currentPos.x][currentPos.y-1].getPiece()->getName()==pawn && cells[currentPos.x][currentPos.y-1].getPiece()->getColor()!=move && currentPos.x==4 && newPos.x==currentPos.x+1 && newPos.y==currentPos.y-1 && cells[currentPos.x][currentPos.y-1].getPiece()->getCount()==1 && cells[currentPos.x][currentPos.y-1].getPiece()->enPassant(cells[currentPos.x][currentPos.y].getPiece())){
							Piece *temp = cells[currentPos.x][currentPos.y-1].getPiece();
							cells[newPos.x][newPos.y].setPiece(cells[currentPos.x][currentPos.y].getPiece());
							cells[currentPos.x][currentPos.y].setNull();
							cells[currentPos.x][currentPos.y-1].setNull();
							if(!isCheck()){
								cells[currentPos.x][currentPos.y].setPiece(cells[newPos.x][newPos.y].getPiece());
								cells[newPos.x][newPos.y].setNull();
								cells[currentPos.x][currentPos.y-1].setPiece(temp);
							}
							else{
								cells[newPos.x][newPos.y].getPiece()->PieceMoved();
								move_sound.play();
								changeMove();
								newMove();
							}
							return; //if bugs remove this line - debugging comment
						}
					}
				}
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
					}
				}
			}
		}
	}
	for(int x=0;x<GRID;x++){
		for(int y=0;y<GRID;y++){
			if(cells[x][y].getPiece()!=NULL){
				if(cells[x][y].getPiece()->getName()==pawn && cells[x][y].getPiece()->getColor()==move){
					if(cells[x][y+1].getPiece()!=NULL){
						if(cells[x][y+1].getPiece()->getColor()!=move && cells[x][y+1].getPiece()->getName()==pawn){
							cells[x][y].getPiece()->AddenPassant(cells[x][y+1].getPiece());
						}
					}
					if(cells[x][y-1].getPiece()!=NULL){
						if(cells[x][y-1].getPiece()->getColor()!=move && cells[x][y-1].getPiece()->getName()==pawn){
							cells[x][y].getPiece()->AddenPassant(cells[x][y-1].getPiece());
						}
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
	if(sum==0 && !isCheck()){
		return true;
	}
	else{
		return false;
	}
}
bool Board::isStaleMate(){
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
	if(sum==0 && isCheck()){
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
				if(status!=sf::Socket::Done){
				    cout<<"Failure";
				    exit(0);
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
//			cout<<"@Data Sent - "<<temp<<" @"<<endl;
		}
		void send(int a, int b, int c, int d, PieceType promotion){
			ostringstream s;
			s.str("");
			s<<a<<b<<c<<d;
			string temp;
			temp += s.str();
			temp+="?";
			if(promotion==queen){
				temp+="q";
			}
			else if(promotion==rook){
				temp+="r";
			}
			else if(promotion==bishop){
				temp+="b";
			}
			else if(promotion==knight){
				temp+="k";
			}
			socket.send(temp.c_str(), temp.length() + 1);
//			cout<<"@Data Sent - "<<temp<<" @"<<endl;
		}
		string receive(){
			char buffer[20000];
			if(socket.receive(buffer, sizeof(buffer), received)==sf::Socket::Done){
				socket.receive(buffer, sizeof(buffer), received);
//				cout<<"@Data Received - "<<buffer<<" @"<<endl;
				return buffer;
			}
			else{
//				cout<<"@Data Received - "<<buffer<<" @"<<endl;
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
		PieceType promote;
		vector<Moves> available;
	public:
		GUI(const ConnectionType type, string ip){
			  if(type==host){
			  	n=new Network;
			  	b=new Board(white);
			  }
			  else if(type==client){
			  	n=new Network(ip);
			  	b=new Board(black);
			  }
			  Point curPos;
			  promote=queen;
			  curPos.x=-1;
			  curPos.y=-1;
			  Point newPos;
			  sf::RenderWindow chessWindow(sf::VideoMode(800, 800), "Chess");
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
			  
			  while(chessWindow.isOpen()){
			  	border.setPosition(curPos.x*100, curPos.y*100);
				if(!b->isCheck()){
					chessWindow.setTitle("Chess - Check");
			  		Point p = b->getKing();
			  		check.setPosition(p.y*100, p.x*100);
				}
				else{
					if(b->getMove()==1){
						chessWindow.setTitle("Chess - White Moves");	
					}
					else{
						chessWindow.setTitle("Chess - Black Moves");
					}
					check.setPosition(-10000, -10000);
				}
				if(b->isCheckMate()){
			  		chessWindow.setTitle("Chess - Checkmate");
			  		Point p = b->getKing();
			  		checkmate.setPosition(p.y*100, p.x*100);
				}
				if(type==host && b->getMove()==black){
					string s=n->receive();
					cout<<s<<endl;
					if(s[4]=='?'){
						PieceType temp;
						if(s[5]=='q'){
							temp=queen;
						}
						else if(s[5]=='r'){
							temp=rook;
						}
						else if(s[5]=='b'){
							temp=bishop;
						}
						else if(s[5]=='k'){
							temp=knight;
						}
						b->movePiece({s[0]-'0',s[1]-'0'},{s[2]-'0', s[3]-'0'});
						b->promotePawn({s[2]-'0',s[3]-'0'}, temp);	
					}
					else{
						b->movePiece({s[0]-'0',s[1]-'0'},{s[2]-'0', s[3]-'0'});
					}
				}
				else if(type==client && b->getMove()==white){
					string s=n->receive();
					cout<<s<<endl;
					if(s[4]=='?'){
						PieceType temp;
						if(s[5]=='q'){
							temp=queen;
						}
						else if(s[5]=='r'){
							temp=rook;
						}
						else if(s[5]=='b'){
							temp=bishop;
						}
						else if(s[5]=='k'){
							temp=knight;
						}
						b->movePiece({s[0]-'0',s[1]-'0'},{s[2]-'0', s[3]-'0'});
						b->promotePawn({s[2]-'0',s[3]-'0'}, temp);	
					}
					else{
						b->movePiece({s[0]-'0',s[1]-'0'},{s[2]-'0', s[3]-'0'});
					}
				}
			    while(chessWindow.pollEvent(event)){
			    	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
			    		promote=queen;
					}
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
						promote=bishop;
					}
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
						promote=rook;
					}
					else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
						promote=knight;
					}
			    	if(type==host && b->getMove()==white){
				        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				    		curPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
				            curPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
				    	}
				    	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
							newPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
				            newPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
							b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
							if(newPos.y==7||newPos.y==0){
								b->promotePawn({newPos.y, newPos.x}, promote);
								n->send(7-curPos.y, 7-curPos.x, 7-newPos.y, 7-newPos.x, promote);
							}
							else{
								n->send(7-curPos.y, 7-curPos.x, 7-newPos.y, 7-newPos.x);	
							}
						}
					}
					else if(type==client && b->getMove()==black){
						if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				    		curPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
				            curPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
				    	}
				    	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
							newPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
				            newPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
							b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
							if(newPos.y==7||newPos.y==0){
								b->promotePawn({newPos.y, newPos.x}, promote);
								n->send(7-curPos.y, 7-curPos.x, 7-newPos.y, 7-newPos.x, promote);
							}
							else{
								n->send(7-curPos.y, 7-curPos.x, 7-newPos.y, 7-newPos.x);	
							}
						}
					}
			      if (event.type == sf::Event::Closed)
			            chessWindow.close();
			    }
			    chessWindow.clear();
			    chessWindow.draw(sprite);
			    chessWindow.draw(border);
			    chessWindow.draw(check);
			    chessWindow.draw(checkmate);
			    dat=b->getDetails();
			    available=b->getMoves({curPos.y, curPos.x});
			    for(int k=0;k<available.size();k++){
			    	sf::CircleShape border;
				  	border.setRadius(5);
				  	if(available[k].cell=="NULL"){
				  		border.setFillColor(sf::Color::Green);
				  		border.setOutlineColor(sf::Color::Green);
					}
					else{
						border.setFillColor(sf::Color::Red);
						border.setOutlineColor(sf::Color::Red);
					}
				  	border.setOutlineThickness(5);
				  	border.setPosition(available[k].p.y*100, available[k].p.x*100);
				  	chessWindow.draw(border);
				}
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
					}
				}
			    chessWindow.display();
			  }
		}
		GUI(){
			  n=NULL;
			  b=new Board(white);
			  promote=queen;
			  Point curPos;
			  curPos.x=-1;
			  curPos.y=-1;
			  Point newPos;
			  sf::RenderWindow chessWindow(sf::VideoMode(800, 800), "Chess");
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
			  
			  while(chessWindow.isOpen()){
			  	border.setPosition(curPos.x*100, curPos.y*100);
				if(!b->isCheck()){
					chessWindow.setTitle("Chess - Check");
			  		Point p = b->getKing();
			  		check.setPosition(p.y*100, p.x*100);
				}
				else{
					if(b->getMove()==1){
						chessWindow.setTitle("Chess - White Moves");	
					}
					else{
						chessWindow.setTitle("Chess - Black Moves");
					}
					check.setPosition(-10000, -10000);
				}
				if(b->isCheckMate()){
			  		chessWindow.setTitle("Chess - Checkmate");
			  		Point p = b->getKing();
			  		checkmate.setPosition(p.y*100, p.x*100);
				}
				if(b->isStaleMate()){
					chessWindow.setTitle("Chess - Stalemate");	//stalemate visuals not created
				}
			    while(chessWindow.pollEvent(event)){
			        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			    		curPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
			            curPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
			    	}
			    	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
						newPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
			            newPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
			            if(newPos.y==0||newPos.y==7){
			            	b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
			            	b->promotePawn({newPos.y, newPos.x}, promote);
						}
						else{
							b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
						}
					}
			      if (event.type == sf::Event::Closed)
			            chessWindow.close();
			    }
			    chessWindow.clear();
			    chessWindow.draw(sprite);
			    chessWindow.draw(border);
			    chessWindow.draw(check);
			    chessWindow.draw(checkmate);
			    dat=b->getDetails();
			    available=b->getMoves({curPos.y, curPos.x});
			    for(int k=0;k<available.size();k++){
			    	sf::CircleShape border;
				  	border.setRadius(5);
				  	if(available[k].cell=="NULL"){
				  		border.setFillColor(sf::Color::Green);
				  		border.setOutlineColor(sf::Color::Green);
					}
					else{
						border.setFillColor(sf::Color::Red);
						border.setOutlineColor(sf::Color::Red);
					}
				  	border.setOutlineThickness(5);
				  	border.setPosition(available[k].p.y*100, available[k].p.x*100);
				  	chessWindow.draw(border);
				}
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
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
			    		chessWindow.draw(s);
					}
				}
			    chessWindow.display();
			  }
		}
		~GUI(){
			if(n){
				delete n;
			}
			delete b;
		}
};

int main(){
	sf::IpAddress address(sf::IpAddress::getLocalAddress());
	ostringstream s;
	s<<address;
	string ip = s.str();
	sf::RenderWindow menuWindow(sf::VideoMode(1000, 800), "Select Mode - "+ip);
	sf::Image bg;
	bg.loadFromFile("bg.jpg");
	sf::Texture texture;
    texture.loadFromImage(bg);
    sf::Sprite sprite;
    sprite.setTexture(texture);
	
	sf::Image picture;
	picture.loadFromFile("mikezulu.png");
	sf::Texture mike;
    mike.loadFromImage(picture);
    sf::Sprite github;
    github.setTexture(mike);
    github.setPosition(430, 450);
	
	char choice='o';
	string textbox="";
	
    sf::Font font;
    font.loadFromFile("arial.ttf");
    
    sf::Text name;
    name.setFont(font); 
    name.setString("Developed by: Muhammad Zain Ul Abiddin\nhttps://github.com/M1keZulu");
    name.setCharacterSize(30);
    name.setFillColor(sf::Color::White);
    name.setStyle(sf::Text::Bold);
    name.setPosition(380, 650);
    
	sf::Text play_offline;
    play_offline.setFont(font); 
    play_offline.setString("Play Offline");
    play_offline.setCharacterSize(50);
    play_offline.setFillColor(sf::Color::Black);
    play_offline.setPosition(430,100);
    
    sf::Text play_host;
    play_host.setFont(font); 
    play_host.setString("Host Game");
    play_host.setCharacterSize(50);
    play_host.setFillColor(sf::Color::Black);
    play_host.setPosition(430,200);
    
    sf::Text play_client;
    play_client.setFont(font); 
    play_client.setString("Connect");
    play_client.setCharacterSize(50);
    play_client.setFillColor(sf::Color::Black);
    play_client.setPosition(430,300);
    
    sf::Text enter_ip;
    enter_ip.setFont(font); 
    enter_ip.setString("Enter IP: "+textbox);
    enter_ip.setCharacterSize(30);
    enter_ip.setFillColor(sf::Color::Yellow);
    enter_ip.setPosition(430,355);
    
    while (menuWindow.isOpen()){
        sf::Event event;
        if(choice=='o'){
        	play_offline.setFillColor(sf::Color::Red);
        	play_host.setFillColor(sf::Color::Black);
        	play_client.setFillColor(sf::Color::Black);
		}
		else if(choice=='h'){
			play_offline.setFillColor(sf::Color::Black);
        	play_host.setFillColor(sf::Color::Red);
        	play_client.setFillColor(sf::Color::Black);
		}
		else if(choice=='c'){
			play_offline.setFillColor(sf::Color::Black);
        	play_host.setFillColor(sf::Color::Black);
        	play_client.setFillColor(sf::Color::Red);
		}
		
        while(menuWindow.pollEvent(event)){
        	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				if(choice=='h'){
					choice='o';
				}
				else if(choice=='c'){
					choice='h';
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				if(choice=='o'){
					choice='h';
				}
				else if(choice=='h'){
					choice='c';
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
				if(choice=='o'){
					GUI g;
				}
				else if(choice=='h'){
					menuWindow.setTitle("Hosting at "+ip+":2000");
					GUI g(host, "");
				}
				else if(choice=='c'){
					menuWindow.setTitle("Connecting to "+textbox+":2000");
					GUI g(client, textbox);
				}
			}
			if(event.type == sf::Event::TextEntered){
				if((event.text.unicode>= 47 && event.text.unicode<=57)|| event.text.unicode==46){
				    textbox+=static_cast<char>(event.text.unicode);
				    enter_ip.setString("Enter IP: "+textbox);
				}
				if(event.text.unicode==8){
					textbox = textbox.substr(0, textbox.size()-1);
					enter_ip.setString("Enter IP: "+textbox);
				}
			}
            if(event.type == sf::Event::Closed)
                menuWindow.close();
        }
        menuWindow.clear();
       	menuWindow.draw(sprite);
       	menuWindow.draw(play_offline);
       	menuWindow.draw(play_host);
       	menuWindow.draw(play_client);
       	menuWindow.draw(enter_ip);
       	menuWindow.draw(github);
       	menuWindow.draw(name);
        menuWindow.display();
    }
    return 0;
}
