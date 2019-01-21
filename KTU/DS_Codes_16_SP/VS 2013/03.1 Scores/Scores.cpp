#include <iostream>
#include <string>
using namespace std;

struct GameEntry										// a game score entry
{ 
	string getName() const								// get player name
	{ return name; }

	int getScore() const								// get score
	{ return score; }

	string name;										// player’s name
	int score;											// player’s score
};

struct Scores											// stores game high scores
{ 
	void add(const GameEntry& e);						// add a game entry
	GameEntry remove(int i);							// remove the ith entry
	void print();										// biz ekledik
	Scores::Scores();
	int maxEntries;										// maximum number of entries
	int numEntries;										// actual number of entries
GameEntry* entries;
};

Scores::Scores()										// constructor
{
	
	maxEntries = 10;									// maximum number of entries
	numEntries = 0;										// actual number of entries

	entries = new GameEntry[maxEntries];				// array of game entries
}

void Scores::add(const GameEntry& e)								// add a game entry
{ 
	int newScore = e.getScore();									// score to add
	if (numEntries == maxEntries)									// the array is full
	{ 
		if (newScore <= entries[maxEntries-1].getScore()) return;	// not high enough - ignore
	}
	else numEntries++;												// if not full, one more entry

	int i = numEntries-2;											// start with the next to last
	while ( i >= 0 && newScore > entries[i].getScore() ) 
	{ 
		entries[i+1] = entries[i];									// shift right if smaller
		i--;
	}
	entries[i+1] = e;												// put e in the empty spot
}

GameEntry Scores::remove(int i) 
{ 
	if ((i < 0) || (i >= numEntries))	cout<< "invalid index !!!";

	GameEntry e = entries[i];										// save the removed object
	for (int j = i+1; j < numEntries; j++)
		entries[j-1] = entries[j];									// shift entries left

	numEntries--;													// one fewer entry
	return e;														// return the removed object
}

void Scores::print() 
{ 
	for(int i=0; i<numEntries; i++)
		cout << entries[i].getName() << "\t" << entries[i].getScore() << endl;
}

void main()
{
	Scores skorlar;

	GameEntry entry0;
	entry0.name = "Anna";
	entry0.score = 660;
	skorlar.add(entry0);

	GameEntry entry1;
	entry1.name = "Rob";
	entry1.score = 750;
	skorlar.add(entry1);

	GameEntry entry2;
	entry2.name = "Jack";
	entry2.score = 510;
	skorlar.add(entry2);

	GameEntry entry3;
	entry3.name = "Mike";
	entry3.score = 1105;
	skorlar.add(entry3);

	GameEntry entry4;
	entry4.name = "Rose";
	entry4.score = 590;
	skorlar.add(entry4);

	GameEntry entry5;
	entry5.name = "Paul";
	entry5.score = 720;
	skorlar.add(entry5);

	skorlar.print();

	::getchar();
}