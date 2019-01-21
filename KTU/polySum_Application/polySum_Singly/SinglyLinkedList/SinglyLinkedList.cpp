#include <string>
#include <iostream>
using namespace std;

struct SinglyNode
{
	int coff;						// polynom coefficient
	int exp;						// polynom exponenet
	SinglyNode* next;				// next item in the list
};

struct SinglyLinkedList
{
	SinglyNode* head;									// pointer to the head of list

	SinglyLinkedList();									// empty list constructor
	~SinglyLinkedList();								// destructor

	bool empty() const;									// is list empty?
	void addFront(const int& e, const int& i);			// add to front of list
	void addBack(const int& e, const int& i);			// add to back of list
	void removeFront();									// remove front item of list
	void removeBack();									// remove back item of list
	void print();

	SinglyLinkedList* addPolynoms(SinglyLinkedList* list2);
};

SinglyLinkedList::SinglyLinkedList()							// constructor
{
	head = NULL;
}

SinglyLinkedList::~SinglyLinkedList()							// destructor
{
	while (!empty()) removeFront();
}

bool SinglyLinkedList::empty() const							// is list empty?
{
	return head == NULL;
}

void SinglyLinkedList::addFront(const int& e, const int& i)	// add to front of list
{
	SinglyNode* v = new SinglyNode;								// create new node
	v->coff = e;												// store data
	v->exp = i;
	v->next = head;												// head now follows v
	head = v;													// v is now the head
}

void SinglyLinkedList::removeFront()							// remove front item
{
	SinglyNode* old = head;										// save current head
	head = old->next;											// skip over old head
	delete old;													// delete the old head
}

void SinglyLinkedList::addBack(const int& e, const int& i)
{
	SinglyNode* v = new SinglyNode;
	v->coff = e;
	v->exp = i;
	v->next = NULL;

	if (head == NULL) head = v;
	else
	{
		SinglyNode* first = head;
		while (first->next != NULL) first = first->next;
		first->next = v;
	}
}

void SinglyLinkedList::removeBack()
{
	if (head == NULL)
	{
		cout << "List is empty !" << endl;
		return;
	}

	SinglyNode* last = head;
	SinglyNode* prev = head;

	while (last->next != NULL)
	{
		prev = last;
		last = last->next;
	}

	prev->next = NULL;
	if (last == head) head = NULL;
	delete last;	
}

void SinglyLinkedList::print()
{
	if (empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	SinglyNode* first = head;
	while (first != NULL)
	{
		if (first->exp == 0) cout << first->coff << "  ";
		else
		if (first->coff == 0) cout << first->exp << "  ";
		else
		if (first->coff == 1) cout << "x^" << first->exp << "  ";
		else
			cout << first->coff << "x^" << first->exp << "  ";

		first = first->next;
	}
}

SinglyLinkedList* SinglyLinkedList::addPolynoms(SinglyLinkedList* list2)
{
	SinglyLinkedList* sumList = new SinglyLinkedList();

	SinglyNode* plist1 = this->head;
	SinglyNode* plist2 = list2->head;

	while ((plist1 != NULL) || (plist2 == NULL)) {

		if (plist1->exp == plist2->exp) {
			
		}

		if (plist1 == NULL) {

			while (plist2 != NULL) {
				sumList->addBack(plist2->coff, plist2->exp);
				plist2 = plist2->next;
			}

			return sumList;
		}

		if (plist2 == NULL) {

			while (plist1 != NULL) {
				sumList->addBack(plist1->coff, plist2->exp);
				plist1 = plist1->next;
			}
		}
	}

	return sumList;	
}

void main()
{
	SinglyLinkedList* list1 = new SinglyLinkedList();
	SinglyLinkedList* list2 = new SinglyLinkedList();

	FILE* f = fopen("polynoms.txt", "r");

	int coff = 0;
	int exp = 0;

	while (true)
	{
		fscanf(f, "%d", &coff);
		fscanf(f, "%d", &exp);

		if (coff != -1) list1->addBack(coff, exp);
		else
			break;
	}

	cout << endl;

	cout << "Polinom 1 : ";
	list1->print();

	cout << endl;

	while (true)
	{
		fscanf(f, "%d", &coff);
		fscanf(f, "%d", &exp);

		if (coff != -1) list2->addBack(coff, exp);
		else
			break;
	}

	cout << "Polinom 2 : ";
	list2->print();

	cout << endl;

	SinglyLinkedList* polySum = list1->addPolynoms(list2);
	cout << "polySum   : ";
	polySum->print();

	::getchar();
}
