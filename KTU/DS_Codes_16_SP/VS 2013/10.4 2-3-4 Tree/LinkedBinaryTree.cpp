#include <string>					
#include <iostream>					
using namespace std;

struct DoublyNode
{						
	int score;												// element score;
	DoublyNode* next;										// next item in the list
	DoublyNode* prev;										// previous item in the list

	friend struct DoublyLinkedList;
	DoublyLinkedList* down;
};

struct DoublyLinkedList
{
	DoublyNode* header;										// pointer to the header of list
	DoublyNode* trailer;									// pointer to the trailer of list
	DoublyNode* up;
	int n;

	DoublyLinkedList();										// empty list constructor
	int size();

	void insertOrdered(const int& i) ;
};

struct LinkedBinaryTree
{
	DoublyLinkedList* root;									// pointer to the root
	int n;													// number of nodes

	LinkedBinaryTree();										// constructor
	int size() const;										// returns number of nodes
	bool empty() const;										// is tree empty?

	void insert(int e);			
	void remove(DoublyNode* p, int e);						// Eklenecek ...

	void inorder(DoublyLinkedList* v) const;				// inorder utility
};

DoublyLinkedList::DoublyLinkedList()						// constructor
{													
	header			= new DoublyNode;						// create sentinels
	trailer			= new DoublyNode;
	header->score	= 0;
	trailer->score	= 0;

	DoublyNode* Node = new DoublyNode;
	Node->down = NULL;

	Node->prev = header;
	Node->next = trailer;

	header->next	= Node;						
	trailer->prev	= Node;

	up = NULL;

	n = 0;
}

void DoublyLinkedList::insertOrdered(const int& i) 
{	
	DoublyNode* newNode		= new DoublyNode;		
	newNode->score			= i;

	DoublyNode* newPointer	= new DoublyNode;
	newPointer->down = NULL;

	// Liste boþ mu?
	if(header->next->next == trailer) 
	{		
		newNode->next		= newPointer;
		newNode->prev		= header->next;	

		header->next->next	= newNode;
		trailer->prev		= newPointer;

		newPointer->prev	= newNode;
		newPointer->next	= trailer;

		n++;
		return; 
	}

	// newNode listenin baþýna mý eklenecek?
	if(newNode->score < header->next->next->score) 
	{ 
		newPointer->next	= newNode;
		newNode->prev		= newPointer;

		newNode->next		= header->next;
		header->next->prev	= newNode;

		header->next		= newPointer;
		newPointer->prev	= header;

		n++;
		return;
	}

	// Liste boþ deðil ve (newNode->score > header->score)
	DoublyNode* current	= header->next->next;
	while (current != trailer)
	{
		if(newNode->score >= current->score) 
			current = current->next->next;
		else 
			break;		
	}

	newNode->next			= newPointer;
	newPointer->prev		= newNode;

	current->prev->next		= newNode;
	newNode->prev			= current->prev;

	newPointer->next		= current;
	current->prev			= newPointer;

	n++;
}

int DoublyLinkedList::size()
{
	return n;
}

void LinkedBinaryTree::insert(int i)			
{ 
	DoublyLinkedList* p;

	if(root == NULL)
	{
		root = new DoublyLinkedList;
		root->insertOrdered(i);
		return;
	}
	else
	{
		p = root;
		DoublyLinkedList* parent = NULL;

		while(true)
		{
			// Eðer düðümde 3 eleman varsa
			if(p->size() == 3)
			{
 				if(p->up == NULL) // root'u parçala
				{
					DoublyLinkedList* pUp = new DoublyLinkedList;
					pUp->insertOrdered(p->header->next->next->next->next->score);

					DoublyLinkedList* pLeft = new DoublyLinkedList;
					pLeft->insertOrdered(p->header->next->next->score);

					DoublyLinkedList* pRight = new DoublyLinkedList;
					pRight->insertOrdered(p->header->next->next->next->next->next->next->score);

					root = pUp;

					pUp->header->next->down								= pLeft;
					pLeft->up											= pUp->header->next;

					pLeft->header->next->down							= p->header->next->down;
					if(pLeft->header->next->down != NULL)				pLeft->header->next->down->up				= pLeft->header->next;

					pLeft->header->next->next->next->down				= p->header->next->next->next->down;
					if(pLeft->header->next->next->next->down != NULL)	pLeft->header->next->next->next->down->up	= pLeft->header->next->next->next;


					pUp->header->next->next->next->down					= pRight;
					pRight->up											= pUp->header->next->next->next;

					pRight->header->next->down							= p->header->next->next->next->next->next->down;
					if(pRight->header->next->down != NULL)				pRight->header->next->down->up				= pRight->header->next;

					pRight->header->next->next->next->down				= p->header->next->next->next->next->next->next->next->down;
					if(pRight->header->next->next->next->down != NULL)	pRight->header->next->next->next->down->up	= pRight->header->next->next->next;

					parent = p;
					DoublyLinkedList* temp = p;
					if(i < pUp->header->next->next->score)
						p = pLeft;
					else
						p = pRight;

					delete temp;
				}
				else
				{
					// 3'lüyü parçalarken yukarý çýkacak elemaný, 1 veya 2 elemanlý düðüme ekle
					DoublyNode* pointerUp = p->up;

					// prev = header mý? Yani düðüm baþýna mý eklenecek? 
					if(pointerUp->prev->score == 0) 
					{
						DoublyNode* pUp			= new DoublyNode;
						pUp->score				= p->header->next->next->next->next->score;
						pUp->next				= pointerUp;
						pUp->prev				= new DoublyNode;
						pUp->prev->next			= pUp;
						pUp->prev->prev			= pointerUp->prev;
						pointerUp->prev->next	= pUp->prev;
						pointerUp->prev			= pUp;

						DoublyLinkedList* pLeft = new DoublyLinkedList;
						pLeft->insertOrdered(p->header->next->next->score);

						DoublyLinkedList* pRight = new DoublyLinkedList;
						pRight->insertOrdered(p->header->next->next->next->next->next->next->score);

						pUp->prev->down										= pLeft;
						pLeft->up											= pUp->prev;

						pLeft->header->next->down							= p->header->next->down;
						if(pLeft->header->next->down != NULL)				pLeft->header->next->down->up = pLeft->header->next;

						pLeft->header->next->next->next->down				= p->header->next->next->next->down;
						if(pLeft->header->next->next->next->down != NULL)	pLeft->header->next->next->next->down->up = pLeft->header->next->next->next;


						pUp->next->down										= pRight;
						pRight->up											= pUp->next;

						pRight->header->next->down							= p->header->next->next->next->next->next->down;
						if(pRight->header->next->down != NULL)				pRight->header->next->down->up = pRight->header->next;

						pRight->header->next->next->next->down				= p->header->next->next->next->next->next->next->next->down;
						if(pRight->header->next->next->next->down != NULL)	pRight->header->next->next->next->down->up = pRight->header->next->next->next;

						parent->n++;
						if( (parent != NULL) && (parent->up == NULL) ) root = parent;

						parent = p;
						DoublyLinkedList* temp = p;
						if(i < pUp->score)
							p = pLeft;
						else
							p = pRight;

						delete temp;					
					}
					else 
					{
						// Düðümde ortaya veya sona mý eklenecek? 
						DoublyNode* pUp			= new DoublyNode;
						pUp->score				= p->header->next->next->next->next->score;
						pUp->next				= new DoublyNode;
						pUp->prev				= pointerUp;
						pUp->next->next			= pointerUp->next;
						pUp->next->prev			= pUp;
						pointerUp->next->prev	= pUp->next;
						pointerUp->next			= pUp;

						DoublyLinkedList* pLeft = new DoublyLinkedList;
						pLeft->insertOrdered(p->header->next->next->score);

						DoublyLinkedList* pRight = new DoublyLinkedList;
						pRight->insertOrdered(p->header->next->next->next->next->next->next->score);

						pUp->prev->down										= pLeft;
						pLeft->up											= pUp->prev;

						pLeft->header->next->down							= p->header->next->down;
						if(pLeft->header->next->down != NULL)				pLeft->header->next->down->up = pLeft->header->next;

						pLeft->header->next->next->next->down				= p->header->next->next->next->down;
						if(pLeft->header->next->next->next->down != NULL)	pLeft->header->next->next->next->down->up = pLeft->header->next->next->next;


						pUp->next->down										= pRight;
						pRight->up											= pUp->next;

						pRight->header->next->down							= p->header->next->next->next->next->next->down;
						if(pRight->header->next->down != NULL)				pRight->header->next->down->up = pRight->header->next;

						pRight->header->next->next->next->down				= p->header->next->next->next->next->next->next->next->down;
						if(pRight->header->next->next->next->down != NULL)	pRight->header->next->next->next->down->up = pRight->header->next->next->next;


						parent->n++;
						if( (parent != NULL) && (parent->up == NULL) ) root = parent;

						parent = p;
						DoublyLinkedList* temp = p;
						if(i < pUp->score)
							p = pLeft;
						else
							p = pRight;

						delete temp;
					
					}
				}
			}
			else
			{
				DoublyNode* temp = p->header->next;

				while((i > temp->next->score) && (temp->next != p->trailer)) 
					temp = temp->next->next;

				if(temp == p->trailer) 
					temp = temp->prev; // düðümün sonuna kadar gidildi mi?

				parent = p;
				if(temp->down != NULL) 
					p = temp->down;
				else 
				{
					p->insertOrdered(i);
					break;
				}
			}
		}	
	}
}

// inorder traversal
void LinkedBinaryTree::inorder(DoublyLinkedList* v) const
{
	if (v->header->next->down != NULL)		inorder(v->header->next->down);

	cout << v->header->next->next->score << " ";

	if (v->header->next->next->next->down != NULL)		inorder(v->header->next->next->next->down);

	if (v->size() > 1) cout << v->header->next->next->next->next->score << " ";

	if (v->size() > 2){
		if (v->header->next->next->next->next->next->down != NULL)		inorder(v->header->next->next->next->next->next->down);
	}

	if (v->size() > 2) cout << v->header->next->next->next->next->next->next->score << " ";
}

// Eklenecek...
void LinkedBinaryTree::remove(DoublyNode* p, int e)
{

}

LinkedBinaryTree::LinkedBinaryTree()				// constructor
{ 
	root = NULL;
	n = 0; 
}

int LinkedBinaryTree::size() const					// number of DoublyNodes
{ 
	return n; 
}



void main()
{
	LinkedBinaryTree tree_234;

	tree_234.insert(16);
	tree_234.insert(8);
	tree_234.insert(24);
	tree_234.insert(4);
	tree_234.insert(12);
	tree_234.insert(20);
	tree_234.insert(28);
	tree_234.insert(2);
	tree_234.insert(6);
	tree_234.insert(10);
	tree_234.insert(14);
	tree_234.insert(18);
	tree_234.insert(22);
	tree_234.insert(26);
	tree_234.insert(30);
	tree_234.insert(1);
	tree_234.insert(3);
	tree_234.insert(5);
	tree_234.insert(7);
	tree_234.insert(9);
	tree_234.insert(11);
	tree_234.insert(13);
	tree_234.insert(15);
	tree_234.insert(17);
	tree_234.insert(19);
	tree_234.insert(21);
	tree_234.insert(23);
	tree_234.insert(25);
	tree_234.insert(27);
	tree_234.insert(29);
	tree_234.insert(31);

	cout<< "2-3-4 Tree Inorder Traversal :" << endl;
	tree_234.inorder(tree_234.root);


	::getchar();
}