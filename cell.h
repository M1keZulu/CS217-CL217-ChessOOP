#ifndef CELL_H
#define CELL_H

class Piece;

class Cell{
	protected:
		Piece *piece;
	public:
		Cell();
		void setNull();
		void setPiece(Piece *m_piece);
		Piece* getPiece();
};

#endif
