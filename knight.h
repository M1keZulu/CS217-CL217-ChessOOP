#ifndef KNIGHT_H
#define KNIGHT_H

class Knight:public Piece{
	public:
		Knight(Color m_color);
		void generateMoves(Point currentPos);
};

#endif

