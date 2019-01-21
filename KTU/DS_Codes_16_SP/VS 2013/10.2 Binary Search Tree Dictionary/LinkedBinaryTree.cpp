#include <string>
#include <iostream>													
using namespace std;	

struct word
{
	char ingilizce[12];
	char turkce[14];
};

struct Node										// a node of the tree
{									
	word kelime;
	Node*   par;								// parent
	Node*   left;								// left child
	Node*   right;								// right child

	Node()										// constructor
	{
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
	void addBelowRoot(Node* p, word kelime);	// add root to empty tree
	void expandExternal(Node* p);				// expand external node
	void removeAboveExternal(Node* p);			// remove p and parent	

	void preorder(Node* v) const;				// preorder utility
	void inorder(Node* v) const;				// inorder utility
	void postorder(Node* v) const;				// postorder utility

	void deleteNode(Node* p, char* kelime);
};

void LinkedBinaryTree::addBelowRoot(Node* p, word kelime)			
{ 
	Node* parent;
	while(p != NULL)
	{
		parent = p;
		if( ::strcmp(kelime.ingilizce, p->kelime.ingilizce) == -1)
			p = p->left;
		else
			p = p->right;
	}

	Node* newNode = new Node;
	strcpy(newNode->kelime.ingilizce, kelime.ingilizce);
	strcpy(newNode->kelime.turkce,	 kelime.turkce);
	newNode->par = parent;

	if (::strcmp(newNode->kelime.ingilizce, parent->kelime.ingilizce) == -1 ) 
		parent->left = newNode; 		
	else 
		parent->right = newNode;

	n += 1;
}

void LinkedBinaryTree::deleteNode(Node* p, char* sorgu)
{
	Node* temp;
	Node* parent;

	while(p != NULL)
	{
		if( ::strcmp(sorgu, p->kelime.ingilizce) == 0)	break;
		else
		{
			parent = p;
			if( ::strcmp(sorgu, p->kelime.ingilizce) == -1)
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
			// Kendisinden küçük en büyük düğümü kendi yerine koy
			if (p->left != NULL)
			{
				temp = p->left;
				while (temp->right != NULL) temp = temp->right;

				strcpy(root->kelime.ingilizce, temp->kelime.ingilizce);
				strcpy(root->kelime.turkce, temp->kelime.turkce);

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

				strcpy(p->kelime.ingilizce, temp->kelime.ingilizce);
				strcpy(p->kelime.turkce, temp->kelime.turkce);

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

LinkedBinaryTree::LinkedBinaryTree()					// constructor
: root(NULL), n(0) { }

int LinkedBinaryTree::size() const						// number of nodes
{ 
	return n; 
}

bool LinkedBinaryTree::empty() const					// is tree empty?
{ 
	return size() == 0; 
}

void LinkedBinaryTree::addRoot()						// add root to empty tree
{ 
	root = new Node; 
	n = 1; 
}

// preorder traversal
void LinkedBinaryTree::preorder(Node* v) const 
{	
	cout << v->kelime.ingilizce <<endl;

	if (v->left != NULL)		preorder(v->left);	

	if (v->right != NULL)		preorder(v->right);	
}

// inorder traversal
void LinkedBinaryTree::inorder(Node* v) const 
{
	if (v->left != NULL)		inorder(v->left);	

	cout << v->kelime.ingilizce <<endl;

	if (v->right != NULL)		inorder(v->right);	

}

// postorder traversal
void LinkedBinaryTree::postorder(Node* v) const 
{
	if (v->left != NULL)		postorder(v->left);	

	if (v->right != NULL)		postorder(v->right);
	
	cout << v->kelime.ingilizce <<endl;	
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


void generateTree(LinkedBinaryTree* binaryTree)
{
	word kelime;

	FILE* dic = fopen("dictionary.txt", "r");

	binaryTree->addRoot();

	fscanf(dic, "%s", &kelime.ingilizce);
	fscanf(dic, "%s", &kelime.turkce);
	strcpy( binaryTree->root->kelime.ingilizce, kelime.ingilizce ); 
	strcpy( binaryTree->root->kelime.turkce, kelime.turkce ); 

	for(int i=0; i<30; i++)
	{
		fscanf(dic, "%s", &kelime.ingilizce);
		fscanf(dic, "%s", &kelime.turkce);

		binaryTree->addBelowRoot(binaryTree->root, kelime);
	}

	cout << endl << "AGAC OLUSTURULDU !" << endl << endl << "press any key...";
	::getchar(); ::getchar();

	fclose(dic);
}

void searchTree(Node* p)
{
	char sorgu[12];
	cout << endl << "Sorgulamak istediginiz kelimeyi giriniz... = ";
	scanf("%s",sorgu);

	while(p != NULL)
	{
		if( ::strcmp(sorgu, p->kelime.ingilizce) == 0)	break;
		else
		{
			if( ::strcmp(sorgu, p->kelime.ingilizce) == -1)
				p = p->left;
			else
				p = p->right;
		}
	}

	if(p == NULL)
	{
		cout << endl << sorgu << " AGACTA YOK !" << endl << endl << "press any key...";
		::getchar(); ::getchar();
	}
	else
	{
		cout << endl << p->kelime.ingilizce << " 'nin Turkcesi " << p->kelime.turkce << " 'dir." << endl << endl << "press any key...";
		::getchar(); ::getchar();
	}
}

void deleteNode(LinkedBinaryTree* binaryTree)
{
	char sorgu[12];
	cout << endl << "Silmek istediginiz kelimeyi giriniz... = ";
	cin >> sorgu;

	binaryTree->deleteNode(binaryTree->root, sorgu);

	cout << endl << sorgu << " silindi... " << endl << endl <<"press any key...";
	::getchar(); ::getchar();
}

void insertNode(LinkedBinaryTree* binaryTree)
{
	word kelime;

	cout << endl << "Kelimenin Ingilizce'sini giriniz... = ";
	cin >> kelime.ingilizce;

	cout << endl << "Kelimenin Turkce'sini giriniz... = ";
	cin >> kelime.turkce;

	binaryTree->addBelowRoot(binaryTree->root, kelime);

	cout << endl << kelime.ingilizce << " eklendi... "<< endl << endl <<"press any key...";
	::getchar(); ::getchar();
}

void main()
{
	LinkedBinaryTree binaryTree;

	char s;
	do
	{
		system("cls");

		printf(" \n");
		printf(" BINARY SEARCH TREE \n");
		printf(" SOZLUK UYGULAMASI\n\n");
		printf(" [0] AGACI DOSYADAN OKU \n");
		printf(" [1] KELIME SORGULA \n");
		printf(" [2] KELIME EKLE\n");
		printf(" [3] KELIME SIL \n");
		printf(" [4] PROGRAMDAN CIK \n");
		printf(" \n SECIMINIZ [0..4] = ");

		s = ::getchar();

		switch(s)
		{
			case '0' :	generateTree(&binaryTree);		break;
			case '1' :	searchTree(binaryTree.root);	break;
			case '2' :	insertNode(&binaryTree);		break;
			case '3' :	deleteNode(&binaryTree);		break;
			case '4' :	return ;
		}
		
	}  while(1);
}





