#ifndef ROOKH
#define ROOK_H

class Rook:public Piece{
	public:
		Rook(Color m_color);
		void generateMoves(Point currentPos);
};

#endif

