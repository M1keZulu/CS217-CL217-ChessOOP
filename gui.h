#ifndef GUI_H
#define GUI_H

class Gui{
	private:
		Board *b;
		Network *n;
		vector<Detail> dat;
		PieceType promote;
		vector<Moves> available;
	public:
		Gui();
		Gui(const ConnectionType type, string ip);
		~Gui();
};

#endif

