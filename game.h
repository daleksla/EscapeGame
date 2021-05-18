#ifndef GAME_H
#define GAME_H

#include <string>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

/* This is a header file; it contains the declarations (defintions) of our functions and methods 
 * These will be implemented in our game.cpp file */

class Character { //to be placed in rooms (e.g guards)
	protected:
		string name ;
		int x ;
		int y ;
		vector <int> inventory ;
	public:
		Character(string inputted_name, int x, int y, vector<int>inputted_inventory) ;
		void printInventory() ;
		int removeItems(int ID) ;
};

class Guard : public Character {
	protected:
		string word ;
		int attempts =0;
		int score =0;
		string currentQuestion ;
		static vector <string> questions ; //user will be given a question
		static map<string, string> answerToQuestion ; //when answer is given, we'll retrieve q; should they match they got it right
	public:
		using Character::Character ;
		void incrementScore() ;
		void incrementAttempts() ;
		void askInput();
		int scoreReturner() ;
		int scoreDeterminate() ;
		void setQuestionsAndATQ() ;
		void reset() ;
};

class Player : public Character { //our player
	protected:
		int moves ;
		static vector <string> commands ;
		static vector <string> commandDescriptions ;
	public:
		using Character::Character ;
		bool move(string direction) ;
		void setCommandsAndDescriptions() ;
		static bool isCommandLegit(string command) ; //cuts the time of evaluating if statements after
		void updateMoves();
		bool isItemInInventory(int itemID);
		static void help();
		void printInventory(); //overwrites old function
		void addItems(int itemID); 
		int getX() ; int getY() ;
		void setLocation(int x, int y) ;
		bool gameWon() ;
};

class Keys { //only one instance will be created, same for all instances
	protected: 
		int ID ;
		string itemName ;
		static map<string, int> mapNameToItem;
		static map<int, string> mapItemToName;
		static map<string, string> mapNameToDescription;
	public:
		Keys(vector<string>names, vector<int> ids, vector<string> descriptions);
		static int NameToItem(string inputted_name) ;
		static string ItemToName(int inputted_int) ;
		static string NameToDescription(string inputted_name) ;
};

class Area {
	protected:
		int x, y ;
		string name, description ;
	public:
		void printName();
		void printDescription();
		string returnName();
		int getX() ; int getY() ;
		virtual void printItems() = 0 ;
};

class Exit : public Area {
	public:
		Exit(int inputted_x, int inputted_y, string inputted_name, string inputted_description) ;
		void printItems() ;
};

class Room : public Area {
	protected:
		vector<int> items ;
	public:
		Room(int inputted_x, int inputted_y, string inputted_name, string inputted_description, vector<int> inputted_items);
		void printItems();
		bool isItemInRoom(int itemID) ;
		void removeItems(int itemID);
};

class Hallway : public Area {
	public:
		Hallway(int inputted_x, int inputted_y, string inputted_name, string inputted_description);
		void printItems();
};

class Maps {
    private:
        void printMap0(); void printMap1();
		void printMap2(); void printMap3();
		void printMap4(); void printMap5();
		void printMap6(); void printMap7();
		void printMap8();
	public:
		void mapChecker(int x, int y) ;
};

class Anagram {
    protected:
		vector <string> wordsToUse ;
		vector <string> wordsUsed ;
		vector <string> wordsLeftToUse ;
		vector <string> listOfLettersToUse ;
		string word ;
		int attempts ;
		int score ;
		static vector<vector<string> > vectorOfWordsToUse ;
		static vector<vector<string> > listOfListOfLettersToUse ;
	public:
		Anagram(int choice) ;
		~Anagram() ;
		static void setVectors() ;
		void incrementScore() ;
		void incrementAttempts() ;
		void askInput();
		int scoreReturner() ;
		int scoreDeterminate() ;
};   

#endif