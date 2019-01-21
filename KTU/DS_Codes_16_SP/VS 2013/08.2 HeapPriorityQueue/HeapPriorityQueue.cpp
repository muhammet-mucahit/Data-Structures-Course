#include <iostream>
#include<vector>
using namespace std;

struct VectorCompleteTree
{
	typedef std::vector<int>::iterator Position;							// a position in the tree
	VectorCompleteTree() : V(1) {}											// constructor
	int size() const						{ return V.size() - 1; }
	Position left(const Position& p)		{ return pos(2*idx(p)); }
	Position right(const Position& p)		{ return pos(2*idx(p) + 1); }
	Position parent(const Position& p)		{ return pos(idx(p)/2); }
	bool hasLeft(const Position& p) const	{ return 2*idx(p) <= size(); }
	bool hasRight(const Position& p) const 	{ return 2*idx(p) + 1 <= size(); }
	bool isRoot(const Position& p) const	{ return idx(p) == 1; }
	Position root()							{ return pos(1); }
	Position last()							{ return pos(size()); }
	void addLast(const int& e)				{ V.push_back(e); }
	void removeLast()						{ V.pop_back(); }

	void swap(const Position& p, const Position& q)
  	{
		int e = *q;
		*q = *p;
		*p = e;
	}

	std::vector<int> V;								// tree contents

	Position pos(int i)								// map an index to a position
	{
		return V.begin() + i;
	}

	int idx(const Position& p) const				// map a position to an index
	{
		return p - V.begin();
	}

};

struct HeapPriorityQueue
{
	int size() const; 								// number of elements
	bool empty() const;  							// is the queue empty?
	void insert(const int& e);						// insert element
	const int& min();								// minimum element
	void removeMin();								// remove minimum
	bool isLess(const int& e, const int& f) const;
	void print();

	VectorCompleteTree T;							// priority queue contents

	typedef VectorCompleteTree::Position Position;	// shortcut for tree position
};

int HeapPriorityQueue::size() const					// number of elements
{
	return T.size();
}

bool HeapPriorityQueue::empty() const
{
	return size() == 0;
}

const int& HeapPriorityQueue::min()
{
	return *(T.root());								// return reference to root element
}

bool HeapPriorityQueue::isLess(const int& e, const int& f) const
{
	if(e<f) return true;
	else return false;
}

void HeapPriorityQueue::insert(const int& e)
{
	T.addLast(e);											// add e to heap
	Position v = T.last();									// e's position

	while (!T.isRoot(v))
	{														// up-heap bubbling
		Position u = T.parent(v);
		if (!isLess(*v, *u)) break;							// if v in order, we're done
		T.swap(v, u);										// ...else swap with parent
		v = u;
	}
}

void HeapPriorityQueue::removeMin()
{
	if (size() == 1)															// only one node?
		T.removeLast();															// ...remove it
	else
	{
		Position u = T.root();													// root position
		T.swap(u, T.last());													// swap last with root
		T.removeLast();															// ...and remove last

		while (T.hasLeft(u))													// down-heap bubbling
		{
			Position v = T.left(u);
			if (T.hasRight(u) && isLess(*(T.right(u)), *v))	v = T.right(u);		// v is u's smaller child

			if (isLess(*v, *u))													// is u out of order?
			{
				T.swap(u, v);													// ...then swap
				u = v;
			}
			else break;															// else we're done
		}
	}
}

void HeapPriorityQueue::print()
{
	std::vector<int> M = T.V;

	int i = 0;
	while (i<=T.size())
	{
		cout << M.at(i) << " ";
		i++;
	}
}


int main()
{
	HeapPriorityQueue Heap;

	Heap.insert(4);
	Heap.insert(5);
	Heap.insert(6);
	Heap.insert(15);
	Heap.insert(9);
	Heap.insert(7);
	Heap.insert(20);
	Heap.insert(16);
	Heap.insert(25);
	Heap.insert(14);
	Heap.insert(12);
	Heap.insert(11);
	Heap.insert(8);
	// Heap.insert(13);

	cout << "Heap Elements : ";
	Heap.print();

	cout << endl << endl << "Min = " << Heap.min() << endl;

	cout << endl << "Insert 2 !" << endl;
	Heap.insert(2);

	cout << endl << "Heap Elements : ";
	Heap.print();

	cout << endl << endl << "Min = " << Heap.min() << endl;

	cout << endl << "Removing Minimum Element !" << endl;
	Heap.removeMin();

	cout << endl << "Heap Elements : ";
	Heap.print();

	::getchar();
}
