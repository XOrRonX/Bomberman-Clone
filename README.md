# Bomberman-Clone
A clone of the game "Bomberman" 

# Important
### To use this project, please download ZIP file OrRon-Bomberman.zip. 


## Getting Started

### Prerequisites

In order to run the project you need:
1. Visual Studio with Windows 10 SDK version 10.0.17763.0

2. SFML

### Installing

1. Download Visual Studio from [here](https://visualstudio.microsoft.com/downloads/).
In installation process choose "Windows 10 SDK (10.0.17763.0)" at the Individual components tab. If you have Visual Studio installed already you can download SDK from "Visual Studio Installer".

2. Download sfml 2.5.0 from [here](https://drive.google.com/open?id=1_D0G_IYPpvv2JnhslLdmXZRFd6zsjqQx).
just extract it and run "SFMLInstall.bat" as administrator (extraction path must contain english letters only).

  
   
   ![alt text](bomberman_pic.PNG)
   
### Prorgam explanation: 

	this program implement the Bomberman game.
	In this game there are a few screens, a player win the game when 
	he is able to find and get into the door in all screens without getting killed
	more than 2 time and w/o taking more time than was defined in the file of the screens
	before finding a door- the player is moving in the creens using a robot he
	control.
	The game is runing on time and so the user controlling the robot can decide
	to which direction the Robot will go, the user needs to press only once the direction 
	and then the robot will continue in that same direction until the user press space
	or untill the robot hit a rock or a wall or the end of the srcreen
	Putting a bomb start a count down of 4 seconds untill the bomb explode. 
	Other than a bomb and a Robot there are also guards which are moving in the
	screen. When a guard meet the Robot it immidietly kill it and the robot 
	lose 1 life of its 3 lives. on the screen there are walls or rocks guards and 
	Robot cannot go through wall.
	When a bomb explode it kills robot or guard that in its location or anywere 
	around its locaiton (up/down/right/left) - the bomb also destroy any rock 
	in these places as well.
	Beyond the above there are aditional objects in the screen:
	1. Present - when a robot collide with it it gets one more bomb to its stock of bombs
	2. Life present - a present which gives one more life to the robot
	3. Ghost Guard - a gaurd that is a ghost becasue it can move through walls, this gaurd
		can also put bombs, this guard runs after the Robot and whenever it collide with
		it the guard put a bomb on the robot tryin to kill him with a bomb


### Design:

Main.cpp takes care of two things:
1. checking if there are more files of screens to read  
2. runds in endless loop each loop is a full game it calls run()
   function of bomberman which execute the game, when the game is over 
   bomberman return to main with or restart the game or exit , if it is start the game 
   main will delete and reallocation the game which is class Bomberman 
   with all the screens


Objects of the game:

Starting with the basic objects.

There are two inherits in the game
1. Regular - Class StaticObject is the parent and it implement all the functions
	From Static objects inherit: Bomb, GhostBomb, Wall, Rock, Door, Present, Life Present
	Class Life is an adition not defined in the project and it is a present 
	that if the robot runs over it get one more life - its sign in input file is 'L'
	Class GhostBomb is an adition not defined in the project it is a bomb that a
	ghost can put near a robot - how a Ghost behave is described below
	these classes have little unique content to them most of their functionality
	is in Static Object
2. Polimorphism  - Class BaseObject is the parent with all its function virtual
	From Base Object inherits: Robot, Guard and Ghost
	Class Ghost is an adition not defined in the project, a Ghost is like a guard 
	with special capabilities, it can move through walls and it can put bombs, it 
	is runing after the Robot and it tries to put on it bombs. its sign in the 
	input file is 'G'

Class Board is another base object which is taking care of reading one input file 
		    and storing all its information in data members.
			it stores the how the screen looks in matrix of chars and it also stores
			the number of bombs, the time of the screen and the lines and columns


Class Bomberman - this is not a base class
	The top object it holds array of Class Controller (explained below), 
	each controller is like a screen it holds all the object of the screen 
	and manage the game. The controllers array is created when main call 
	Bomberman to add a screen and this happens as long 
	as main see there are more files with screen available to read.  
	Bomberman also hold a menu screen where the user can decide if to start a game
	or to exit, when one game end the user can decide to start the game from the 
	begining or to exit the game.
	Main calls run() function of bomberman, run() function starts the menu 
	and based on the user if he chose exit then the game ends and if start 
	then bomberman call run() of the active Controller and then wait until the 
	controller ends executing the screen and all its moves.
	then Bomberman based on the state decide what to do if game over then open the 
	menue for the user to decide what to do next and if not game over then 
	it means the robot found a door so move to next controller if exist 
	and copy it the points and the life of the previous controller.
	If this was the las controller then the game is won.	

Class Controller is actually a screen 
	the is the main object of the game and it has all the objects of the game
	This class manages all the moves and knows all the rules of the game 
	for one screen It has these main obejcts:
		1. m_board of class Board - hold all the info read on one screen from a file 
		2. m_gameObjects - vector of GameObjects of Guard/Robot/Ghost 
		3. m_gameStaticObjects - vector of all the static objects not including bombs
		4. m_bombsList - vector of class Bomb 
		5. all the graphical objects like Window
	

### File Format

	Each file is only one screen
	Main() is looking for the following name format "board.bombX.txt"
	where X is a numebr starting from 1 and next file will be 2 next 3 and so on
	when main() does not find the next file it assumes no more files or screens.

### List of files:

main.cpp  - holds the game of class Bomberman, in endless loop call the game until
			the user chose in the menu to exit
Macros.h - Holds all the enums and consts for the program
Controller.cpp and Controller.h - holds class Controller described abot 
BaseObject.cpp and BaseObject.h - virtual base class BaseObject
Board.cpp and Board.h - class Board
Bomb.cpp and Bomb.h - class Bomb
Bomberma.cpp and Bomberman.h - class Bomberman
Door.cpp and Door.h - class Door
Ghost.cpp and Ghost.h - class Ghost
GhostBomb.cpp and GhostBomb.h - class GhostBomb
Guard.cpp and Guard.h - class Guard
Life.cpp and Life.h - class Life
Present.cpp and Present.h - class Present
Robot.cpp and Robot.h - class Robot
Rock.cpp and Rock.h - class Rock
StaticObject.cpp and StaticObject.h - base class StaticObject 
Wall.cpp and Wall.h - class Wall

There are 4 ready screens :

board.bomb1.txt
board.bomb2.txt
board.bomb3.txt
board.bomb4.txt


List of graphical used files sound and pictures


### Main data structures:
		Class Controller which holds many objects
		1. m_board of class Board - hold all the info read on one screen from a file 
		2. m_gameObjects - vector of GameObjects of Guard/Robot/Ghost 
		3. m_gameStaticObjects - vector of all the static objects not including bombs
		4. m_bombsList - vector of class Bomb 
		5. all the graphical objects like Window

		Class Bomberman which holds Vector of controller one for every 
						screen


### Algorithms:
			Guard Move:

			The algorithm to decide where to move the smart Guard
			Gaurd movement - The guard movement has two parts to it:
			  1. Tries to move closer to the Robot based on the Robot position 
			  2. Take a random step in case of a collision 
			 

### known bugs - no known bugs

### comment -


the main differences and aditions to the original project definition:

a. class Life is a present that adds life to the Robot - its mark in the input 
   file is 'L' and it shape on the screen is a red heart
b. class Ghost is a type of special guard that runs after the Robot and it throw
   bombs on the robot when it collide with it. There are no limits to the bombs
   it can have. its sign on the input file is 'G'
c. When you wants to leave a screen the way to do it is press the key D 
    on the keyboard
d. in the default mode the guards are moving half the speed of the robot. if you
    want to make them move as fast as the robot need to press the key H. Pressing
	it second time will get the guards back to a speed that is half the speed 
	of the Robot.



