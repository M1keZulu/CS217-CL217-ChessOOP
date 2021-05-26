#include<iostream>
#include<sstream>
#include<SFML/Network.hpp>
#include "enums_data.h"
#include "network.h"

using namespace std;

Network::Network(string s){
			ip=sf::IpAddress(s);
			sf::Socket::Status status = socket.connect(ip, 2000);
				if(status!=sf::Socket::Done){
				    cout<<"Failure";
				    exit(0);
				}
				else{
					cout<<"Connected";
				}
			socket.setBlocking(false);
}
Network::Network(){
			sf::TcpListener listener;
			listener.listen(2000);
			listener.accept(socket);
			socket.setBlocking(false);
}
void Network::send(int a, int b, int c, int d){
	ostringstream s;
	s.str("");
	s<<a<<b<<c<<d;
	string temp;
	temp += s.str();
	socket.send(temp.c_str(), temp.length() + 1);
}
void Network::send(int a, int b, int c, int d, PieceType promotion){
	ostringstream s;
	s.str("");
	s<<a<<b<<c<<d;
	string temp;
	temp += s.str();
	temp+="?";
	if(promotion==queen){
		temp+="q";
	}
	else if(promotion==rook){
		temp+="r";
	}
	else if(promotion==bishop){
		temp+="b";
	}
	else if(promotion==knight){
		temp+="k";
	}
	socket.send(temp.c_str(), temp.length() + 1);
//			cout<<"@Data Sent - "<<temp<<" @"<<endl;
}
string Network::receive(){
	char buffer[20000];
	if(socket.receive(buffer, sizeof(buffer), received)==sf::Socket::Done){
		socket.receive(buffer, sizeof(buffer), received);
//				cout<<"@Data Received - "<<buffer<<" @"<<endl;
		return buffer;
	}
	else{
//				cout<<"@Data Received - "<<buffer<<" @"<<endl;
		return "";
	}
}
