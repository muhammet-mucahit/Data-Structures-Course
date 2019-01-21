#include <iostream>
using namespace std;

struct Node									// a node of the tree
{
	int    elt;								// element value
	Node*   par;							// parent
	Node*   left;							// left child
	Node*   right;							// right child

	Node()									// constructor
	{
		elt = 0;
		par = NULL;
		left = NULL;
		right = NULL;
	}
};


struct LinkedBinaryTree
{
	Node* root;								// pointer to the root
	int n;									// number of nodes

	LinkedBinaryTree();						// constructor
	int size() const;						// number of nodes
	bool empty() const;						// is tree empty?
	void addRoot();							// add root to empty tree
	void expandExternal(Node* p);			// expand external node
	void removeAboveExternal(Node* p);		// remove p and parent

	void preorder(Node* v) const;			// preorder utility
	void inorder(Node* v) const;			// inorder utility
	void postorder(Node* v) const;			// postorder utility
	void eulerTour(Node* v) const;
};



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

// expand external node
void LinkedBinaryTree::expandExternal(Node* v)
{
	v->left			= new Node;					// add a new left child
	v->left->par	= v;						// v is its parent
	v->right			= new Node;				// and a new right child
	v->right->par	= v;						// v is its parent
	n += 2;										// two more nodes
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

// Euler Tour traversal
void LinkedBinaryTree::eulerTour(Node* v) const
{
	if (v->left != NULL)
	{
		cout << v->elt << " ";
		eulerTour(v->left);
	}
	else
		cout << v->elt << " ";

	if (v->right != NULL)
		eulerTour(v->right);
}

// remove p and parent
void LinkedBinaryTree::removeAboveExternal(Node* p)
{
	if ( p->left != NULL || p->right != NULL)
	{
		cout <<endl<<endl<< "This node is not external !"<<endl;
		return;
	}

	Node* w = p;  Node* v = w->par;						// get p's node and parent
	Node* sib = (w == v->left ?  v->right : v->left);

	if (v == root)
	{													// child of root?
		root = sib;										// ...make sibling root
		sib->par = NULL;
	}
	else
	{
		Node* gpar = v->par;							// w's grandparent

		if (v == gpar->left)
			gpar->left = sib; 							// replace parent by sib
		else
			gpar->right = sib;

		sib->par = gpar;
	}

	delete w; delete v;									// delete removed nodes
	n -= 2;												// two fewer nodes
}


int main()
{
	LinkedBinaryTree binaryTree;

	binaryTree.addRoot();

	binaryTree.root->elt = 8;

	binaryTree.expandExternal(binaryTree.root);

	binaryTree.root->left->elt = 4;
	binaryTree.root->right->elt = 12;

	binaryTree.expandExternal(binaryTree.root->left);

	binaryTree.root->left->left->elt = 2;
	binaryTree.root->left->right->elt = 6;

	binaryTree.expandExternal(binaryTree.root->right);

	binaryTree.root->right->left->elt = 10;
	binaryTree.root->right->right->elt = 14;

	binaryTree.expandExternal(binaryTree.root->left->left);

	binaryTree.root->left->left->left->elt = 1;
	binaryTree.root->left->left->right->elt = 3;

	binaryTree.expandExternal(binaryTree.root->left->right);

	binaryTree.root->left->right->left->elt = 5;
	binaryTree.root->left->right->right->elt = 7;

	binaryTree.expandExternal(binaryTree.root->right->left);

	binaryTree.root->right->left->left->elt = 9;
	binaryTree.root->right->left->right->elt = 11;

	binaryTree.expandExternal(binaryTree.root->right->right);

	binaryTree.root->right->right->left->elt = 13;
	binaryTree.root->right->right->right->elt = 15;



	//cout<< "Inorder Traversal : " ;
	//binaryTree.inorder(binaryTree.root);

	//cout<<endl<<endl;

	//cout<< "Preorder Traversal : " ;
	//binaryTree.preorder(binaryTree.root);

	//cout<<endl<<endl;

	//cout<< "Postorder Traversal : " ;
	//binaryTree.postorder(binaryTree.root);

	//cout<<endl<<endl;

	cout << "Euler Tour Traversal : ";
	binaryTree.eulerTour(binaryTree.root);


	//binaryTree.removeAboveExternal(binaryTree.root->left->right->right);

	//cout<<endl<<endl;

	//cout<< "Inorder Traversal  After Removing 7 and 6 :" << endl;
	//binaryTree.inorder(binaryTree.root);

	//cout<<endl<<endl;

	//cout<< "Preorder Traversal  After Removing 7 and 6 :" << endl;
	//binaryTree.preorder(binaryTree.root);

	//cout<<endl<<endl;

	//cout<< "Postorder Traversal  After Removing 7 and 6 :" << endl;
	//binaryTree.postorder(binaryTree.root);

	::getchar();

}
