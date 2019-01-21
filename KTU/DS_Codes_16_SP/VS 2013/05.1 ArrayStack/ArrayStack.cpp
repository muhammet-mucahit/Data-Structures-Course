#include <iostream>
using namespace std;

struct ArrayStack
{
	enum { DEF_CAPACITY = 100 };			// default stack capacity

	ArrayStack(int cap = DEF_CAPACITY);		// constructor from capacity
	int size() const;						// number of items in the stack
	bool empty() const;						// is the stack empty?
	const int& top();						// get the top element
	void push(const int& e);				// push element onto stack
	void pop();								// pop the stack


	int* S;									// array of stack elements
	int capacity;							// stack capacity
	int t;									// index of the top of the stack
};


ArrayStack::ArrayStack(int cap)					// constructor from capacity
: S(new int[cap]), capacity(cap), t(-1)
{
}

int ArrayStack::size() const					// number of items in the stack
{
	return (t + 1);
}

bool ArrayStack::empty() const					// is the stack empty?
{
	return (t < 0);
}


const int& ArrayStack::top()					// return top of stack
{
	if (empty()) { cout<<"Stack is empty !"; return 0; }
	return S[t];
}


void ArrayStack::push(const int& e)				// push element onto the stack
{
	if (size() == capacity){ cout<<"Stack is full !"; return; }
	S[++t] = e;
}


void ArrayStack::pop()							// pop the stack
{
	if (empty()){ cout<<"Stack is empty !"; return; }
	--t;
}


int main()
{
	ArrayStack A;

	A.push(7);
	A.push(13);
	A.push(1);
	cout << A.top() << endl;

	A.pop();
	A.push(9);
	cout << A.top() << endl;

	A.pop();
	cout << A.top() << endl;

	::getchar();
}
