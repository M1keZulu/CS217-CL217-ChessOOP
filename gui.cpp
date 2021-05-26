#include<iostream>
#include<vector>
#define GRID 8
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "enums_data.h"
#include "cell.h"
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "board.h"
#include "network.h"
#include "gui.h"

using namespace std;

Gui::Gui(const ConnectionType type, string ip){
	if(type==host){
	n=new Network;
	b=new Board(white);
	}
	else if(type==client){
	n=new Network(ip);
	b=new Board(black);
	}
	Point curPos;
	promote=queen;
	curPos.x=-1;
	curPos.y=-1;
	Point newPos;
	sf::RenderWindow chessWindow(sf::VideoMode(800, 800), "Chess");
	sf::Event event;
	sf::Image image;
	image.loadFromFile("src/board1.png");
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite(texture);
	
	sf::RectangleShape border;
	border.setSize(sf::Vector2f(100,100));
	border.setOutlineColor(sf::Color::Blue);
	border.setOutlineThickness(5);
	border.setFillColor(sf::Color::Transparent);
	
	sf::RectangleShape checkmate;
	checkmate.setSize(sf::Vector2f(100,100));
	checkmate.setOutlineColor(sf::Color::Red);
	checkmate.setFillColor(sf::Color::Red);
	checkmate.setPosition(-10000,-10000);
	
	sf::RectangleShape check;
	check.setSize(sf::Vector2f(100,100));
	check.setOutlineColor(sf::Color::Yellow);
	check.setFillColor(sf::Color::Yellow);
	check.setPosition(-10000,-10000);
	
	while(chessWindow.isOpen()){
	border.setPosition(curPos.x*100, curPos.y*100);
	if(!b->isCheck()){
		chessWindow.setTitle("Chess - Check");
		Point p = b->getKing();
		check.setPosition(p.y*100, p.x*100);
	}
	else{
		if(b->getMove()==1){
			chessWindow.setTitle("Chess - White Moves");	
		}
		else{
			chessWindow.setTitle("Chess - Black Moves");
		}
		check.setPosition(-10000, -10000);
	}
	if(b->isCheckMate()){
		chessWindow.setTitle("Chess - Checkmate");
		Point p = b->getKing();
		checkmate.setPosition(p.y*100, p.x*100);
	}
	if(type==host && b->getMove()==black){
		string s=n->receive();
		cout<<s<<endl;
		if(s[4]=='?'){
			PieceType temp;
			if(s[5]=='q'){
				temp=queen;
			}
			else if(s[5]=='r'){
				temp=rook;
			}
			else if(s[5]=='b'){
				temp=bishop;
			}
			else if(s[5]=='k'){
				temp=knight;
			}
			b->movePiece({s[0]-'0',s[1]-'0'},{s[2]-'0', s[3]-'0'});
			b->promotePawn({s[2]-'0',s[3]-'0'}, temp);	
		}
		else{
			b->movePiece({s[0]-'0',s[1]-'0'},{s[2]-'0', s[3]-'0'});
		}
	}
	else if(type==client && b->getMove()==white){
		string s=n->receive();
		cout<<s<<endl;
		if(s[4]=='?'){
			PieceType temp;
			if(s[5]=='q'){
				temp=queen;
			}
			else if(s[5]=='r'){
				temp=rook;
			}
			else if(s[5]=='b'){
				temp=bishop;
			}
			else if(s[5]=='k'){
				temp=knight;
			}
			b->movePiece({s[0]-'0',s[1]-'0'},{s[2]-'0', s[3]-'0'});
			b->promotePawn({s[2]-'0',s[3]-'0'}, temp);	
		}
		else{
			b->movePiece({s[0]-'0',s[1]-'0'},{s[2]-'0', s[3]-'0'});
		}
	}
	while(chessWindow.pollEvent(event)){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
			promote=queen;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
			promote=bishop;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
			promote=rook;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
			promote=knight;
		}
		if(type==host && b->getMove()==white){
	        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
	    		curPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
	            curPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
	    	}
	    	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				newPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
	            newPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
				b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
				if(newPos.y==7||newPos.y==0){
					b->promotePawn({newPos.y, newPos.x}, promote);
					n->send(7-curPos.y, 7-curPos.x, 7-newPos.y, 7-newPos.x, promote);
				}
				else{
					n->send(7-curPos.y, 7-curPos.x, 7-newPos.y, 7-newPos.x);	
				}
			}
		}
		else if(type==client && b->getMove()==black){
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
	    		curPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
	            curPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
	    	}
	    	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				newPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
	            newPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
				b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
				if(newPos.y==7||newPos.y==0){
					b->promotePawn({newPos.y, newPos.x}, promote);
					n->send(7-curPos.y, 7-curPos.x, 7-newPos.y, 7-newPos.x, promote);
				}
				else{
					n->send(7-curPos.y, 7-curPos.x, 7-newPos.y, 7-newPos.x);	
				}
			}
		}
	  if (event.type == sf::Event::Closed)
	        chessWindow.close();
	}
	chessWindow.clear();
	chessWindow.draw(sprite);
	chessWindow.draw(border);
	chessWindow.draw(check);
	chessWindow.draw(checkmate);
	dat=b->getDetails();
	available=b->getMoves({curPos.y, curPos.x});
	for(int k=0;k<available.size();k++){
		sf::CircleShape border;
	  	border.setRadius(5);
	  	if(available[k].cell=="NULL"){
	  		border.setFillColor(sf::Color::Green);
	  		border.setOutlineColor(sf::Color::Green);
		}
		else{
			border.setFillColor(sf::Color::Red);
			border.setOutlineColor(sf::Color::Red);
		}
	  	border.setOutlineThickness(5);
	  	border.setPosition(available[k].p.y*100, available[k].p.x*100);
	  	chessWindow.draw(border);
	}
	for(int i=0;i<dat.size();i++){
		if(dat[i].name==pawn&&dat[i].color==white){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/w_pawn.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(13+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==pawn&&dat[i].color==black){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/b_pawn.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(13+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==knight&&dat[i].color==white){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/w_knight.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(13+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==knight&&dat[i].color==black){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/b_knight.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(13+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==rook&&dat[i].color==white){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/w_rook.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(13+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==rook&&dat[i].color==black){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/b_rook.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(13+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==bishop&&dat[i].color==white){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/w_bishop.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(13+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==bishop&&dat[i].color==black){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/b_bishop.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(13+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==queen&&dat[i].color==white){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/w_queen.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(2+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==queen&&dat[i].color==black){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/b_queen.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(2+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==king&&dat[i].color==white){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/w_king.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(8+y*100,5+x*100);
			chessWindow.draw(s);
		}
		else if(dat[i].name==king&&dat[i].color==black){
			int x =dat[i].x;
			int y =dat[i].y;
			sf::Image i;
			i.loadFromFile("src/b_king.png");
			sf::Texture t;
			t.loadFromImage(i);
			sf::Sprite s;
			s.setTexture(t);
			s.setScale(0.7,0.7);
			s.setPosition(8+y*100,5+x*100);
			chessWindow.draw(s);
		}
	}
	chessWindow.display();
	}
}
Gui::Gui(){
  n=NULL;
  b=new Board(white);
  promote=queen;
  Point curPos;
  curPos.x=-1;
  curPos.y=-1;
  Point newPos;
  sf::RenderWindow chessWindow(sf::VideoMode(800, 800), "Chess");
  sf::Event event;
  sf::Image image;
  image.loadFromFile("src/board1.png");
  sf::Texture texture;
  texture.loadFromImage(image);
  sf::Sprite sprite(texture);
  sf::RectangleShape border;
  border.setSize(sf::Vector2f(100,100));
  border.setOutlineColor(sf::Color::Blue);
  border.setOutlineThickness(5);
  border.setFillColor(sf::Color::Transparent);
  
  sf::RectangleShape checkmate;
  checkmate.setSize(sf::Vector2f(100,100));
  checkmate.setOutlineColor(sf::Color::Red);
  checkmate.setFillColor(sf::Color::Red);
  checkmate.setPosition(-10000,-10000);
  
  sf::RectangleShape check;
  check.setSize(sf::Vector2f(100,100));
  check.setOutlineColor(sf::Color::Yellow);
  check.setFillColor(sf::Color::Yellow);
  check.setPosition(-10000,-10000);
  
  while(chessWindow.isOpen()){
  	border.setPosition(curPos.x*100, curPos.y*100);
	if(!b->isCheck()){
		chessWindow.setTitle("Chess - Check");
  		Point p = b->getKing();
  		check.setPosition(p.y*100, p.x*100);
	}
	else{
		if(b->getMove()==1){
			chessWindow.setTitle("Chess - White Moves");	
		}
		else{
			chessWindow.setTitle("Chess - Black Moves");
		}
		check.setPosition(-10000, -10000);
	}
	if(b->isCheckMate()){
  		chessWindow.setTitle("Chess - Checkmate");
  		Point p = b->getKing();
  		checkmate.setPosition(p.y*100, p.x*100);
	}
	if(b->isStaleMate()){
		chessWindow.setTitle("Chess - Stalemate");	//stalemate visuals not created
	}
    while(chessWindow.pollEvent(event)){
    	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
			promote=queen;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
			promote=bishop;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
			promote=rook;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
			promote=knight;
		}
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
    		curPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
            curPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
    	}
    	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			newPos.x = sf::Mouse::getPosition(chessWindow).x/(chessWindow.getSize().x/8);
            newPos.y = sf::Mouse::getPosition(chessWindow).y/(chessWindow.getSize().y/8);
            if(newPos.y==0||newPos.y==7){
            	b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
            	b->promotePawn({newPos.y, newPos.x}, promote);
			}
			else{
				b->movePiece({curPos.y,curPos.x},{newPos.y, newPos.x});
			}
		}
      if (event.type == sf::Event::Closed)
            chessWindow.close();
    }
    chessWindow.clear();
    chessWindow.draw(sprite);
    chessWindow.draw(border);
    chessWindow.draw(check);
    chessWindow.draw(checkmate);
    dat=b->getDetails();
    available=b->getMoves({curPos.y, curPos.x});
    for(int k=0;k<available.size();k++){
    	sf::CircleShape border;
	  	border.setRadius(5);
	  	if(available[k].cell=="NULL"){
	  		border.setFillColor(sf::Color::Green);
	  		border.setOutlineColor(sf::Color::Green);
		}
		else{
			border.setFillColor(sf::Color::Red);
			border.setOutlineColor(sf::Color::Red);
		}
	  	border.setOutlineThickness(5);
	  	border.setPosition(available[k].p.y*100, available[k].p.x*100);
	  	chessWindow.draw(border);
	}
    for(int i=0;i<dat.size();i++){
    	if(dat[i].name==pawn&&dat[i].color==white){
    		int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/w_pawn.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(13+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==pawn&&dat[i].color==black){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/b_pawn.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(13+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==knight&&dat[i].color==white){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/w_knight.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(13+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==knight&&dat[i].color==black){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/b_knight.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(13+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==rook&&dat[i].color==white){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/w_rook.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(13+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==rook&&dat[i].color==black){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/b_rook.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(13+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==bishop&&dat[i].color==white){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/w_bishop.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(13+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==bishop&&dat[i].color==black){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/b_bishop.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(13+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==queen&&dat[i].color==white){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/w_queen.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(2+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==queen&&dat[i].color==black){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/b_queen.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(2+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==king&&dat[i].color==white){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/w_king.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(8+y*100,5+x*100);
    		chessWindow.draw(s);
		}
		else if(dat[i].name==king&&dat[i].color==black){
			int x =dat[i].x;
    		int y =dat[i].y;
    		sf::Image i;
    		i.loadFromFile("src/b_king.png");
    		sf::Texture t;
    		t.loadFromImage(i);
    		sf::Sprite s;
    		s.setTexture(t);
    		s.setScale(0.7,0.7);
    		s.setPosition(8+y*100,5+x*100);
    		chessWindow.draw(s);
		}
	}
    chessWindow.display();
  }
}
Gui::~Gui(){
	if(n){
		delete n;
	}
	delete b;
}
