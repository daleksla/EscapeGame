#include "game.h" //.h file (to get ability to make objects)
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <unistd.h>
#include <thread>
using namespace std ;

/* This is our 'client file'. It will be used to create an instance of the class'
 * It will also determine what, how and when we use it 
 * To run in terminal, type 'c++ game.cpp source.cpp' */

string returnCommand()
{ 
	string value ;
	cout << "< Command: " ; cin >> value ;
	cout << endl ;
	return value ;
}

string returnData()
{ 
	string value ;
	cout << "< data: " ; cin >> value ;
	cout << endl ;
	return value ;
}

void examineRoom(Player player, Room solitary, Room cell1, Room cell2, Room cell3, Room cell4, Hallway hallwayNorth, Hallway hallwaySouth)
{	
	//print description
	if(player.getX() == 1 && player.getY() == 0) {solitary.printDescription() ; solitary.printItems(); }
	if(player.getX() == 1 && player.getY() == 1) {hallwaySouth.printDescription() ; hallwaySouth.printItems(); }
	if(player.getX() == 0 && player.getY() == 1) {cell1.printDescription() ; cell1.printItems(); }
	if(player.getX() == 2 && player.getY() == 1) {cell2.printDescription() ; cell2.printItems(); }
	if(player.getX() == 1 && player.getY() == 2) {hallwayNorth.printDescription() ; hallwayNorth.printItems(); }
	if(player.getX() == 0 && player.getY() == 2) {cell3.printDescription() ; cell3.printItems(); }
	if(player.getX() == 2 && player.getY() == 2) {cell4.printDescription() ; cell4.printItems(); }
}

void printNameAgain(Player player, Room solitary, Room cell1, Room cell2, Room cell3, Room cell4, Hallway hallwayNorth, Hallway hallwaySouth)
{
	//print name
	if(player.getX() == 1 && player.getY() == 0) {solitary.printName(); }
	if(player.getX() == 1 && player.getY() == 1) {hallwaySouth.printName(); }
	if(player.getX() == 0 && player.getY() == 1) {cell1.printName(); }
	if(player.getX() == 2 && player.getY() == 1) {cell2.printName(); }
	if(player.getX() == 1 && player.getY() == 2) {hallwayNorth.printName(); }
	if(player.getX() == 0 && player.getY() == 2) {cell3.printName(); }
	if(player.getX() == 2 && player.getY() == 2) {cell4.printName(); }
}

bool checkRooms(Player player, vector <Room> rooms, vector<Hallway> hallways, string direction, int valueToChange)
{
	int x = player.getX() ; int y = player.getY() ;
	if(direction == "x") {x+= valueToChange ;}
	if(direction == "y") {y+= valueToChange ;}
	
	for(int i=0; i < rooms.size(); i+=1)
	{
		if(rooms[i].getX() == x && rooms[i].getY() == y) {return true;}
	}
	
	for(int i=0; i < hallways.size(); i+=1)
	{
		if(hallways[i].getX() == x && hallways[i].getY() == y) {return true;}
	}
	
	return false ;
}

int main()
{
	cout << "Welcome to Salih's text adventure game - Good luck!\n" << endl ;
	cout << "Type in a single word command followed by further input (where appropriate)" << endl ;
	cout << "(hint: type 'help' to get a list of commands & how to implement them)" << endl ;
	cout << endl ;
	
	bool status = false ; //will change to true if person wins game in room 2,2 ; used for a while loop
	bool result = false ; //if person moves
	bool executed = false ;
	//define objects 
	Keys keys({"green-key", "silver-key", "final-key", "game", "guard"}, 
			  {0,1,2, 100, 20}, 
			  {"This key is needed to enter room Cell #2", "This key is needed to enter room Cell #3", "This key is needed to enter Cell #4", "Type 'play game' to use it", "He might have something of use to you - type 'play guard'"}) ; //create a map of keys

	Player player("Salih", 1, 0, {}) ; //create player
	player.setCommandsAndDescriptions() ; //set universal commands & their descriptions
	Maps maps ;
	Room solitary(1, 0, "Solitary Confinement", "Your prison cell; ahead is the South part of the Hallway", {-1});
	Hallway hallwaySouth(1,1,"South Hallway", "To your west is Cell #1, to your east is Cell #2, to your south is Solitary Confinement") ;
	Room cell1(0,1, "Cell #1", "To your east is the South Hallway", {0}) ;
	Room cell2(2,1, "Cell #2", "To your west is the South Hallway", {1}) ;
	Hallway hallwayNorth(1,2,"North Hallway", "To your west is Cell #3, to your east is Cell #4, to your south is the South Hallway") ;
	Room cell4(2,2, "Cell #4", "To your west is the North Hallway. On the floor is a game", {100});
	Room cell3(0,2, "Cell #3", "To your east the North Hallway. There is a guard in this room", {-1});
	Guard guard("Guard", 0, 2, {2}) ;

	solitary.printName();
	maps.mapChecker(player.getX(), player.getY());
	solitary.printItems() ;
	
	while(status == false)
	{
		executed = false ;
		
		string command = returnCommand() ; //call function
		if(!player.isCommandLegit(command)) {cout << "Invalid command, try again!" << endl ; continue ;}
		//all statements below only require one parameter (command)	NOTE: use function to check valid instructions after while loop implemented
		if(command=="help") {player.help() ; executed = true ;} //continue so we return to top of while loop again
		else if(command == "quit") {cout << "Thanks for playing!" << endl ; return 0 ;}
		else if(command == "clear") {cout << "\033[2J\033[1;1H" << endl ; executed = true ; }
		//all statement's below require command & 'data'
		else {
			string data = returnData() ; //call function, get excess data
			if(command == "move")
			{
				executed = true ;
				if(data == "north" || data=="south" || data=="east" || data=="west")
				{
					string inputted_direction ;
					int inputted_valueToChange;
					if(data=="north" || data=="south")
					{
						inputted_direction = "y";
						if(data=="north") {inputted_valueToChange = 1;}
						if(data=="south") {inputted_valueToChange = -1;}
					}
					if(data=="east" || data=="west")
					{
						inputted_direction = "x";
						if(data=="east") {inputted_valueToChange = 1;}
						if(data=="west") {inputted_valueToChange = -1;}
					}
					bool result = checkRooms(player, {solitary, cell1, cell2, cell3, cell4},{hallwaySouth, hallwayNorth}, inputted_direction, inputted_valueToChange);//to pass to movement function so rooms exists
					if(result == true) 
					{
						bool anotherresult = player.move(data); 
						if(anotherresult){
							printNameAgain(player, solitary, cell1, cell2, cell3, cell4, hallwayNorth, hallwaySouth) ;
							if(player.getX() != 2 && player.getY() != 3) {maps.mapChecker(player.getX(), player.getY()) ;}
							examineRoom(player, solitary, cell1, cell2, cell3, cell4, hallwayNorth, hallwaySouth) ;}		
					} 
					else {cout << "You can't move there!" << endl ;}
				}
				else {cout << "Not a valid direction!" << endl ;}
			}
			if(command == "examine")
			{
				executed = true ;
				if(data == "room")
				{
					if(data=="room"){examineRoom(player, solitary, cell1, cell2, cell3, cell4, hallwayNorth, hallwaySouth) ;}
				}
				else if(data == "inventory") {player.printInventory() ; executed = true ;}
				else if(data == "position") {printNameAgain(player, solitary, cell1, cell2, cell3, cell4, hallwayNorth, hallwaySouth) ; maps.mapChecker(player.getX(), player.getY()) ;}
				else if(data == "guard" && (player.getX()==0 && player.getY() == 2)) 
				{
					 cout << Keys::NameToDescription(data) << endl ;
				}
				else 
				{
					if(Keys::NameToDescription(data) == "invalid") {cout << "That isn't a valid item!" << endl ;}
					else 
					{
						bool canYouSee ;
						int itemID = keys.NameToItem(data);
						if(player.getX() == 1 && player.getY() == 0) 
							{canYouSee = solitary.isItemInRoom(itemID); }
						else if(player.getX() == 0 && player.getY() == 1) 
							{canYouSee = cell1.isItemInRoom(itemID); }
						else if(player.getX() == 2 && player.getY() == 1) 
							{canYouSee = cell2.isItemInRoom(itemID); }
						else if(player.getX() == 0 && player.getY() == 2) 
							{canYouSee = cell3.isItemInRoom(itemID); }
						else if(player.getX() == 2 && player.getY() == 2) 
							{canYouSee = cell4.isItemInRoom(itemID); }
						//remove item from room if true
						if(canYouSee == true || player.isItemInInventory(itemID)) {cout << data << ": " << Keys::NameToDescription(data) << endl ;}
						else {cout << "You can't examine that! (hint: be in the same room or get it)" << endl;}
					}
				}
			}
			else if(command == "play" && data == "guard" && (guard.scoreReturner()==0))
			{
				executed = true ;
				if( (player.getX() == 0 && player.getY() == 2) ==false) { cout << "Play who??? (hint: get to Cell #3)" << endl ; continue ;}
				guard.askInput() ; 
				if(guard.scoreReturner() >= 3) 
				{
					guard.removeItems(2) ;
					player.addItems(2) ;
					cout << "You've bested the guard! A 'prize' has been deposited in your inventory ;)" << endl ;
				}
				else {cout << "You didn't win, try again!" << endl ; guard.reset();}
			}
			else if(command == "play" && data == "guard" && (guard.scoreReturner()>0)) {cout << "You've already won! (a.k.a he's no longer of use)" << endl ;}
			else if(command == "play" && data == "game")
			{
				executed = true ;
				if( (player.getX() == 2 && player.getY() == 2) ==false) { cout << "Play what game??? (hint: get to Cell #4)" << endl ; continue ;}
				Anagram anagram((rand() % 2)) ;
				if(anagram.scoreReturner() == 3)
				{
					cout << "The game, upon your victory, propelled you out the exit as your reward... (with a little parting gift as a treat)" << endl ;
					player.setLocation(2,3);
				}
				else {continue ;}	
			}
			else if(command == "get") 
			{
				//retrieve item id
				int itemID = keys.NameToItem(data);
				if(data == "green-key" || data == "silver-key") 
				{
					bool canYouRemove ;
					//determine if its in the room
					if(player.getX() == 1 && player.getY() == 0) 
						{canYouRemove = solitary.isItemInRoom(itemID); }
					if(player.getX() == 1 && player.getY() == 1) 
						{hallwaySouth.printItems(); bool canYouRemove = false; }
					if(player.getX() == 0 && player.getY() == 1) 
						{canYouRemove = cell1.isItemInRoom(itemID); }
					if(player.getX() == 2 && player.getY() == 1) 
						{canYouRemove = cell2.isItemInRoom(itemID); }
					if(player.getX() == 1 && player.getY() == 2) 
						{hallwayNorth.printItems(); bool canYouRemove = false;}
					if(player.getX() == 0 && player.getY() == 2) 
						{canYouRemove = cell3.isItemInRoom(itemID); }
					if(player.getX() == 2 && player.getY() == 2) 
						{canYouRemove = cell4.isItemInRoom(itemID); }
					//remove item from room if true
					if(canYouRemove == true) 
					{
						if(player.getX() == 1 && player.getY() == 0) {solitary.removeItems(itemID); }
						if(player.getX() == 0 && player.getY() == 1) {cell1.removeItems(itemID); }
						if(player.getX() == 2 && player.getY() == 1) {cell2.removeItems(itemID); }
						if(player.getX() == 0 && player.getY() == 2) {cell3.removeItems(itemID); }
						if(player.getX() == 2 && player.getY() == 2) {cell4.removeItems(itemID); }
						player.addItems(itemID); 
						cout << "You've got the " << data << endl ;
						continue ;
					}
					cout << "You can't remove that! (hint: be in the same room!)" << endl ;
				}
				else{cout << "You can't take that!"<<endl ;}
			}
		}
		if(executed=false) {cout << "Invalid input, try again!" << endl ; }
		cout << endl ;
		status = player.gameWon() ;
	}
	sleep(3); 
	//create an 'Exit' object, which upon creation clears the screen & says something nice
	cout << "\033[2J\033[1;1H" << endl ;
	Exit exit(2, 3, "Exit", "A gift awaits inside...") ;
	//
	return 0 ;
} 