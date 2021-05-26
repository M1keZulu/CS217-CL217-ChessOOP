#ifndef PIECE_H
#define PIECE_H

class Piece{
	protected:
		const PieceType name;
		static Cell	*cell;
		const Color color;
		static vector<Piece*> pieces;
		int moveCount;
		vector<Point> movesAvailable;
		vector<Piece*> pawnLocation;
	public:
		Piece(Color m_color, PieceType name);
		static void setCellArray(Cell *m_cell);
		static vector<Piece*> getPieces();
		static void clearPieces();
		virtual Color getColor();
		virtual PieceType getName();
		virtual void PieceMoved();
		virtual vector<Point> getAvailableMoves();
		int inLimits(Point checkPos);
		virtual void generateMoves(Point currentPos);
		virtual int isMoveLegal(Point newPos);
		virtual bool isUnderAttack(Point currentPos);
		virtual void addMove(Point pos);
		virtual int numberMoves();
		virtual int getCount();
		virtual Direction getPawnDirection();
		virtual bool enPassant(Piece *ptr);
		virtual void AddenPassant(Piece *ptr);
		vector<Point> getPossibleMoves();
};

#endif
