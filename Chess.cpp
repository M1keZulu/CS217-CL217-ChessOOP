#include<iostream>
#include<vector>
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
//DataTypes

//Forward Decleration for Circular Dependency
class Cell;
class Piece;
class Board;

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
		int inLimits(Point checkPos);
		virtual void generateMoves(Point currentPos);
		virtual int isMoveLegal(Point newPos);
		
};

vector<Piece*> Piece::pieces;
Cell* Piece::cell;
Piece::Piece(Color m_color, PieceType m_name):color(m_color),name(m_name){pieces.push_back(this);moveCount=0;} //Piece Constructor
void Piece::setCellArray(Cell *m_cell){cell = m_cell;}
Color Piece::getColor(){return color;}
PieceType Piece::getName(){return name;}
void Piece::PieceMoved(){moveCount++;}
void Piece::generateMoves(Point currentPos){}
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
//Class Piece

//Class Pawn
class Pawn:public Piece{
	public:
		Pawn(Color m_color);
		void generateMoves(Point currentPos);
};

Pawn::Pawn(Color m_color):Piece(m_color, pawn){}
void Pawn::generateMoves(Point currentPos){
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
				movesAvailable.push_back({currentPos.x-1, currentPos.y});
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
	if(inLimits({currentPos.x-2, currentPos.y-1})){		//(x-2,y-1)
		if((cell+((currentPos.x-2)*GRID)+(currentPos.y-1))->getPiece()==NULL || (cell+((currentPos.x-2)*GRID)+(currentPos.y-1))->getPiece()->getColor()!=color){
			movesAvailable.push_back({currentPos.x-2, currentPos.y-1});
		}
	}
}
//Class Knight

//Class Board
class Board{
	private:
		Cell cells[GRID][GRID];
	public:
		Board();
		void movePiece(Point currentPos, Point newPos);
		void displayBoard();
};

Board::Board(){ 
	Piece *ptr;
	
	ptr=new Knight(white);
	cells[6][1].setPiece(ptr);
	
	Piece::setCellArray(&cells[0][0]);
	cells[6][1].getPiece()->generateMoves({6,1});
}
void Board::movePiece(Point currentPos, Point newPos){
		cout<<cells[currentPos.x][currentPos.y].getPiece()->movesAvailable.size()<<endl; //only for debugging
		if(cells[currentPos.x][currentPos.y].getPiece()->isMoveLegal(newPos)){
			cells[newPos.x][newPos.y].setPiece(cells[currentPos.x][currentPos.y].getPiece());
			cells[currentPos.x][currentPos.y].setNull();
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
//Class Board

int main(){
	Board b;
	b.displayBoard();
	b.movePiece({6,1}, {4,0});
	cout<<endl;
	b.displayBoard();
}
