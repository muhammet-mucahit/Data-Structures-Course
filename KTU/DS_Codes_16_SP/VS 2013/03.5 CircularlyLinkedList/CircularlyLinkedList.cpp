#include <string>
#include <iostream>
using namespace std;

struct CircularlyNode
{
	string elem;								// element name
	int score;									// element score
	CircularlyNode* next;						// next item in the list
};

struct CircularlyLinkedList						// a circularly linked list
{
	CircularlyNode* cursor;						// the cursor

	CircularlyLinkedList();						// constructor
	~CircularlyLinkedList();					// destructor

	bool empty() const;							// is list empty?
	int size() const;
	const string& front() const;				// element following cursor
	const string& back() const;					// element at cursor
	void advance();								// advance cursor
	void add(const string& e, const int& i);	// add after cursor
	void remove();								// remove node after cursor
	void print();

	void insertOrdered(const string& e, const int& i) ;
	void removeOrdered(const string& e, const int& i) ;
};


CircularlyLinkedList::CircularlyLinkedList()	// constructor
{
	cursor = NULL;
}

CircularlyLinkedList::~CircularlyLinkedList()	// destructor
{
	while (!empty()) remove();
}

bool CircularlyLinkedList::empty() const		// is list empty?
{
	return cursor == NULL;
}

void CircularlyLinkedList::add(const string& e, const int& i)
{																	// add after cursor
	CircularlyNode* v	= new CircularlyNode;						// create a new node
	v->elem				= e;
	v->score			= i;

	if (cursor == NULL)
	{																// list is empty?
		v->next		= v;											// v points to itself
		cursor		= v;											// cursor points to v
	}
	else
	{																// list is nonempty?
		v->next			= cursor->next;								// link in v after cursor
		cursor->next	= v;
	}
}

void CircularlyLinkedList::remove()
{
	if (empty())
	{
		cout << "List is empty ! " << endl;
		return;
	};
																	// remove node after cursor
	CircularlyNode* old = cursor->next;								// the node being removed

	if (old == cursor) 												// removing the only node?
		cursor = NULL;												// list is now empty
	else
		cursor->next = old->next;									// link out the old node

	delete old;														// delete the old node
}

void CircularlyLinkedList::advance()								// advance cursor
{
	cursor = cursor->next;
}

const string& CircularlyLinkedList::back() const					// element at cursor
{
	return cursor->elem;
}

const string& CircularlyLinkedList::front() const					// element following cursor
{
	return cursor->next->elem;
}

void CircularlyLinkedList::print()
{
	if (empty())
	{
		cout << "List is empty ! " << endl;
		return;
	};

	// Cursor son elemana (rear) işaret ettiğinden
	// ilk elemandan itibaren listelemesi için first = cursor->next yapıldı.
	CircularlyNode* first = cursor->next;

	while (!(first == cursor))
	{
		cout << first->elem << "\t" << first->score << endl;
		first = first->next;
	}

	// son elemanı da listele
	cout << first->elem << "\t" << first->score << endl;
}

void CircularlyLinkedList::insertOrdered(const string& e, const int& i)
{
	add(e,i);

	// Listede sadece 1 eleman var.
	if(cursor->next == cursor) return;

	// listenin başına mı eklenecek? (2. elemandan küçük mü?)
	if( i < cursor->next->next->score)
	{
		return;
	}

	// listenin sonuna mı eklenecek?
	if( i > cursor->score)
	{
		cursor = cursor->next;
		return;
	}

	CircularlyNode* newNode = cursor->next;
	CircularlyNode* front	= newNode->next;
	CircularlyNode* back	= NULL;

	while( (newNode->score > front->score) )
	{
		back = front;
		front = front->next;
	}

	// cursor->next newNode'a işaret ediyor.
	// newNode'u yerleştirmeden önce cursor->next'i ondan sonrakine işaret ettir.
	cursor->next	= cursor->next->next;		// veya newNode->next
	back->next		= newNode;
	newNode->next	= front;
}

void CircularlyLinkedList::removeOrdered(const string& e, const int& i)
{
	CircularlyNode* current		= cursor;
	CircularlyNode* previous	= cursor;

	if (empty())
	{
		cout << "List is empty ! " << endl;
		return;
	};

	// Kalan son eleman mı silinecek?
	if( cursor->next == cursor )
	{
		delete cursor;
		cursor = NULL;
		return;
	}

	// Listenin ilk elemanı mı silinecek?
	if( (cursor->next->elem == e) && (cursor->next->score == i) )
	{
		current = current->next;
		cursor->next = cursor->next->next;
		delete current;
		return;
	}

	current = current->next;
	while (current != cursor)
	{
		if( (current->elem == e) && (current->score == i) )
		{
			previous->next = current->next;
			delete current;
			return;
		}

		previous	= current;
		current		= current->next;
	}

	// Son eleman mı silinecek ?
	if( (current->elem == e) && (current->score == i) )
	{
		previous->next = current->next;
		delete current;
		cursor = previous;	// Yeni son eleman artık önceki
	}
	else cout << "\n" << e << " is not found" << endl;
}

int main()
{
	CircularlyLinkedList list;

	list.insertOrdered("Paul", 720);
	list.insertOrdered("Rose", 590);
	list.insertOrdered("Anna", 660);	
	list.insertOrdered("Mike", 1105);
	list.insertOrdered("Rob",  750);
	list.insertOrdered("Jack", 510);
	list.insertOrdered("Jill", 740);
	
	cout << "List after insertions :" << endl;
	list.print();

	//list.removeOrdered("Adam", 610);	// Bu eleman listede yok !

	//list.removeOrdered("Jack", 510);
	//list.removeOrdered("Mike", 1105);
	//list.removeOrdered("Paul", 720);

	//cout << "\nList after removals (Jack, Mike, Paul) :" << endl;
	//list.print();

	//list.removeOrdered("Rose", 590);
	//list.removeOrdered("Rob",  750);
	//list.removeOrdered("Anna", 660);
	//list.removeOrdered("Jill", 740);

	//cout << "\nList after removals (Rose, Rob, Anna, Jill ) :" << endl;
	//list.print();

	//list.removeOrdered("Adam", 610);	// Liste boş !

	::getchar();
}
