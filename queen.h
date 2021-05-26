#ifndef QUEEN_H
#define QUEEN_H

class Queen:public Piece{
	public:
		Queen(Color m_color);
		void generateMoves(Point currentPos);
};

#endif

