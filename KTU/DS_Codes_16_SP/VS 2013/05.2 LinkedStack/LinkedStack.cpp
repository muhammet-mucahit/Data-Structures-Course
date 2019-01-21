#include <iostream>
using namespace std;

struct SinglyNode
{
	int elem;								// element value
	SinglyNode* next;						// next item in the list
};


struct SinglyLinkedList
{
	SinglyNode* head;						// pointer to the head of list

	SinglyLinkedList();						// empty list constructor
	~SinglyLinkedList();					// destructor

	bool empty() const;						// is list empty?
	const int& front() const;				// get front element
	void addFront(const int& e);			// add to front of list
	void removeFront();						// remove front item list
};


void SinglyLinkedList::removeFront()
{											// remove front item
	SinglyNode* old = head;					// save current head
	head = old->next;						// skip over old head
	delete old;								// delete the old head
}

void SinglyLinkedList::addFront(const int& e)
{											// add to front of list
	SinglyNode* v = new SinglyNode;			// create new node
	v->elem = e;							// store data
	v->next = head;							// head now follows v
	head = v;								// v is now the head
}

SinglyLinkedList::SinglyLinkedList()		// constructor
{ 
	head = NULL;
}

SinglyLinkedList::~SinglyLinkedList()		// destructor
{
	while (!empty()) removeFront();
}

bool SinglyLinkedList::empty() const		// is list empty?
{
	return head == NULL;
}

const int& SinglyLinkedList::front() const	// get front element
{
	return head->elem;
}


struct LinkedStack						// stack as a linked list
{
	SinglyLinkedList S;					// linked list of elements
	int n;								// number of elements

	LinkedStack();						// constructor
	int size() const;					// number of items in the stack
	bool empty() const;					// is the stack empty?

	const int& top() const ;			// the top element
	void push(const int& e);  			// push element onto stack
	void pop() ;						// pop the stack
};


LinkedStack::LinkedStack() : S(), n(0)		// constructor
{
}

int LinkedStack::size() const				// number of items in the stack
{
	return n;
}

bool LinkedStack::empty() const				// is the stack empty?
{
	return n == 0;
}

const int& LinkedStack::top() const			// return top of stack
{
	if (empty()){ cout <<"Top of empty stack !"<<endl; return 0; }
	return S.front();
}

void LinkedStack::push(const int& e)		// push element onto the stack
{
	++n;
	S.addFront(e);
}

void LinkedStack::pop()						// pop the stack
{
	if (empty()) { cout<<"Pop from empty stack !"<<endl; return; }
	--n;
	S.removeFront();
}

int main()
{
	LinkedStack LStack;

	LStack.push(7);
	LStack.push(13);
	LStack.push(1);

	cout << "Top = " << LStack.top() << endl;

	LStack.pop();
	LStack.push(9);

	cout << "Top = " << LStack.top() << endl;

	LStack.pop();

	cout << "Top = " << LStack.top() << endl;

	::getchar();

}
