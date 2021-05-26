/*
	Name: Chess-OOP
	Author:	Muhammad Zain Ul Abiddin
	Description: Chess game made using OOP principles for Semester Project
	Date: 24/05/2021
*/

//Forward Decleration for Circular Dependency
class Cell;
class Piece;
class Board;
class GUI;

#include<iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include<time.h>
#include<string>
#include<string.h>
#include<sstream>
#define GRID 8
#include "enums_data.h"
#include "cell.h"
#include "board.h"
#include "network.h"
#include "gui.h"

using namespace std;

int main(){
	sf::IpAddress address(sf::IpAddress::getLocalAddress());
	ostringstream s;
	s<<address;
	string ip = s.str();
	sf::RenderWindow menuWindow(sf::VideoMode(1000, 800), "Select Mode - "+ip);
	sf::Image bg;
	bg.loadFromFile("src/bg.jpg");
	sf::Texture texture;
    texture.loadFromImage(bg);
    sf::Sprite sprite;
    sprite.setTexture(texture);
	
	sf::Image picture;
	picture.loadFromFile("src/mikezulu.png");
	sf::Texture mike;
    mike.loadFromImage(picture);
    sf::Sprite github;
    github.setTexture(mike);
    github.setPosition(430, 450);
	
	char choice='o';
	string textbox="";
	
    sf::Font font;
    font.loadFromFile("src/arial.ttf");
    
    sf::Text name;
    name.setFont(font); 
    name.setString("Developed by: Muhammad Zain Ul Abiddin\nhttps://github.com/M1keZulu");
    name.setCharacterSize(30);
    name.setFillColor(sf::Color::White);
    name.setStyle(sf::Text::Bold);
    name.setPosition(380, 650);
    
	sf::Text play_offline;
    play_offline.setFont(font); 
    play_offline.setString("Play Offline");
    play_offline.setCharacterSize(50);
    play_offline.setFillColor(sf::Color::Black);
    play_offline.setPosition(430,100);
    
    sf::Text play_host;
    play_host.setFont(font); 
    play_host.setString("Host Game");
    play_host.setCharacterSize(50);
    play_host.setFillColor(sf::Color::Black);
    play_host.setPosition(430,200);
    
    sf::Text play_client;
    play_client.setFont(font); 
    play_client.setString("Connect");
    play_client.setCharacterSize(50);
    play_client.setFillColor(sf::Color::Black);
    play_client.setPosition(430,300);
    
    sf::Text enter_ip;
    enter_ip.setFont(font); 
    enter_ip.setString("Enter IP: "+textbox);
    enter_ip.setCharacterSize(30);
    enter_ip.setFillColor(sf::Color::Yellow);
    enter_ip.setPosition(430,355);
    
    while (menuWindow.isOpen()){
        sf::Event event;
        if(choice=='o'){
        	play_offline.setFillColor(sf::Color::Red);
        	play_host.setFillColor(sf::Color::Black);
        	play_client.setFillColor(sf::Color::Black);
		}
		else if(choice=='h'){
			play_offline.setFillColor(sf::Color::Black);
        	play_host.setFillColor(sf::Color::Red);
        	play_client.setFillColor(sf::Color::Black);
		}
		else if(choice=='c'){
			play_offline.setFillColor(sf::Color::Black);
        	play_host.setFillColor(sf::Color::Black);
        	play_client.setFillColor(sf::Color::Red);
		}
		
        while(menuWindow.pollEvent(event)){
        	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				if(choice=='h'){
					choice='o';
				}
				else if(choice=='c'){
					choice='h';
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				if(choice=='o'){
					choice='h';
				}
				else if(choice=='h'){
					choice='c';
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
				if(choice=='o'){
					Gui g;
				}
				else if(choice=='h'){
					menuWindow.setTitle("Hosting at "+ip+":2000");
					Gui g(host, "");
				}
				else if(choice=='c'){
					menuWindow.setTitle("Connecting to "+textbox+":2000");
					Gui g(client, textbox);
				}
			}
			if(event.type == sf::Event::TextEntered){
				if((event.text.unicode>= 47 && event.text.unicode<=57)|| event.text.unicode==46){
				    textbox+=static_cast<char>(event.text.unicode);
				    enter_ip.setString("Enter IP: "+textbox);
				}
				if(event.text.unicode==8){
					textbox = textbox.substr(0, textbox.size()-1);
					enter_ip.setString("Enter IP: "+textbox);
				}
			}
            if(event.type == sf::Event::Closed)
                menuWindow.close();
        }
        menuWindow.clear();
       	menuWindow.draw(sprite);
       	menuWindow.draw(play_offline);
       	menuWindow.draw(play_host);
       	menuWindow.draw(play_client);
       	menuWindow.draw(enter_ip);
       	menuWindow.draw(github);
       	menuWindow.draw(name);
        menuWindow.display();
    }
    return 0;
}
