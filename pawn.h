#ifndef PAWN_H
#define PAWN_H

class Pawn:public Piece{
	Direction d;
	public:
		Pawn(Color m_color, Direction d);
		void generateMoves(Point currentPos);
		Direction getPawnDirection();
		bool enPassant(Piece *ptr);
		void AddenPassant(Piece *ptr);
};

#endif
