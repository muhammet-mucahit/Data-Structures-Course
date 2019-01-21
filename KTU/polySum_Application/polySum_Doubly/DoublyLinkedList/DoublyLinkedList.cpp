#include <string>
#include <iostream>
using namespace std;

struct DoublyNode
{
	int coff;						// polynom coefficient
	int exp;						// polynom exponenet
	DoublyNode* next;				// next item in the list
	DoublyNode* prev;				// previous item in the list
};

struct DoublyLinkedList
{
	DoublyNode* header;										// pointer to the header of list
	DoublyNode* trailer;									// pointer to the trailer of list

	DoublyLinkedList();										// empty list constructor
	~DoublyLinkedList();									// destructor

	bool empty() const;										// is list empty?
	void addFront(const int& c, const int& e);				// add to front of list
	void addBack(const int& c, const int& e);				// add to back of list
	void removeFront();										// remove front item list
	void removeBack();										// remove from back
	void printH2T();

	void add(DoublyNode* v, const int& c, const int& e);	// insert new node before v
	void remove(DoublyNode* v);								// remove node v

	DoublyLinkedList* addPolynoms(DoublyLinkedList* list2);
};


DoublyLinkedList::DoublyLinkedList()				// constructor
{
	header			= new DoublyNode;				// create sentinels
	trailer			= new DoublyNode;
	header->next	= trailer;						// have them point to each other
	trailer->prev	= header;
}

DoublyLinkedList::~DoublyLinkedList()				// destructor
{
	while (!empty()) removeFront();					// remove all but sentinels
	delete header;									// remove the sentinels
	delete trailer;
}

bool DoublyLinkedList::empty() const				// is list empty?
{
	return (header->next == trailer);
}

void DoublyLinkedList::addFront(const int& c, const int& e)		// add to front of list
{
	add(header->next, c, e);
}

void DoublyLinkedList::addBack(const int& c, const int& e)		// add to back of list
{
	add(trailer, c, e);
}

void DoublyLinkedList::add(DoublyNode* v, const int& c, const int& e)	// insert new node before v
{
	DoublyNode* u = new DoublyNode;				// create a new node for e
	u->coff = c;
	u->exp = e;

	u->next = v;								// link u in between v
	u->prev = v->prev;							// ...and v->prev   

	v->prev->next = u;							// correct code should be
	v->prev = u;								// like this
}

void DoublyLinkedList::removeFront()				// remove from font
{
	remove(header->next);
}

void DoublyLinkedList::removeBack()					// remove from back
{
	remove(trailer->prev);
}

void DoublyLinkedList::remove(DoublyNode* v)
{													// remove node v
	DoublyNode* u	= v->prev;						// predecessor
	DoublyNode* w	= v->next;						// successor
	u->next			= w;							// unlink v from list
	w->prev			= u;
	delete v;
}

void DoublyLinkedList::printH2T()
{
	if (empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	DoublyNode* first = header;
	while (!(first->next == trailer))
	{
		if (first->next->exp == 0) cout << first->next->coff << "  ";
		else
		if (first->next->coff == 0) cout << first->next->exp << "  ";
		else
		if (first->next->coff == 1) cout << "x^" << first->next->exp << "  ";
		else
			cout << first->next->coff << "x^" << first->next->exp << "  ";

		first = first->next;
	}
}

DoublyLinkedList* DoublyLinkedList::addPolynoms(DoublyLinkedList* list2)
{
	DoublyLinkedList* sumList = new DoublyLinkedList();

	DoublyNode* plist1 = this->header->next;
	DoublyNode* plist2 = list2->header->next;

	return sumList;
}

void main()
{
	DoublyLinkedList* list1 = new DoublyLinkedList();
	DoublyLinkedList* list2 = new DoublyLinkedList();

	FILE* f = fopen("polynoms.txt", "r");

	int coff = 0;
	int exp = 0;
	fscanf(f, "%d", &coff);
	fscanf(f, "%d", &exp);
	list1->addBack(coff, exp);

	while (coff != -1)
	{
		fscanf(f, "%d", &coff);
		fscanf(f, "%d", &exp);
		list1->addBack(coff, exp);
	}

	cout << endl;

	list1->removeBack();
	cout << "Polinom 1 : ";
	list1->printH2T();

	cout << endl;

	fscanf(f, "%d", &coff);
	fscanf(f, "%d", &exp);
	list2->addBack(coff, exp);

	while (coff != -1)
	{
		fscanf(f, "%d", &coff);
		fscanf(f, "%d", &exp);
		list2->addBack(coff, exp);
	}

	list2->removeBack();
	cout << "Polinom 2 : ";
	list2->printH2T();

	cout << endl;

	DoublyLinkedList* polySum = list1->addPolynoms(list2);
	cout << "polySum   : ";
	polySum->printH2T();

	::getchar();
}
