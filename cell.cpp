#include<iostream>
#include "cell.h"

using namespace std;

Cell::Cell(){piece=NULL;}
void Cell::setNull(){piece=NULL;}
void Cell::setPiece(Piece *m_piece){piece=m_piece;}
Piece* Cell::getPiece(){return piece;}
