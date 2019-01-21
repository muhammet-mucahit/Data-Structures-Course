#include <iostream>
using namespace std;
#include <list>

struct ListPriorityQueue
{
	std::list<int> L;										// priority queue contents

	int size() const;										// number of elements
	bool empty() const;										// is the queue empty?
	void insert(const int& e);								// insert element
	const int& min() const;									// minimum element
	void removeMin();										// remove minimum
	bool isLess(const int& e, const int& f) const;			// less-than comparator
	void print();
};

int ListPriorityQueue::size() const
{
	return L.size();
}

bool ListPriorityQueue::empty() const
{
	return L.empty();
}

const int& ListPriorityQueue::min() const
{
	return L.front();										// minimum is at the front
}

bool ListPriorityQueue::isLess(const int& e, const int& f) const
{
	if(e<f) return true;
	else return false;
}

void ListPriorityQueue::insert(const int& e)
{
	std::list<int>::iterator p;
	p = L.begin();
	while (p != L.end() && !isLess(e, *p)) ++p;				// find larger element
	L.insert(p, e);											// insert e before p
}

void ListPriorityQueue::removeMin()
{
	L.pop_front();
}

void ListPriorityQueue::print()
{
	std::list<int>::iterator p;
	p = L.begin();

	while (p != L.end())
	{
		cout << *p << " ";
		p++;
	}
}

int main()
{
	ListPriorityQueue PriorityQueue;

	cout <<"Inserting Three Priority Queue Elements (3,2,1) ! " << endl;
	PriorityQueue.insert(3);
	PriorityQueue.insert(2);
	PriorityQueue.insert(1);

	cout << endl <<"Priority Queue Elements : ";
	PriorityQueue.print();

	cout << endl << endl <<"Min = " << PriorityQueue.min() << endl;

	cout << endl <<"Removing Minimum Element ! " << endl;
	PriorityQueue.removeMin();

	cout << endl <<"Min = " << PriorityQueue.min() << endl;

	cout << endl <<"Inserting Two Priority Queue Elements (1,4) ! " << endl;
	PriorityQueue.insert(1);
	PriorityQueue.insert(4);

	cout << endl <<"Priority Queue Elements : ";
	PriorityQueue.print();

	cout << endl << endl <<"Min = " << PriorityQueue.min() << endl;

	cout << endl <<"Removing Minimum Element ! " << endl;
	PriorityQueue.removeMin();

	cout << endl <<"Min = " << PriorityQueue.min() << endl;

	cout << endl <<"Priority Queue Elements : ";
	PriorityQueue.print();

	::getchar();
}
