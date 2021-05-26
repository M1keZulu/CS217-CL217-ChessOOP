#ifndef NETWORK_H
#define NETWORK_H

class Network{
	private:
		sf::IpAddress ip;
		sf::TcpSocket socket;
		char connectionType, mode;
		int x;
		size_t received;
		string text;
	public:
		Network(string s);
		Network();
	public:
		void send(int a, int b, int c, int d);
		void send(int a, int b, int c, int d, PieceType promotion);
		string receive();
};

#endif
