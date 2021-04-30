#include<iostream>
#include<vector>
#include<fstream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
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
		int inLimits(Point checkPos); //this function is useless as of latest build
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
	ofstream log;
	log.open("dem.txt");
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
	log.close();
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
		vector<Detail> getDetails();
};

Board::Board(){ 
	Piece *ptr;
	
	ptr=new Pawn(black);
	cells[4][1].setPiece(ptr);
	ptr=new Knight(white);
	cells[4][4].setPiece(ptr);
	
	Piece::setCellArray(&cells[0][0]);
	cells[4][4].getPiece()->generateMoves({4,4});
}
void Board::movePiece(Point currentPos, Point newPos){
		if(currentPos.x>=0&&currentPos.x<8&&currentPos.y>=0&&currentPos.y<8){
			if(cells[currentPos.x][currentPos.y].getPiece()!=NULL){
				if(cells[currentPos.x][currentPos.y].getPiece()->isMoveLegal(newPos)){
					cells[newPos.x][newPos.y].setPiece(cells[currentPos.x][currentPos.y].getPiece());
					cells[currentPos.x][currentPos.y].setNull();
				}
			}
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
//Class Board

class GUI{
	private:
		Board b;
		vector<Detail> dat;
	public:
		GUI(){
			  Point curPos;
			  Point newPos;
			  sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Game Testing");
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
			  while (renderWindow.isOpen()){
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
				}
			    renderWindow.display();
			  }
		}
};

int main(){
	GUI g;
}
