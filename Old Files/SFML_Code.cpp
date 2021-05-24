#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>

using namespace std;

struct Point{
	int x;
	int y;
};

int main(){
  Point curPos;
  Point newPos;
  ofstream Log("log.txt");
  sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "Game Testing");
  sf::Event event;
  sf::Image image;
  image.create(800, 800, sf::Color::Black);
  
  bool isBlackPixel = false;
  sf::Color blackPixel(0,0,0,255);
  sf::Color whitePixel(255, 255, 255, 255);
  
  for (int y = 0; y < 800; y++){
 
    for (int x = 0; x < 800; x++){
      if (isBlackPixel)
        image.setPixel(x, y, blackPixel);
      else
        image.setPixel(x, y, whitePixel);
   
      if (!(x % 100))
        isBlackPixel = !isBlackPixel;
    }
    
    if(!(y%100))
      isBlackPixel = !isBlackPixel;
  }
  sf::Texture texture;
  texture.loadFromImage(image);
  sf::Sprite sprite(texture);
  while (renderWindow.isOpen()){
    while (renderWindow.pollEvent(event)){
//    	switch (event.type) {
//            case sf::Event::MouseButtonPressed:
//            	curPos.x = sf::Mouse::getPosition(renderWindow).x/100;
//            	curPos.y = sf::Mouse::getPosition(renderWindow).y/100;
//            	switch (event.type) {
//            		case sf::Event::MouseButtonPressed:
//            			newPos.x = sf::Mouse::getPosition(renderWindow).x/100;
//            			newPos.y = sf::Mouse::getPosition(renderWindow).y/100;
//            			break;
//				}
//				
//				break;
//        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
    		curPos.x = sf::Mouse::getPosition(renderWindow).x/100;
            curPos.y = sf::Mouse::getPosition(renderWindow).y/100;
    	}
    	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
			newPos.x = sf::Mouse::getPosition(renderWindow).x/100;
            newPos.y = sf::Mouse::getPosition(renderWindow).y/100;
			Log<<"("<<curPos.x<<","<<curPos.y<<") to ("<<newPos.x<<","<<newPos.y<<")"<<endl;
		}
      if (event.type == sf::Event::Closed)
                renderWindow.close();
    }
    renderWindow.clear();
    renderWindow.draw(sprite);
    renderWindow.display();
  }
  Log.close();
}
