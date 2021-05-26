#ifndef BISHOP_H
#define BISHOP_H

class Bishop:public Piece{
	public:
		Bishop(Color m_color);
		void generateMoves(Point currentPos);
};

#endif
