#include <string>
#include <iostream>
using namespace std;

struct CircularlyNode
{
	string elem;							// element value
	CircularlyNode* next;					// next item in the list
};


struct CircularlyLinkedList					// a circularly linked list
{
	CircularlyNode* cursor;					// the cursor

	CircularlyLinkedList();					// constructor
	~CircularlyLinkedList();				// destructor
	bool empty() const;						// is list empty?
	const string& front() const;			// element following cursor
	const string& back() const;				// element at cursor
	void advance();							// advance cursor
	void add(const string& e);				// add after cursor
	void remove();							// remove node after cursor
	void print();
};



bool CircularlyLinkedList::empty() const				// is list empty?
{
	return cursor == NULL;
}

const string& CircularlyLinkedList::back() const		// element at cursor
{
	return cursor->elem;
}

const string& CircularlyLinkedList::front() const		// element following cursor
{
	return cursor->next->elem;
}

void CircularlyLinkedList::advance()					// advance cursor
{
	cursor = cursor->next;
}

void CircularlyLinkedList::remove()
{														// remove node after cursor
	CircularlyNode* old = cursor->next;					// the node being removed

	if (old == cursor) 									// removing the only node?
		cursor = NULL;									// list is now empty
	else
		cursor->next = old->next;						// link out the old node

	delete old;											// delete the old node
}

CircularlyLinkedList::CircularlyLinkedList()			// constructor
{ 
	cursor = NULL;
}

CircularlyLinkedList::~CircularlyLinkedList()			// destructor
{
	while (!empty()) remove();
}

void CircularlyLinkedList::add(const string& e)
{														// add after cursor
	CircularlyNode* v = new CircularlyNode;				// create a new node
	v->elem = e;

	if (cursor == NULL)
	{													// list is empty?
		v->next		= v;								// v points to itself
		cursor		= v;								// cursor points to v
	}
	else
	{													// list is nonempty?
		v->next			= cursor->next;					// link in v after cursor
		cursor->next	= v;
	}
}


void CircularlyLinkedList::print()
{
	if (empty())
	{
		cout << " List is empty ! " << endl;
		return;
	};

	// Cursor son eklenen elemana (rear) işaret ettiğinden
	// kuyruğun ilk elemanından itibaren listelemesi için first = cursor->next yapıldı.
	CircularlyNode* first = cursor->next;

	while (!(first == cursor))
	{
		cout << first->elem << endl;
		first = first->next;
	}

	// son elemanı da listele
	cout << cursor->elem << endl;
}

struct CircularlyLinkedQueue
{
	CircularlyLinkedList C;
	int n;

	CircularlyLinkedQueue();
	int size() const;
	bool empty() const;
	const string& front();
	void enqueue(const string& e);
	void dequeue();
};


CircularlyLinkedQueue::CircularlyLinkedQueue()		// constructor
: C(), n(0)
{
}

int CircularlyLinkedQueue::size() const				// number of items in the queue
{
	return n;
}

bool CircularlyLinkedQueue::empty() const			// is the queue empty?
{
	return n == 0;
}

// get the front element
const string& CircularlyLinkedQueue::front()
{
	if (empty())
	{
		cout << "front of empty queue !"<<endl;
		return "-1";
	}

	return C.front();								// list front is queue front
}

void CircularlyLinkedQueue::enqueue(const string& e)
{
	C.add(e);										// insert after cursor
	C.advance();									// ... and advance
	n++;
}

void CircularlyLinkedQueue::dequeue()
{
	if (empty())
	{
		cout << "dequeuing of empty queue !" << endl;
		return;
	}

	C.remove();										// remove from list front
	n--;
}


int main()
{
	// Queue (kuyruk) FIFO (First In First Out) mantığına göre çalışır.
	// Ekleme kuyruk sonuna (rear), silme kuyruk başından (front) yapılır.

	CircularlyLinkedQueue Queue;

	cout << "Adding some elements to Circularyl Linked Queue :\n";
	Queue.enqueue("Omer");
	Queue.enqueue("Oguzhan");
	Queue.enqueue("Fatih");
	Queue.enqueue("Ali Osman");
	Queue.C.print();

	cout <<"\n";
	cout << "Remove one element from Circularyl Linked Queue :\n";
	Queue.dequeue();
	Queue.C.print();

	cout <<"\n";
	cout << "Add one element to Circularyl Linked Queue :\n";
	Queue.enqueue("Omer");
	Queue.C.print();

	cout <<"\n";
	cout << "Remove one element from Circularyl Linked Queue :\n";
	Queue.dequeue();
	Queue.C.print();

	cout <<"\n";
	cout << "Add one element to Circularyl Linked Queue :\n";
	Queue.enqueue("Oguzhan");
	Queue.C.print();

	::getchar();
}
