# CS217-CL217-ChessOOP

<img src="https://imgur.com/1wULnoj.png?raw=true">

Chess Game designed as a semester project for OOP course at FAST National University-NUCES, Karachi.

![FAST National University](https://upload.wikimedia.org/wikipedia/en/thumb/e/e4/National_University_of_Computer_and_Emerging_Sciences_logo.png/250px-National_University_of_Computer_and_Emerging_Sciences_logo.png)

## Description

Object-Oriented Programming is an important programming paradigm. It is important that a programmer is well-versed with its principles to write code that makes development and maintenance of code easier and secure. Game Development relies on OOP more than any other form of development. It is, therefore, an effecient way to demonstrate skills that were picked up during the course. Chess is a game that is played worldwide and is a very good example of how different core objects of the game can be simulated virtually throught Object-Oriented Programming. This game is completely made from scratch and uses OOP principles to implement a completely functional game that can be played both Offline and Online over a LAN network or Public Internet using port-forwarding. Simple and Fast Multimedia Library (SFML) was used to achieve the graphical and network functionality of the game. 

## Getting Started

### Dependencies

* Windows 10/MacOS/Linux
* SFML (Simple and Fast Multimedia Library)

### Installing

* All the files linked in the GitHub repository are needed for the project to run as intended <br>
This project was developed on Windows 10 using Dev-C++ with SFML Library Version 2.4.2 TDM. The files for this particular version are available in the respoitory. However, it should be made sure that the library you download is compatible with the exact version of the C++ compiler that you are using. In this case, the compiler in use was TDM-GCC 4.9.2 64-bit Release. For more information and download, visit https://www.sfml-dev.org/download.php

### Executing program

* How to run the program <br>
Once all the files have been downloaded and the library has been linked, compile and run chess.cpp.

```
g++ chess.cpp board.cpp cell.cpp network.cpp gui.cpp piece.cpp king.cpp queen.cpp bishop.cpp rook.cpp knight.cpp pawn.cpp -I <sfml-include>
g++ chess.o board.o cell.o network.o gui.o piece.o king.o queen.o bishop.o rook.o knight.o pawn.o -L <sfml-library> -static-libgcc -DSFML_STATIC -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
```

<b>Specific Instructions for Executing the Project on Dev-C++</b>

To run this project using Dev-C++, create a new project (either console or GUI - console is required for debugging) and then follow the instructions in this video by Mike Exc (All Rights Reserved) https://www.youtube.com/watch?v=uAd2jINKCxc
When done, add the chess.cpp file to the project and press F11 to compile and run.

## Gameplay

### Features
Complete functionality of chess game has been added except for draw conditions. Only one draw condition is implemented up till now which will occur when the moving side is not in check and has no moves left.
Special Moves Available:
* En Passant
<img src="https://imgur.com/axSaVoF.gif?raw=true" width="300" height="300">

* Short Castling
<img src="https://imgur.com/Z2QLP7m.gif?raw=true" width="300" height="300">

* Long Castling
<img src="https://imgur.com/C5fQiNY.gif?raw=true" width="300" height="300">

* Pawn Promotion
<img src="https://imgur.com/CV0VKaJ.gif?raw=true" width="300" height="300">

* Stalemate by no legal moves left

### Movement
#### Main Menu
The main menu works with a KEYBOARD only and up/down arrow keys are used to navigate the menu. You can enter the IP address directly by typing using the keyboard.
Refer to help menu for a known bug regarding the Host mode.

![](https://imgur.com/INeMw52.gif)

#### Offline/Online Modes
To make a move, use the left mouse button to select the piece you want to move and right mouse button at the desired location that you want to move the piece to.

IMPORTANT: It is important to note that before the PROMOTION move, you will have to press q(queen), r(rook), k(knight), or b(bishop) on the keyboard before making hitting the right mouse button. By default, the game promotes all pawns to Queen.

![](https://imgur.com/ujhUFrn.gif)

## Help/Known Issues

* The Host Functionality in the program is bugged due to an issue in programming the main event loop of the program. It will go to not responding when left for a while, the only options are to connect or to force quit it if that happens.
* Highlighting possible moves is only available for non-special/generic moves as of now.


## Author

Muhammad Zain Ul Abiddin<br>
muhammadzain757@gmail.com<br>
[LinkedIn](https://www.linkedin.com/in/muhammad-zain-ul-abiddin-83194a201/)

## Acknowledgments

* [JohnPablock](https://opengameart.org/content/chess-pieces-and-board-squares) for Texture Images
* [Userstyles.org](https://userstyles.org/styles/113726/lichess-board-babinga) for Board Background


## Online Gameplay
![](https://user-images.githubusercontent.com/68997634/119646585-c3f52100-be38-11eb-94fc-db266221e3cc.gif)

