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
		elt   = 0;
		par   = NULL;
		left  = NULL;
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


void LinkedBinaryTree::addBelowRoot(Node* p, int elt)			
{ 
	Node* parent = NULL;
	Node* Gparent = NULL;

	while(p != NULL)
	{
		parent = p;
		if( p->elt > elt)
			p = p->left;
		else

			p = p->right;
	}

	Node* newNode = new Node;
	newNode->elt = elt;
	newNode->par = parent;

	if (newNode->elt < parent->elt) 
		parent->left = newNode; 		
	else 
		parent->right = newNode;

	n += 1;

	// NOW SPLAYING ...

	if(parent != NULL) Gparent = parent->par;

	while (newNode->par != NULL)
	{
		if (newNode->par == root)
		{	
			// ZIG
			if (newNode->elt < root->elt) 
			{
				root->left			= newNode->right;
				if(newNode->right != NULL) newNode->right->par = root;
				newNode->right		= root;
				root->par			= newNode;
			}
			else
			{
				root->right			= newNode->left;
				if(newNode->left != NULL) newNode->left->par	= root;
				newNode->left		= root;
				root->par			= newNode;
			}

			root			= newNode;
			newNode->par	= NULL;
		}
		else
		{
			// ZIG-ZAG (left-right)
			if((newNode == parent->right) && (parent == Gparent->left))
			{
				// I. AÞAMA (newNode <-> Parent)					 
				parent->right	= newNode->left;
				if(newNode->left != NULL)  newNode->left->par = parent;
				newNode->left	= parent; 
				parent->par		= newNode;
				Gparent->left	= newNode;
				newNode->par	= Gparent;

				// II. AÞAMA (newNode <-> Gparent)
				newNode->par		= Gparent->par;
				Gparent->left		= newNode->right;
				if(newNode->right != NULL)  newNode->right->par = Gparent;
				newNode->right		= Gparent;
				Gparent->par		= newNode;

				if(newNode->par == NULL) 
					root = newNode;
				else if (newNode->elt < newNode->par->elt)
					newNode->par->left = newNode;
				else
					newNode->par->right = newNode;
			}
			// ZIG-ZAG (right-left)
			else if((newNode == parent->left) && (parent == Gparent->right))
			{
				// I. AÞAMA (newNoded <-> Parent)					 
				parent->left	= newNode->right;
				if(newNode->right != NULL)  newNode->right->par = parent;
				newNode->right	= parent; 
				parent->par		= newNode;
				Gparent->right	= newNode;
				newNode->par	= Gparent;

				// II. AÞAMA (newNode <-> Gparent)
				newNode->par		= Gparent->par;
				Gparent->right		= newNode->left;
				if(newNode->left != NULL) newNode->left->par	= Gparent; 
				newNode->left		= Gparent;
				Gparent->par		= newNode;

				if(newNode->par == NULL) 
					root = newNode;
				else if (newNode->elt < newNode->par->elt)
					newNode->par->left = newNode;
				else
					newNode->par->right = newNode;
			}
			// ZIG-ZIG (left-left)
			else if((newNode == parent->left) && (parent == Gparent->left))
			{
				// I. AÞAMA (Parent <-> Gparent)					 
				Gparent->left	= parent->right;
				if(parent->right != NULL) parent->right->par = Gparent;
					
				if(Gparent->par != NULL)
				{
					if (Gparent->elt < Gparent->par->elt)
						Gparent->par->left	= parent;
					else
						Gparent->par->right	= parent;
				}

				parent->par		= Gparent->par; 
				parent->right	= Gparent;
				Gparent->par	= parent;
				Gparent			= parent->par;

				// II. AÞAMA (newNode <-> Parent)
				parent->left	= newNode->right;
				if(newNode->right != NULL) newNode->right->par = parent;
				newNode->right	= parent; 
				parent->par		= newNode;

				if(Gparent != NULL)
				{
					if (newNode->elt < Gparent->elt)
						Gparent->left	= newNode;
					else
						Gparent->right	= newNode;	
				}

				newNode->par	= Gparent;
			}
			// ZIG-ZIG (right-right)
			else if((newNode == parent->right) && (parent == Gparent->right))
			{
				// I. AÞAMA (Parent <-> Gparent)					 
				Gparent->right	= parent->left;
				if(parent->left != NULL) parent->left->par = Gparent;

				if(Gparent->par != NULL)
				{
					if (Gparent->elt < Gparent->par->elt)
						Gparent->par->left	= parent;
					else
						Gparent->par->right	= parent;
				}
					
				parent->par		= Gparent->par; 
				parent->left	= Gparent;
				Gparent->par	= parent;
				Gparent			= parent->par;

				// II. AÞAMA (newNode <-> Parent)
				parent->right	= newNode->left;
				if(newNode->left != NULL) newNode->left->par = parent;
				newNode->left	= parent; 
				parent->par		= newNode;

				if(Gparent != NULL)
				{
					if (newNode->elt < Gparent->elt)
						Gparent->left	= newNode;
					else
						Gparent->right	= newNode;	
				}

				newNode->par	= Gparent;
			}

			parent  = newNode->par;
			if (parent != NULL) Gparent = newNode->par->par;	
			if (newNode->par == NULL) root = newNode;
		}
	}
}

void LinkedBinaryTree::deleteNode(Node* p, int e)
{
	Node* temp;

	while(p != NULL)
	{
		if(p->elt == e)	break;
		else
		{
			if( e < p->elt)
				p = p->left;
			else
				p = p->right;
		}
	}

	if( p == NULL)
	{
		cout << "The node does not exists" << endl;
		::getchar();
		return;
	}
	else
	{		
		if( p == root)              
		{
			// Kendisinden küçük en büyük düðümü kendi yerine koy
			if(p->left != NULL)
			{
				temp = p->left;
				while (temp->right != NULL) temp = temp->right;
				root->elt = temp->elt;

				if(temp->left != NULL)
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

			else if(p->right != NULL)
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
			if( p->left != NULL)
			{
				temp = p->left;
				while (temp->right != NULL) temp = temp->right;
				p->elt = temp->elt;

				if(temp->left != NULL)
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
			else if(p->right != NULL)
			{
				if(p == p->par->left)
				{
					p->par->left  = p->right;
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

			if(p->left == NULL && p->right == NULL)
			{
				if(p->par->left == p) 
					p->par->left = NULL;
				else 
					p->par->right = NULL;
				delete p;
			}	
		}
	} 
}

LinkedBinaryTree::LinkedBinaryTree()			// constructor
{ 
	root = NULL;
	n = 0;
}

int LinkedBinaryTree::size() const				// number of nodes
{ 
	return n; 
}

bool LinkedBinaryTree::empty() const			// is tree empty?
{ 
	return size() == 0; 
}

void LinkedBinaryTree::addRoot()				// add root to empty tree
{ 
	root = new Node; 
	n = 1; 
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


void main()
{
	LinkedBinaryTree splayTree;

	splayTree.addRoot();
	
	splayTree.root->elt = 12;

	splayTree.addBelowRoot(splayTree.root, 2);
	splayTree.addBelowRoot(splayTree.root, 10);
	splayTree.addBelowRoot(splayTree.root, 6);
	splayTree.addBelowRoot(splayTree.root, 4);
	splayTree.addBelowRoot(splayTree.root, 8);
	splayTree.addBelowRoot(splayTree.root, 5);
	splayTree.addBelowRoot(splayTree.root, 9);
	splayTree.addBelowRoot(splayTree.root, 1);
	splayTree.addBelowRoot(splayTree.root, 13);
	splayTree.addBelowRoot(splayTree.root, 7);	// 12.01.2012 Final
	
	cout<< "Inorder Traversal : " ;
	splayTree.inorder(splayTree.root);

	::getchar();
}