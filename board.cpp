#include<iostream>
#include<vector>
#define GRID 8
#include "enums_data.h"
#include "cell.h"
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include <SFML/Audio.hpp>
#include "board.h"

using namespace std;

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
			if(cells[curPos.x][curPos.y].getPiece()->getName()==king && cells[curPos.x][curPos.y].getPiece()->getCount()==0 && cells[curPos.x][curPos.y].getPiece()->getColor()==move){
				if(cells[curPos.x][curPos.y+3].getPiece()!=NULL){
					if(cells[curPos.x][curPos.y+3].getPiece()->getName()==rook && cells[curPos.x][curPos.y+3].getPiece()->getCount()==0){
						if(cells[curPos.x][curPos.y+1].getPiece()==NULL && cells[curPos.x][curPos.y+2].getPiece()==NULL){
							if(isCheck() && cells[curPos.x][curPos.y].getPiece()->isUnderAttack({curPos.x, curPos.y+1}) && cells[curPos.x][curPos.y].getPiece()->isUnderAttack({curPos.x, curPos.y+2})){
								ret.push_back({{curPos.x, curPos.y+2}, "special"});
							}
						}
					}
				}
				else if(cells[curPos.x][curPos.y-3].getPiece()!=NULL){
					if(cells[curPos.x][curPos.y-3].getPiece()->getName()==rook && cells[curPos.x][curPos.y-3].getPiece()->getCount()==0){
						if(cells[curPos.x][curPos.y-1].getPiece()==NULL && cells[curPos.x][curPos.y-2].getPiece()==NULL){
							if(isCheck() && cells[curPos.x][curPos.y].getPiece()->isUnderAttack({curPos.x, curPos.y-1}) && cells[curPos.x][curPos.y].getPiece()->isUnderAttack({curPos.x, curPos.y-2})){
								ret.push_back({{curPos.x, curPos.y-2}, "special"});
							}
						}
					}
				}
			}
			if(cells[curPos.x][curPos.y].getPiece()->getName()==king && cells[curPos.x][curPos.y].getPiece()->getCount()==0 && cells[curPos.x][curPos.y].getPiece()->getColor()==move){
				if(cells[curPos.x][curPos.y-4].getPiece()!=NULL){
					if(cells[curPos.x][curPos.y-4].getPiece()->getName()==rook && cells[curPos.x][curPos.y-4].getPiece()->getCount()==0){
						if(cells[curPos.x][curPos.y-1].getPiece()==NULL && cells[curPos.x][curPos.y-2].getPiece()==NULL){
							if(isCheck() && cells[curPos.x][curPos.y].getPiece()->isUnderAttack({curPos.x, curPos.y-1}) && cells[curPos.x][curPos.y].getPiece()->isUnderAttack({curPos.x, curPos.y-2})){
								ret.push_back({{curPos.x, curPos.y-2}, "special"});
							}
						}
					}
				}
				else if(cells[curPos.x][curPos.y+4].getPiece()!=NULL){
					if(cells[curPos.x][curPos.y+4].getPiece()->getName()==rook && cells[curPos.x][curPos.y+4].getPiece()->getCount()==0){
						if(cells[curPos.x][curPos.y+1].getPiece()==NULL && cells[curPos.x][curPos.y+2].getPiece()==NULL){
							if(isCheck() && cells[curPos.x][curPos.y].getPiece()->isUnderAttack({curPos.x, curPos.y+1}) && cells[curPos.x][curPos.y].getPiece()->isUnderAttack({curPos.x, curPos.y+2})){
								ret.push_back({{curPos.x, curPos.y+2}, "special"});
							}
						}
					}
				}
			}
			if(cells[curPos.x][curPos.y].getPiece()->getName()==pawn && cells[curPos.x][curPos.y].getPiece()->getColor()==move){
				if(cells[curPos.x][curPos.y].getPiece()->getPawnDirection()==up){
					if(cells[curPos.x][curPos.y+1].getPiece()!=NULL){
						if(cells[curPos.x][curPos.y+1].getPiece()->getName()==pawn && cells[curPos.x][curPos.y+1].getPiece()->getColor()!=move && curPos.x==3 && cells[curPos.x][curPos.y+1].getPiece()->getCount()==1 && cells[curPos.x][curPos.y+1].getPiece()->enPassant(cells[curPos.x][curPos.y].getPiece())){
							Piece *temp = cells[curPos.x][curPos.y+1].getPiece();
							cells[curPos.x-1][curPos.y+1].setPiece(cells[curPos.x][curPos.y].getPiece());
							cells[curPos.x][curPos.y].setNull();
							cells[curPos.x][curPos.y+1].setNull();
							if(isCheck()){
								ret.push_back({{curPos.x-1, curPos.y+1}, "special"});
							}
							cells[curPos.x][curPos.y].setPiece(cells[curPos.x-1][curPos.y+1].getPiece());
							cells[curPos.x-1][curPos.y+1].setNull();
							cells[curPos.x][curPos.y+1].setPiece(temp);
						}
					}
				    if(cells[curPos.x][curPos.y-1].getPiece()!=NULL){
						if(cells[curPos.x][curPos.y-1].getPiece()->getName()==pawn && cells[curPos.x][curPos.y-1].getPiece()->getColor()!=move && curPos.x==3 && cells[curPos.x][curPos.y-1].getPiece()->getCount()==1 && cells[curPos.x][curPos.y-1].getPiece()->enPassant(cells[curPos.x][curPos.y].getPiece())){
							Piece *temp = cells[curPos.x][curPos.y-1].getPiece();
							cells[curPos.x-1][curPos.y-1].setPiece(cells[curPos.x][curPos.y].getPiece());
							cells[curPos.x][curPos.y].setNull();
							cells[curPos.x][curPos.y-1].setNull();
							if(isCheck()){
								ret.push_back({{curPos.x-1, curPos.y-1}, "special"});
							}
							cells[curPos.x][curPos.y].setPiece(cells[curPos.x-1][curPos.y-1].getPiece());
							cells[curPos.x-1][curPos.y-1].setNull();
							cells[curPos.x][curPos.y-1].setPiece(temp);
						}
					}
				}
				if(cells[curPos.x][curPos.y].getPiece()->getPawnDirection()==down){
					if(cells[curPos.x][curPos.y+1].getPiece()!=NULL){
						if(cells[curPos.x][curPos.y+1].getPiece()->getName()==pawn && cells[curPos.x][curPos.y+1].getPiece()->getColor()!=move && curPos.x==4 && cells[curPos.x][curPos.y+1].getPiece()->getCount()==1 && cells[curPos.x][curPos.y+1].getPiece()->enPassant(cells[curPos.x][curPos.y].getPiece())){
							Piece *temp = cells[curPos.x][curPos.y+1].getPiece();
							cells[curPos.x+1][curPos.y+1].setPiece(cells[curPos.x][curPos.y].getPiece());
							cells[curPos.x][curPos.y].setNull();
							cells[curPos.x][curPos.y+1].setNull();
							if(isCheck()){
								ret.push_back({{curPos.x+1, curPos.y+1}, "special"});
							}
							cells[curPos.x][curPos.y].setPiece(cells[curPos.x+1][curPos.y+1].getPiece());
							cells[curPos.x+1][curPos.y+1].setNull();
							cells[curPos.x][curPos.y+1].setPiece(temp);
						}
					}
					if(cells[curPos.x][curPos.y-1].getPiece()!=NULL){
						if(cells[curPos.x][curPos.y-1].getPiece()->getName()==pawn && cells[curPos.x][curPos.y-1].getPiece()->getColor()!=move && curPos.x==4 && cells[curPos.x][curPos.y-1].getPiece()->getCount()==1 && cells[curPos.x][curPos.y-1].getPiece()->enPassant(cells[curPos.x][curPos.y].getPiece())){
							Piece *temp = cells[curPos.x][curPos.y-1].getPiece();
							cells[curPos.x+1][curPos.y-1].setPiece(cells[curPos.x][curPos.y].getPiece());
							cells[curPos.x][curPos.y].setNull();
							cells[curPos.x][curPos.y-1].setNull();
							if(isCheck()){
								ret.push_back({{curPos.x+1, curPos.y-1}, "special"});
							}
							cells[curPos.x][curPos.y].setPiece(cells[curPos.x+1][curPos.y-1].getPiece());
							cells[curPos.x+1][curPos.y-1].setNull();
							cells[curPos.x][curPos.y-1].setPiece(temp);
						}
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
	move_sound.openFromFile("src/move_sound.wav");
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
