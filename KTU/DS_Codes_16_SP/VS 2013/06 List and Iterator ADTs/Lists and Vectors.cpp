#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
using namespace std; // make std:: accessible

struct DoublyNode
{
	string elem;											// element name
	int score;												// element score;
	//DoublyNode* next;										// next item in the list
	//DoublyNode* prev;										// previous item in the list
};

void printList(list<DoublyNode> stl_List)
{
	typedef list<DoublyNode>::iterator Iterator; // iterator type

	for (Iterator p = stl_List.begin(); p != stl_List.end(); ++p)
		cout << p->elem << "  " << p->score << endl;	
}

bool compare(DoublyNode a, DoublyNode b) 
{
	if (a.score < b.score) return true;
	else return false;
}

int vectorSum1(const vector<int>& V)
{
	int sum = 0;
	for (int i = 0; i < V.size(); i++)
		sum += V[i];
	return sum;
}

int vectorSum2(vector<int> V) 
{
	typedef vector<int>::iterator Iterator; // iterator type
	int sum = 0;
	for (Iterator p = V.begin(); p != V.end(); ++p)
		sum += *p;
	return sum;
}

void main()
{
	//
	// STL List Samples
	//

	DoublyNode Node;
	list<DoublyNode> stl_List;

	Node.elem = "Jack"; Node.score = 510;
	stl_List.push_back(Node);

	Node.elem = "Rose"; Node.score = 590;
	stl_List.push_back(Node);

	Node.elem = "Anna"; Node.score = 660;
	stl_List.push_back(Node);

	Node.elem = "Paul"; Node.score = 720;
	stl_List.push_back(Node);

	Node.elem = "Jill"; Node.score = 740;
	stl_List.push_back(Node);

	Node.elem = "Rob"; Node.score = 750;
	stl_List.push_back(Node);

	Node.elem = "Mike"; Node.score = 1105;
	stl_List.push_back(Node);

	printList(stl_List);

	//stl_List.pop_front();
	//stl_List.pop_back();
	//printList(stl_List);

	//list<DoublyNode>::iterator i;
	//i = stl_List.begin();
	//advance(i,3);
	//stl_List.erase(i);
	//printList(stl_List);

	//stl_List.sort(compare);
	//printList(stl_List);


	//
	// STL Vector Samples
	//

	//int a[] = { 17, 12, 33, 15, 62, 45 };
	//vector<int> v(a, a + 6);						// v: 17 12 33 15 62 45

	//cout << v.size() << endl;						// outputs: 6

	//v.pop_back();									// v: 17 12 33 15 62
	//cout << v.size() << endl;						// outputs: 5

	//v.push_back(19);								// v: 17 12 33 15 62 19
	//cout << v.front() << " " << v.back() << endl;	// outputs: 17 19

	//v.erase(v.end() - 4, v.end() - 2);				// v: 12 15 62 19
	//cout << v.size() << endl;						// outputs: 4

	//cout << "vectorSum1 = " << vectorSum1(v) << endl;
	//cout << "vectorSum2 = " << vectorSum2(v) << endl;


	//
	// STL Stack Samples
	//

	//stack<int> stl_stack;
	//stl_stack.push(1);
	//stl_stack.push(2);
	//stl_stack.push(3);
	//stl_stack.push(4);
	//stl_stack.push(5);

	//cout << stl_stack.top() << endl;

	//stl_stack.pop();
	//cout << stl_stack.top() << endl;


	//
	// STL Queue Samples
	//

	//queue<int> stl_queue;
	//stl_queue.push(1);
	//stl_queue.push(2);
	//stl_queue.push(3);
	//stl_queue.push(4);
	//stl_queue.push(5);

	//cout << "front = " << stl_queue.front() << " back = " << stl_queue.back() << endl;

	//stl_queue.pop();
	//cout << "front = " << stl_queue.front() << endl;

	//stl_queue.push(6);
	//cout << "back = " << stl_queue.back() << endl;

	getchar();

}