#ifndef BOARD_H
#define BOARD_H

class Board{
	private:
		Cell cells[GRID][GRID];
		Color move;
		void newMove();
		void changeMove();
		bool dummyMove(Point currentPos, Point newPos);
		sf::Music move_sound;
	public:
		Board(Color c);
		void movePiece(Point currentPos, Point newPos);
		void displayBoard();
		vector<Detail> getDetails();
		bool isCheckMate();
		Point getKing();
		bool isCheck();
		Color getMove();
		void promotePawn(Point currentPos, PieceType name);
		bool isStaleMate();
		vector<Moves> getMoves(Point curPos);
		~Board();
};

#endif
