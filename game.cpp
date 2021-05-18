#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <iterator>
#include <cmath>
#include "game.h" //.h file (to get declarations)
using namespace std ;

/* This is where we will implement the functions / variables from our .h file 
 * This will be one of our .cpp files (our 'implement' file)
 * We will have to compile both .cpp files simultaneously to run the program */

Character::Character(string inputted_name, int inputted_x, int inputted_y, vector<int> inputted_inventory)
{
	this->name=inputted_name; 
	this->x=inputted_x ; this->y=inputted_y ;
	this->inventory=inputted_inventory; 
}

int Character::removeItems(int ID) {inventory.erase(remove(inventory.begin(), inventory.end(), ID), inventory.end());}

void Character::printInventory()
{
	if(inventory.empty()) {cout << "There are no items in his inventory!" << endl;}
	else {
		cout << "The following items are in his inventory: ";
		for(vector<int>::iterator it = begin(inventory); it != end(inventory); it = next(it)) 
		{
			if(it == prev(end(inventory))) { cout << Keys::ItemToName(*it) << endl ;}
			else {cout << Keys::ItemToName(*it) ;}
		}
	}
}

vector <string> Guard::questions = {} ;
map<string, string> Guard::answerToQuestion = {} ;

void Guard::setQuestionsAndATQ()
{
	questions = {"When was the Battle of Hastings?",
				 "Which continent in Egypt in?",
				 "What animal is on the Slytherin emblem?",
				 "Which country is Cairo located in?",
				 "Name the main villain in the book series 'Harry Potter'",
				 "Provide a synonym for witchcraft"
	};
	
	answerToQuestion.insert(pair<string,string>("1066","When was the Battle of Hastings?"));
	answerToQuestion.insert(pair<string,string>("Africa","Which continent in Egypt in?"));
	answerToQuestion.insert(pair<string,string>("Snake","What animal is on the Slytherin emblem?"));
	answerToQuestion.insert(pair<string,string>("Egypt","Which country is Cairo located in?"));
	answerToQuestion.insert(pair<string,string>("Voldemort","Name the main villain in the book series 'Harry Potter'"));
	answerToQuestion.insert(pair<string,string>("Magic","Provide a synonym for witchcraft"));
	
}

void Guard::incrementAttempts() {attempts +=1 ;}

void Guard::incrementScore() {score +=1 ;}

int Guard::scoreReturner()
{
	return score ;
}

void Guard::askInput() 
{
	setQuestionsAndATQ() ;
	cout << "Please type in the answers to the following questions: " << endl ;
	while(score != 3 && attempts < 5)
	{
		currentQuestion = questions[attempts] ;
		cout << questions[attempts] << endl ;
		cout << "> " ; cin >> word ;
		if(word == "quit") {cout << "Thanks for playing!" << endl ; exit(0);}
		if(scoreDeterminate()==-1) {continue ;}
	}
}

void Guard::reset() 
{
	score = 0 ;
	attempts = 0 ;
}

int Guard::scoreDeterminate()
{
	incrementAttempts() ;
	if(answerToQuestion.at(word) == currentQuestion)
	{
		cout << "Correct answer!" << endl ;
		incrementScore() ;	
		return 0 ;
	}
	cout << "Incorrect answer!" << endl ;
	return -1 ;
}

bool Player::move(string direction)
{
	int fake_x=x; int fake_y=y ; bool status = true ;
	
	if(direction=="north") {fake_y+=1; }
	else if(direction=="south") {fake_y-=1; }
	else if(direction=="east") {fake_x+=1; }
	else {fake_x-=1; }
	
	if((fake_x == 2 && fake_y==1) || (fake_x == 0 && fake_y == 2) || (fake_x == 2 && fake_y == 2))
	{
		status = false ;
		if(fake_x==2&&fake_y==1)
		{
			for(vector<int>::iterator it = begin(inventory); it != end(inventory); it = next(it)) 
			{
				if(*it == 0) {status = true; break ;}
			}
		}
		else if(fake_x==0&&fake_y==2)
		{
			for(vector<int>::iterator it = begin(inventory); it != end(inventory); it = next(it)) 
			{
				if(*it == 1) {status = true; break ;}
			}
		}		
		else if(fake_x==2&&fake_y==2)
		{
			for(vector<int>::iterator it = begin(inventory); it != end(inventory); it = next(it)) 
			{
				if(*it == 2) {status = true; break ;}
			}
		}
	}
	else {status = true ;}
	
	if(status == false)
	{
		if(fake_x==2&&fake_y==1) {cout << "You haven't got the " << Keys::ItemToName(0) << endl ;}
		if(fake_x==0&&fake_y==2) {cout << "You haven't got the " << Keys::ItemToName(1) << endl ;}
		if(fake_x==2&&fake_y==2) {cout << "You haven't got the " << Keys::ItemToName(2) << endl ;}
	}
	else {this->x=fake_x ; this->y=fake_y; return status ;}
	return status ;
}

void Player::setCommandsAndDescriptions()
{
	commands={"move", "get", "quit", "examine", "clear", "play", "help"};
	commandDescriptions={"Player moves to a new location (providing it's valid); possible directions are north, south, east and west.\nExample: move north",
							 "Player can get a specified item off the floor (providing it's within the room).\nExample: get green-key",
							 "Player can exit game.\nExample: quit",
							 "Player can view the contents of a certain 'location'/item.\nExample - examine room, examine inventory, examine position, examine item-name",
							 "Player can clear contents of his screen for a clearer view.\nExample -  clear",
							 "Player can play certain objects present in the room with them.\nExample - play game, play guard",
							 "Player can view list of commands & how to use them.\nExample - help"};
}
	
void Player::updateMoves() {moves +=1 ;}

vector<string> Player::commands = {};
vector<string> Player::commandDescriptions = {};

void Player::help() 
{
	cout << "Valid commands: "<< endl;
	for(vector<string>::iterator it = begin(commands); it != end(commands); it = next(it)) 
	{
		for(vector<string>::iterator itz = begin(commandDescriptions); itz != end(commandDescriptions); itz = next(itz)) 
		{
			cout << *it << ": " << *itz << endl ;
			cout << endl ;
			it = next(it) ;
		}
		break ;
	}
}

bool Player::isItemInInventory(int itemID)
{
	for(vector<int>::iterator it = begin(inventory); it != end(inventory); it = next(it)) 
	{
		if(*it == itemID) {return true ;}
	}
	return false ;
}

bool Player::isCommandLegit(string command) 
{
	for(vector<string>::iterator it = begin(commands); it != end(commands); it = next(it)) 
	{
		if(*it == command) {return true ;}
	}
	return false ;
}

void Player::printInventory()
{
	if(inventory.empty()) {cout << "You have no items in your inventory!" << endl;}
	else {
		cout << "The following items are in your inventory: ";
		for(vector<int>::iterator it = begin(inventory); it != end(inventory); it = next(it)) 
		{
			if(it == prev(end(inventory))) { cout << Keys::ItemToName(*it) << endl ;}
			else {cout << Keys::ItemToName(*it) << ", " ;}
		}
	}
}

void Player::addItems(int itemID)
{
	inventory.push_back(itemID) ;
}

int Player::getX() {return x;}

int Player::getY() {return y;}

void Player::setLocation(int inputted_x, int inputted_y) {this->x=inputted_x ; this->y=inputted_y; }

bool Player::gameWon() {if(x==2&&y==3) {return true ;} return false ;}

std::map<string, int> Keys::mapNameToItem = {};
std::map<string, string> Keys::mapNameToDescription = {};
std::map<int, string> Keys::mapItemToName = {};

Keys::Keys(vector<string>names, vector<int> ids, vector<string> descriptions)
{
	for(vector<string>::iterator it = begin(names); it != end(names); it = next(it)) 
	{
		for(vector<int>::iterator itz = begin(ids); itz != end(ids); itz = next(itz)) 
		{
			mapNameToItem.insert(pair<string,int>(*it,*itz));
			mapItemToName.insert(pair<int, string>(*itz,*it));
			it = next(it) ;
		}
		break ;
	}
	
	for(vector<string>::iterator it = begin(names); it != end(names); it = next(it)) 
	{
		for(vector<string>::iterator itz = begin(descriptions); itz != end(descriptions); itz = next(itz)) 
		{
			mapNameToDescription.insert(pair<string,string>(*it,*itz));
			it = next(it) ;
		}
		break;
	}
}

int Keys::NameToItem(string inputted_name) 
{
	return mapNameToItem[inputted_name] ;
}

string Keys::ItemToName(int inputted_int) 
{
	return mapItemToName[inputted_int] ;
}

string Keys::NameToDescription(string inputted_name)
{
	if(mapNameToDescription[inputted_name] != "") {return mapNameToDescription[inputted_name];} 
	else{return "invalid";}
}

Exit::Exit(int inputted_x, int inputted_y, string inputted_name, string inputted_description) 
{
	this->x=inputted_x ; 
	this->y=inputted_y ;
	this->name=inputted_name ;
	this->description=inputted_description;
	printItems() ;
}

void Exit::printItems()
{
	
	cout << "Le golden Meerkat     ,'''''-._             " << endl ;
	cout << "                    ;  ,.  <> `-._ 		" << endl ;
	cout << "                    ;  \'   _,--'""" << endl ;
	cout << "                   ;      (" << endl ;
	cout << "                   ; ,   ` \"" << endl ;
	cout << "                   ;, ,     \"" << endl ;
	cout << "                  ;    |    |" << endl ;
	cout << "                  ; |, |    |\"" << endl ;
	cout << "                 ;  |  |    | \"" << endl ;
	cout << "                 |.-\ ,\    |\ :" << endl ;
	cout << "                 |.- `. `-. | ||" << endl ;
	cout << "                 :.-   `-. \ ';;" << endl ;
	cout << "                 .- ,   \;;|" << endl ;
	cout << "                  ;   ,  |  ,\"" << endl ;
	cout << "                 ; ,    ;    \"" << endl ;
	cout << "                 ;    , /`.  , )" << endl ;
	cout << "              __,;,   ,'   \  ,|" << endl ;
	cout << "        _,--''__,|   /      \  :" << endl ;
	cout << "      ,'_,-''    | ,/        | :" << endl ;
	cout << "     / /         | ;         ; |" << endl ;
	cout << "    | |      __,-| |--..__,--| |---.--....___" << endl ;
	cout <<"___,-| |----''    / |         `._`-.          `----" << endl ;
	cout <<"      \ \        `"""             """      --" << endl ;
	cout <<"       `.`.                 --'" << endl ;
	cout <<"         `.`-._        _,             ,-     __,-" << endl ;
	cout <<"            `-.`." << endl ;
	cout <<"   --'         `;" << endl ;	
}

void Area::printName()
{
	cout << "You are in the " << name << endl ;
}

int Area::getX() { return x ;}

void Area::printDescription() {cout << description << endl ;}

int Area::getY() { return y ;}

Room::Room(int inputted_x, int inputted_y, string inputted_name, string inputted_description, vector<int> inputted_items) 
{
	this->x=inputted_x ;
	this->y=inputted_y ;
	this->name=inputted_name ;
	this->description=inputted_description ;
	this->items=inputted_items;
}

void Room::removeItems(int itemID)
{
	items.erase(remove(items.begin(), items.end(), itemID), items.end());
}

void Room::printItems() 
{
	if(items.empty()) { cout <<  "You've taken all the items in the room!" << endl ; }
	else if(items[0] == -1) { cout << "There are no items in this room!" << endl ; }
	else {
		cout << "The following items are in the room: ";
		for(vector<int>::iterator it = begin(items); it != end(items); it = next(it)) 
		{
			if(it == prev(end(items))) { cout << Keys::ItemToName(*it) << endl ;}
			else {cout << Keys::ItemToName(*it) ;}
		}
	}
}

bool Room::isItemInRoom(int itemID)
{
	for(vector<int>::iterator it = begin(items); it != end(items); it = next(it)) 
	{
		if(*it == itemID) {return true ;}
	}
	return false ;
}
 
Hallway::Hallway(int inputted_x, int inputted_y, string inputted_name, string inputted_description) 
{
	this->x=inputted_x ;
	this->y=inputted_y ;
	this->name=inputted_name ;
	this->description=inputted_description ;
}

void Hallway::printItems()
{
	cout << "There are no items to be picked up in hallways" << endl ;
}

void Maps::printMap0()
{
	cout <<"               ____ " << endl;
	cout <<"              |_  _|" << endl;
	cout <<" ____   ____   _||_"  << endl;
	cout <<"|_  _|=|_  _|=|_  _|" << endl;
	cout <<" _||_   _||_   _||_"  << endl;
	cout <<"|____|=|_  _|=|____|" << endl;
	cout <<"        _||_"         << endl;
	cout <<"       |____|"        << endl;
}

void Maps::printMap1()
{
	cout <<"               ____ " << endl;
	cout <<"              |_  _|" << endl;
	cout <<" ____   ____   _||_"  << endl;
	cout <<"|_  _|=|_  _|=|_  _|" << endl;
	cout <<" _||_   _||_   _||_"  << endl;
	cout <<"|____|=|_  _|=|____|" << endl;
	cout <<"\033[31m"<<"        _"<<"\033[0m"<<"||"<<"\033[31m"<<"_"         << endl;
	cout <<"\033[31m"<<"       |____|"        <<"\033[0m"<< endl; 
}
	
void Maps::printMap2()
{       
	cout <<"               ____ " << endl;
	cout <<"              |_  _|" << endl;
	cout <<" ____   ____   _||_"  << endl;
	cout <<"|_  _|=|_  _|=|_  _|" << endl;
	cout <<" _||_   "<<"\033[31m"<<"_"<<"\033[0m"<<"||"<<"\033[31m"<<"_"<<"\033[0m"<<"   _||_"  << endl;
	cout <<"|____|="<<"\033[31m"<<"|_  _|"<<"\033[0m"<<"=|____|" << endl;
	cout <<"        _||_"         << endl;
	cout <<"       |____|"        << endl;        
}
	
void Maps::printMap3()
{
	cout <<"               ____ " << endl;
	cout <<"              |_  _|" << endl;
	cout <<" ____   ____   _||_"  << endl;
	cout <<"|_  _|=|_  _|=|_  _|" << endl;
	cout <<"\033[31m"<<" _||_"<<"\033[0m"<<"   _||_   _||_"  << endl;
	cout <<"\033[31m"<<"|____|"<<"\033[0m"<<"=|_  _|=|____|" << endl;
	cout <<"        _||_"         << endl;
	cout <<"       |____|"        << endl;
}
	
void Maps::printMap4()
{
	cout <<"               ____ " << endl;
	cout <<"              |_  _|" << endl;
	cout <<" ____   ____   _||_"  << endl;
	cout <<"|_  _|=|_  _|=|_  _|" << endl;
	cout <<" _||_   _||_   "<<"\033[31m"<<"_||_"  <<"\033[0m"<< endl;
	cout <<"|____|=|_  _|="<<"\033[31m"<<"|____|" <<"\033[0m"<< endl;
	cout <<"        _||_"         << endl;
	cout <<"       |____|"        << endl;
}
	
void Maps::printMap5()
{
	cout <<"               ____ " << endl;
	cout <<"              |_  _|" << endl;
	cout <<" ____   "<<"\033[31m"<<"____"<<"\033[0m"<<"   _||_"  << endl;
	cout <<"|_  _|="<<"\033[31m"<<"|_  _|"<<"\033[0m"<<"=|_  _|" << endl;
	cout <<" _||_   _||_   _||_"  << endl;
	cout <<"|____|=|_  _|=|____|" << endl;
	cout <<"        _||_"         << endl;
	cout <<"       |____|"        << endl;
}	
	
	
void Maps::printMap6()
{
	cout <<"               ____ " << endl;
	cout <<"              |_  _|" << endl;
	cout <<"\033[31m"<<" ____"<<"\033[0m"<<"   ____   _||_"  << endl;
	cout <<"\033[31m"<<"|_  _|"<<"\033[0m"<<"=|_  _|=|_  _|" << endl;
	cout <<" _||_   _||_   _||_"  << endl;
	cout <<"|____|=|_  _|=|____|" << endl;
	cout <<"        _||_"         << endl;
	cout <<"       |____|"        << endl;
}	
	
void Maps::printMap7()
{
	cout <<"               ____ " << endl;
	cout <<"              |_  _|" << endl;
	cout <<" ____   ____   "<<"\033[31m"<<"_"<<"\033[0m"<<"||"<<"\033[31m"<<"_"  <<"\033[0m"<< endl;
	cout <<"|_  _|=|_  _|="<<"\033[31m"<<"|_  _|" <<"\033[0m"<< endl;
	cout <<" _||_   _||_   _||_"  << endl;
	cout <<"|____|=|_  _|=|____|" << endl;
	cout <<"        _||_"         << endl;
	cout <<"       |____|"        << endl;
}
	
void Maps::printMap8()
{
	cout <<"\033[31m"<<"               ____ " << endl;
	cout <<"              |_  _|" <<"\033[0m"<< endl;
	cout <<" ____   ____   _||_"  << endl;
	cout <<"|_  _|=|_  _|=|_  _|" << endl;
	cout <<" _||_   _||_   _||_"  << endl;
	cout <<"|____|=|_  _|=|____|" << endl;
	cout <<"        _||_"         << endl;
	cout <<"       |____|"        << endl;
}

void Maps::mapChecker(int x, int y)
{
	if (x == 1)
	{
		if (y == 0) {printMap1();}
		else if (y == 1) {printMap2();}
		else if (y == 2) {printMap5();}
		else {printMap0();}
	}
	else if (x == 0)
	{
		if(y == 1) {printMap3();}
		else if(y == 2) {printMap6();}
		else {printMap0();}
	}
	else if (x == 2)
	{
		if(y == 1) {printMap4();}
		else if(y == 2) {printMap7();}
		else if (y == 3) {printMap8();}
		else {printMap0();}
	}
	cout << "" << endl ;
}

vector<vector<string> > Anagram::vectorOfWordsToUse = {{"ad", "add", "dad"},{"ok", "coke", "ko"}} ;
vector<vector<string> > Anagram::listOfListOfLettersToUse = {{"a", "d", "d"},{"c", "o", "k", "e"}} ;

void Anagram::setVectors()
{
	vectorOfWordsToUse = {{"ad", "add", "dad"},{"ok", "coke", "ko"}} ;
	listOfListOfLettersToUse = {{"a", "d", "d"},{"c", "e", "k", "o"}} ;
}

void Anagram::incrementAttempts() {attempts +=1 ;}

void Anagram::incrementScore() {score +=1 ;}

Anagram::Anagram(int choice)
{
	setVectors();
	wordsToUse = vectorOfWordsToUse[choice] ;
	listOfLettersToUse = listOfListOfLettersToUse[choice] ;
	wordsLeftToUse = wordsToUse ;
	score = 0 ;	
	attempts = 0 ;
	//
	while(attempts < 5)
	{
		askInput() ;
		if(word == "quit") { cout << "Thanks for playing!" << endl ; exit(0);}
		scoreDeterminate() ;
		if(score==3) {break; }
	}
	if(score==3) {cout << "You've won the game! " << endl ;}
	
}
	
void Anagram::askInput() 
{
	if(score==0) 
	{
		cout << "Please make a word using the following letters: " ;
		for(vector<string>::iterator it = begin(listOfLettersToUse); it != end(listOfLettersToUse); it = next(it)) 
		{if(it == prev(end(listOfLettersToUse))) { cout << *it << endl ;}
		else {cout << *it << ", " ;}}
	}
	cout << "< word: " ; cin >> word ;
	cout << endl ;
}

int Anagram::scoreDeterminate()
{
	bool status = false;
	for(vector<string>::iterator it = begin(wordsLeftToUse); it != end(wordsLeftToUse); it = next(it)) 
	{
		if(*it == word) 
		{
			incrementScore() ;
			incrementAttempts() ;
			status = true ;
			wordsUsed.push_back(word) ;
			wordsLeftToUse.erase(remove(wordsLeftToUse.begin(), wordsLeftToUse.end(), word), wordsLeftToUse.end());
			return 0 ;
		}
	}

	for(vector<string>::iterator it = begin(wordsUsed); it != end(wordsUsed); it = next(it))
	{
		if(*it == word) 
		{
			cout << "You've already used that word!" << endl ;
			incrementAttempts() ;
			status = true ; 
			return 0 ; 
		}
	}

	cout << "That isn't a valid word!" << endl ;
	incrementAttempts() ;
	return 0 ;
}

int Anagram::scoreReturner()
{
	return score ;
}

Anagram::~Anagram()
{
}