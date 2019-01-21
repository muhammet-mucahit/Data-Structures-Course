#include <string>
#include <iostream>
using namespace std;

struct SinglyNode 
{
	string elem;										// element name
	int score;											// element score
	SinglyNode* next;									// next item in the list
};

struct SinglyLinkedList
{
	SinglyNode* head;									// pointer to the head of list

	SinglyLinkedList();									// empty list constructor
	~SinglyLinkedList();								// destructor

	bool empty() const;									// is list empty?
	const string& front() const;						// get front element
	void addFront(const string& e, const int& i);		// add to front of list
	void addBack(const string& e, const int& i);		// add to back of list
	void removeFront();									// remove front item of list
	void removeBack();									// remove back item of list
	void print();

	void insertOrdered(const string& e, const int& i) ;
	void removeOrdered(const string& e, const int& i) ;

	SinglyLinkedList* mergeLists(SinglyLinkedList* list2) ;
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

const string& SinglyLinkedList::front() const					// get front element
{
	return head->elem;
}

void SinglyLinkedList::addFront(const string& e, const int& i)	// add to front of list
{
	SinglyNode* v	= new SinglyNode;							// create new node
	v->elem			= e;										// store data
	v->score		= i;
	v->next			= head;										// head now follows v
	head			= v;										// v is now the head
}

void SinglyLinkedList::removeFront()							// remove front item
{
	SinglyNode* old		= head;									// save current head
	head				= old->next;							// skip over old head
	delete old;													// delete the old head
}

void SinglyLinkedList::addBack(const string& e, const int& i)
{
	SinglyNode* v = new SinglyNode;
	v->elem = e;
	v->score = i;
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
	if(empty())
	{
		cout << "List is empty !" << endl;
		return;
	}

	SinglyNode* first = head;
	while (first != NULL)
	{
		cout << first->elem << "\t" << first->score << endl;
		first = first->next;
	}
}

void SinglyLinkedList::insertOrdered(const string& e, const int& i)
{
	SinglyNode* newNode		= new SinglyNode;
	newNode->elem			= e;
	newNode->score			= i;
	newNode->next			= NULL;

	// Liste boş mu?
	if(head == NULL)
	{
		head = newNode;
		return;
	}

	// newNode listenin başına mı eklenecek?
	if(newNode->score < head->score)
	{
		newNode->next	= head;
		head			= newNode;
		return;
	}

	// Liste boş değil ve (newNode->score > head->score)
	SinglyNode* current	= head;
	while (current->next != NULL)
	{
		if(newNode->score >= current->next->score)
			current	= current->next;
		else
			break;
	}

	newNode->next	= current->next;
	current->next	= newNode;
}

void SinglyLinkedList::removeOrdered(const string& e, const int& i)
{
	SinglyNode* current		= head;
	SinglyNode* previous	= head;		// Liste tek yönlü olduğundan silerken previous gerekli

	// Liste boş mu?
	if(head == NULL)
	{
		cout << "List is empty !" << endl;
		return;
	}

	// Listenin ilk elemanı mı silinecek?
	if( (current->elem == e) && (current->score == i) )
	{
		head = current->next;
		delete current;
		return;
	}

	// Head'in işaret ettiğinden sonraki elemanlardan biri, belki de en son eleman silinecek
	current = current->next;
	while (current != NULL)
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

	if(current == NULL) cout << "\n" << e << " is not found" << endl;
}

SinglyLinkedList* SinglyLinkedList::mergeLists(SinglyLinkedList* list2)
{
	SinglyLinkedList* mergedList = new SinglyLinkedList();

	SinglyNode* plist1 = this->head;
	SinglyNode* plist2 = list2->head;

	while ((plist1 != NULL) || (plist2 != NULL))
	{
		if (plist1 == NULL)
		{
			while (plist2 != NULL)
			{
				mergedList->addBack(plist2->elem, plist2->score);
				plist2 = plist2->next;
			}

			return mergedList;
		}

		if (plist2 == NULL)
		{
			while (plist1 != NULL)
			{
				mergedList->addBack(plist1->elem, plist1->score);
				plist1 = plist1->next;
			}

			return mergedList;
		}

		if (plist1->score <= plist2->score)
		{
			mergedList->addBack(plist1->elem, plist1->score);
			plist1 = plist1->next;
		}
		else
		{
			mergedList->addBack(plist2->elem, plist2->score);
			plist2 = plist2->next;
		}
	}
}

int main()
{
	SinglyLinkedList list;

	list.addFront("Omer", 1000);
	list.addFront("Oguzhan", 1500);
	list.addFront("Fatih", 1250);
	list.print();

	cout << endl;
	list.removeFront();
	list.print();

	cout << endl;
	list.removeFront();
	list.print();

	cout << endl;
	list.removeFront();
	list.print();

	//SinglyLinkedList list;
	//	
	//list.insertOrdered("Paul", 720);
	//list.insertOrdered("Rose", 590);
	//list.insertOrdered("Anna", 660);	
	//list.insertOrdered("Mike", 1105);
	//list.insertOrdered("Rob",  750);
	//list.insertOrdered("Jack", 510);
	//list.insertOrdered("Jill", 740);

	//cout << "List after insertions :" << endl;
	//list.print();

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


	//SinglyLinkedList* list1 = new SinglyLinkedList();
	//list1->insertOrdered("Mike", 1105);
	//list1->insertOrdered("Rob", 750);
	//list1->insertOrdered("Paul", 720);
	//list1->insertOrdered("Anna", 660);
	//cout << "list1 : " << endl;
	//list1->print();
	//cout << endl;

	//SinglyLinkedList* list2 = new SinglyLinkedList();
	//list2->insertOrdered("Rose", 590);
	//list2->insertOrdered("Jack", 510);
	//list2->insertOrdered("Jill", 740);
	//list2->insertOrdered("Adam", 610);
	//cout << "list2 : " << endl;
	//list2->print();
	//cout << endl;

	//SinglyLinkedList* mergedList = list1->mergeLists(list2);

	//cout << "Merged list :" << endl;
	//mergedList->print();

	::getchar();
}
