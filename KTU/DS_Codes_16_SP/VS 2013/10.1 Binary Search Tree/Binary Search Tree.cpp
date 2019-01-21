
#include <iostream>
using namespace std;

struct Node										// a node of the tree
{
	int    elt;									// element value
	Node*   par;								// parent
	Node*   left;								// left child
	Node*   right;								// right child

	Node()										// constructor
	{
		elt = 0;
		par = NULL;
		left = NULL;
		right = NULL;
	}
};


struct LinkedBinaryTree
{
	Node* root;									// pointer to the root
	int n;										// number of nodes

	LinkedBinaryTree();							// constructor
	int size() const;							// number of nodes
	bool empty() const;							// is tree empty?
	void addRoot();								// add root to empty tree
	void addBelowRoot(Node* p, int);			// add root to empty tree
	void expandExternal(Node* p);				// expand external node
	void removeAboveExternal(Node* p);			// remove p and parent

	void preorder(Node* v) const;				// preorder utility
	void inorder(Node* v) const;				// inorder utility
	void postorder(Node* v) const;				// postorder utility

	void deleteNode(Node* p, int);
};


LinkedBinaryTree::LinkedBinaryTree()				// constructor
: root(NULL), n(0) { }

int LinkedBinaryTree::size() const					// number of nodes
{
	return n;
}

bool LinkedBinaryTree::empty() const				// is tree empty?
{
	return size() == 0;
}

void LinkedBinaryTree::addRoot()					// add root to empty tree
{
	root = new Node;
	n = 1;
}

void LinkedBinaryTree::addBelowRoot(Node* p, int e)
{
	Node* parent;

	while (p != NULL)
	{
		parent = p;
		if (e < p->elt)
			p = p->left;
		else
			p = p->right;
	}

	Node* newNode = new Node;
	newNode->elt = e;
	newNode->par = parent;

	if (newNode->elt < parent->elt)
		parent->left = newNode;
	else
		parent->right = newNode;

	n += 1;
}

// preorder traversal
void LinkedBinaryTree::preorder(Node* v) const
{
	cout << v->elt << " ";

	if (v->left != NULL)		preorder(v->left);

	if (v->right != NULL)		preorder(v->right);
}

// inorder traversal
void LinkedBinaryTree::inorder(Node* v) const
{
	if (v->left != NULL)		inorder(v->left);

	cout << v->elt << " ";

	if (v->right != NULL)		inorder(v->right);

}

// postorder traversal
void LinkedBinaryTree::postorder(Node* v) const
{
	if (v->left != NULL)		postorder(v->left);

	if (v->right != NULL)		postorder(v->right);

	cout << v->elt << " ";
}

void LinkedBinaryTree::deleteNode(Node* p, int e)
{
	Node* temp;

	while (p != NULL)
	{
		if (p->elt == e)	break;
		else
		{
			if (e < p->elt)
				p = p->left;
			else
				p = p->right;
		}
	}

	if (p == NULL)
	{
		cout << "The node does not exists" << endl;
		::getchar();
		return;
	}
	else
	{
		if (p == root)
		{
			// Kendisinden küçük en büyük düðümü kendi yerine koy
			if (p->left != NULL)
			{
				temp = p->left;
				while (temp->right != NULL) temp = temp->right;
				root->elt = temp->elt;

				if (temp->left != NULL)
				{
					temp->par->right = temp->left;
					temp->left->par = temp->par;
				}
				else
				{
					temp->par->right = NULL;
				}

				delete temp;
				return;
			}

			// Kendisinden büyük en küçük düðümü kendi yerine koy
			//if(p->right != NULL)
			//{
			//	temp = p->right;
			//	while (temp->left != NULL) temp = temp->left;
			//	root->elt = temp->elt;

			//	if(temp->right != NULL)
			//	{
			//		temp->par->left = temp->right;
			//		temp->right->par = temp->par;
			//
			//	}
			//	else
			//	{
			//		temp->par->left = NULL;
			//	}
			//	delete temp;
			//	return;
			//}

			else if (p->right != NULL)
			{
				root = p->right;
				delete p;
				return;
			}
			else
			{
				root = NULL;
				return;
			}
		}
		else
		{
			// Kendisinden küçük en büyük düðümü kendi yerine koy
			if (p->left != NULL)
			{
				temp = p->left;
				while (temp->right != NULL) temp = temp->right;
				p->elt = temp->elt;

				if (temp->left != NULL)
				{
					temp->par->right = temp->left;
					temp->left->par = temp->par;
				}
				else
				{
					temp->par->right = NULL;
				}

				delete temp;
				return;
			}
			else if (p->right != NULL)
			{
				if (p == p->par->left)
				{
					p->par->left = p->right;
					p->right->par = p->par;
				}
				else
				{
					p->par->right = p->right;
					p->right->par = p->par;

				}

				delete p;
				return;
			}

			// Kendisinden büyük en küçük düðümü kendi yerine koy
			//if( p->right != NULL)
			//{
			//	temp = p->right;
			//	while (temp->left != NULL) temp = temp->left;
			//	p->elt = temp->elt;

			//	if(temp->right != NULL)
			//	{
			//		temp->par->left = temp->right;
			//		temp->right->par = temp->par;
			//	}
			//	else
			//	{
			//		temp->par->left = NULL;
			//	}
			//
			//	delete temp;
			//	return;
			//}
			//else if(p->left != NULL)
			//{
			//	if(p == p->par->left)
			//	{
			//		p->par->left = p->left;
			//		p->left->par = p->par;
			//	}
			//	else
			//	{
			//		p->par->right = p->left;
			//		p->left->par = p->par;
			//
			//	}
			//
			//	delete p;
			//	return;
			//}

			if (p->left == NULL && p->right == NULL)
			{
				if (p->par->left == p)
					p->par->left = NULL;
				else
					p->par->right = NULL;
				delete p;
			}
		}
	}
}

// remove p and par
void LinkedBinaryTree::removeAboveExternal(Node* p)
{
	if ( p->left != NULL || p->right != NULL)
	{
		cout <<endl<<endl<< "This node is not external !"<<endl;
		return;
	}

	Node* w = p;  Node* v = w->par;						// get p's node and par
	Node* sib = (w == v->left ?  v->right : v->left);

	if (v == root)
	{													// p of root?
		root = sib;										// ...make sibling root
		sib->par = NULL;
	}
	else
	{
		Node* gpar = v->par;							// w's grandpar

		if (v == gpar->left)
			gpar->left = sib; 							// replace par by sib
		else
			gpar->right = sib;

		sib->par = gpar;
	}

	delete w; delete v;									// delete removed nodes
	n -= 2;												// two fewer nodes
}

// expand external node
void LinkedBinaryTree::expandExternal(Node* v)
{
	v->left			= new Node;			// add a new left p
	v->left->par	= v;				// v is its par
	v->right		= new Node;			// and a new right p
	v->right->par	= v;				// v is its par
	n += 2;								// two more nodes
}


int main()
{
	LinkedBinaryTree binaryTree;

	binaryTree.addRoot();

	binaryTree.root->elt = 16;

	binaryTree.addBelowRoot(binaryTree.root, 8);
	binaryTree.addBelowRoot(binaryTree.root, 24);
	binaryTree.addBelowRoot(binaryTree.root, 4);
	binaryTree.addBelowRoot(binaryTree.root, 12);
	binaryTree.addBelowRoot(binaryTree.root, 20);
	binaryTree.addBelowRoot(binaryTree.root, 28);
	binaryTree.addBelowRoot(binaryTree.root, 2);
	binaryTree.addBelowRoot(binaryTree.root, 6);
	binaryTree.addBelowRoot(binaryTree.root, 10);
	binaryTree.addBelowRoot(binaryTree.root, 14);
	binaryTree.addBelowRoot(binaryTree.root, 18);
	binaryTree.addBelowRoot(binaryTree.root, 22);
	binaryTree.addBelowRoot(binaryTree.root, 26);
	binaryTree.addBelowRoot(binaryTree.root, 30);
	binaryTree.addBelowRoot(binaryTree.root, 1);
	binaryTree.addBelowRoot(binaryTree.root, 3);
	binaryTree.addBelowRoot(binaryTree.root, 5);
	binaryTree.addBelowRoot(binaryTree.root, 7);
	binaryTree.addBelowRoot(binaryTree.root, 9);
	binaryTree.addBelowRoot(binaryTree.root, 11);
	binaryTree.addBelowRoot(binaryTree.root, 13);
	binaryTree.addBelowRoot(binaryTree.root, 15);
	binaryTree.addBelowRoot(binaryTree.root, 17);
	binaryTree.addBelowRoot(binaryTree.root, 19);
	binaryTree.addBelowRoot(binaryTree.root, 21);
	binaryTree.addBelowRoot(binaryTree.root, 23);
	binaryTree.addBelowRoot(binaryTree.root, 25);
	binaryTree.addBelowRoot(binaryTree.root, 27);
	binaryTree.addBelowRoot(binaryTree.root, 29);
	binaryTree.addBelowRoot(binaryTree.root, 31);

	cout<< "Inorder Traversal :" << endl;
	binaryTree.inorder(binaryTree.root);

	// Kendisinden küçük en büyük düðümü kendi yerine koy
	binaryTree.deleteNode(binaryTree.root,  8);
	binaryTree.deleteNode(binaryTree.root,  7);
	binaryTree.deleteNode(binaryTree.root,  16);	// root'u sil, yerine 15 gelecek

	// Kendisinden büyük en küçük düğümü kendi yerine koy
	//binaryTree.deleteNode(binaryTree.root,  24);
	//binaryTree.deleteNode(binaryTree.root,  25);
	//binaryTree.deleteNode(binaryTree.root,  16);	// delete root, yerine 17 gelecek


	cout<<endl<<endl<< "Inorder Traversal After Deletions :" << endl;
	binaryTree.inorder(binaryTree.root);

	::getchar();
}
