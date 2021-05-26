#ifndef KING_H
#define KING_H

class King:public Piece{
	public:
		King(Color m_color);
		void generateMoves(Point currentPos);
};


#endif

