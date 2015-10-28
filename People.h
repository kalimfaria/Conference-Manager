#ifndef PEOPLE_H
#define PEOPLE_H


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


int id=0;
int reaD = 0;
int fileiD;
string filename;

struct Node
{
	int id;
	string name;
	string address;
	string school;
	string city;
	string country;

	Node *left;
	Node *right;
	int height;

	Node()
	{
		left= NULL;
		right = NULL;
		height  = 0;
	}
};

class People
{
private: 
	Node * Root;

public:
	int maxid;
	ofstream myfile;
	ifstream infile;
	People () { Root = NULL; maxid = 0;}

	// A utility function to get height of the tree
	int height(Node *N)
	{
		if (N == NULL)
			return 0;
		return N->height;
	}

	// A utility function to get maximum of two integers
	int max(int a, int b)
	{
		return (a > b)? a : b;
	}

	/* Helper function that allocates a new node with the given value and
	NULL left and right pointers. */
	Node* newNode(int value)
	{
		Node *newnode;
		newnode         = new Node;																				
		newnode->id     = value;


		if(reaD == 0)
		{
			if(infile.is_open())
			{
				infile >> newnode-> name>> newnode->address >> newnode->school >> newnode -> city >> newnode ->country >> newnode->height ; newnode->height = 1;
				int len = newnode->name.length();
				newnode->id = value;
				while (len)
				{
					if(newnode->name[len-1] == '_')
						newnode->name[len-1] = ' ';
					len--;
				}
				int len2 = newnode->address.length();
				while (len2)
				{
					if(newnode->address[len2-1] == '_')
						newnode->address[len2-1] = ' ';
					len2--;
				}
				int len3 = newnode->school.length();
				while (len3)
				{
					if(newnode->school[len3-1] == '_')
						newnode->school[len3-1] = ' ';
					len3--;
				}
				int len4 = newnode->city.length();
				while (len4)
				{
					if(newnode->city[len4-1] == '_')
						newnode->city[len4-1] = ' ';
					len4--;
				}
				int len5 = newnode->country.length();
				while (len5)
				{
					if(newnode->country[len5-1] == '_')
						newnode->country[len5-1] = ' ';
					len5--;
				}
			}		
		}
		else
		{
			//CHANGE
			cin.ignore();
			cout << "Enter the details below : \n";
			
			do {
				cout << "Name : ";
			getline(cin, newnode->name);

			} while (newnode ->name == "\0");
			
			do {
				cout << "Address : " ;
			getline(cin, newnode->address);
			} while (newnode ->address == "\0");
			do {

			cout << "School : ";
			getline(cin, newnode->school);
			} while (newnode ->school == "\0");
			do {
			cout << "City : ";
			getline(cin, newnode->city);
			} while (newnode -> city == "\0");
			do {
			cout << "Country : ";
			getline(cin, newnode->country);
			} while (newnode ->country == "\0");
			cout << "ID : " << newnode->id << endl;
		}
		newnode->left   = NULL;
		newnode->right  = NULL;
		newnode->height = 1;  // new node is initially added at leaf
		return(newnode);
	}
	// A utility function to right rotate subtree rooted with y
	// See the diagram given above.
	Node *rightRotate( Node *y)
	{
		Node *x = y->left;
		Node *T2 = x->right;

		// Perform rotation
		x->right = y;
		y->left = T2;

		// Update heights
		y->height = max(height(y->left), height(y->right))+1;
		x->height = max(height(x->left), height(x->right))+1;

		// Return new root
		return x;
	}
	// A utility function to left rotate subtree rooted with x
	// See the diagram given above.
	Node *leftRotate(Node *x)
	{
		Node *y = x->right;
		Node *T2 = y->left;

		// Perform rotation
		y->left = x;
		x->right = T2;

		//  Update heights
		x->height = max(height(x->left), height(x->right))+1;
		y->height = max(height(y->left), height(y->right))+1;

		// Return new root
		return y;
	}
	// Get Balance factor of node N
	int getBalance(Node *N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) - height(N->right);
	}
	void Insert( int value )
	{
		Root = insert (Root,value);
	}
	Node* insert(Node* node, int value)
	{
		/* 1.  Perform the normal BST rotation */
		if (node == NULL)
			return(newNode(value));
		if (value < node->id)
			node->left  = insert(node->left, value);
		else if ( value > node->id )
			node->right = insert(node->right, value);

		/* 2. Update height of this ancestor node */
		node->height = max(height(node->left), height(node->right)) + 1;

		/* 3. Get the balance factor of this ancestor node to check whether
		this node became unbalanced */
		int balance = getBalance(node);

		// If this node becomes unbalanced, then there are 4 cases

		// Left Left Case
		if (balance > 1 && value < node->left->id) // so insertion is on the left  (in a straight line)
			return rightRotate(node);

		// Right Right Case
		if (balance < -1 && value > node->right->id)// so insertion is on the right (in a straight line)
			return leftRotate(node);

		// Left Right Case
		if (balance > 1 && value > node->left->id)
		{
			node->left =  leftRotate(node->left);
			return rightRotate(node);
		}

		// Right Left Case
		if (balance < -1 && value < node->right->id)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		/* return the (unchanged) node pointer */

		return node;
	}	
	/* Given a non-empty binary search tree, return the node with minimum 
	value found in that tree. Note that the entire tree does not
	need to be searched. */
	Node * minValueNode(Node* node) // we have to give this node root->right // what this does is
		// it gets the minimum value from the right of the tree
	{
		Node* current = node;

		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
			current = current->left;

		return current;
	}
	Node * maxValueNode(Node* node) // we have to give this node root->left
		// gets the  maximum value from the left of the tree
	{
		Node* current = node;

		/* loop down to find the rightmost leaf */
		while (current->right != NULL)
			current = current->right;

		return current;
	}	
	void Delete (int value)
	{
		Root = deleteNode(Root, value);
	}
	Node* deleteNode(Node* root, int value)
	{
		if (root == NULL)
			return root;

		if ( value < root->id )
			root->left = deleteNode(root->left, value);

		else if( value > root->id )
			root->right = deleteNode(root->right, value);

		else
		{			
			if( (root->left == NULL) || (root->right == NULL) )
			{
				Node *temp = root->left ? root->left : root->right;

				if(temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else 
					*root = *temp; 
				delete temp;
				temp = NULL;
			}
			else
			{
				Node* temp = minValueNode(root->right);
				root->id = temp->id;
				root->right = deleteNode(root->right, temp->id);
			}
		}

		if (root == NULL)
			return root;

		// UPDATE HEIGHT OF THE CURRENT NODE
		root->height = max(height(root->left), height(root->right)) + 1;


		//  GET THE BALANCE FACTOR OF THIS NODE (to check whether
		//  this node became unbalanced)
		int balance = getBalance(root);

		// If this node becomes unbalanced, then there are 4 cases

		// Left Left Case
		if (balance > 1 && getBalance(root->left) >= 0)
			return rightRotate(root);

		// Left Right Case
		if (balance > 1 && getBalance(root->left) < 0)
		{
			root->left =  leftRotate(root->left);
			return rightRotate(root);
		}

		// Right Right Case
		if (balance < -1 && getBalance(root->right) <= 0)
			return leftRotate(root);

		// Right Left Case
		if (balance < -1 && getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}
	// A utility function to print preorder traversal of the tree.
	// The function also prints height of every node

	void PreOrder ( )
	{
		preOrder(Root);
	};

	void InOrder ()
	{
		inOrder(Root);
	}

	void PostOrder ()
	{
		postOrder(Root);
	}

	void preOrder(Node *root)
	{
		if(root != NULL)
		{
			cout << "Member ID : " << root->id << "\nName : " << root->name << "\nAddress : " << root->address << "\nSchool : " << root->school << "\nCity : " << root->city << "\nCountry : " << root->country/* << "\nHeight : " << root->height */<< endl;
			preOrder(root->left);
			preOrder(root->right);
		}
	}

	void inOrder(Node *root)
	{
		if(root == NULL)
			{
				//cout << "No Attendees!\n";
				return;
		}
		else if(root != NULL)
		{
			inOrder(root->left);
			cout << "Member ID : " << root->id << "\nName : " << root->name << "\nAddress : " << root->address << "\nSchool : " << root->school << "\nCity : " << root->city << "\nCountry : " << root->country << endl << endl;
			inOrder(root->right);
		}
	}

	void postOrder (Node * root)
	{
		if(root != NULL)
		{
			postOrder(root->left);
			postOrder(root->right);
			cout << "Member ID : " << root->id << "\nName : " << root->name << "\nAddress : " << root->address << "\nSchool : " << root->school << "\nCity : " << root->city << "\nCountry : " << root->country /*<< "\nHeight : " << root->height*/ << endl;

		}
	}

	int Count ()
	{
		return Count(Root);
	}

	int Count(Node * node)
	{
		if ( node == NULL )
			return 0;
		return ( Count(node->left) + Count(node->right) + 1 );
	}

	int FindMin () // uses the binary search tree property of the AVL Tree
	{
		Node* Temp = Root;
		while ( Temp->left != NULL )
			Temp = Temp->left;
		return Temp->id;
	}

	int FindMax () // uses the binary search tree property of the AVL Tree
	{
		Node* Temp = Root;
		while ( Temp->right != NULL )
			Temp = Temp->right;
		return Temp->id;
	} 

	int Find (int value)
	{
		return Find(Root, value);
	}

	int Find (Node* node, int value)
	{
		if ( node == NULL )	{
			cout << "Attendee " << value << " not found in the tree." << endl;
			return  0;
		}
		if ( node->id < value )
			Find ( node->right,value );
		else if ( node->id > value )
			Find ( node->left,value );
		else // Found!
		{	cout << "Member ID : " << node->id << "\nName : " << node->name << "\nAddress : " << node->address << "\nSchool : " << node->school << "\nCity : " << node->city << "\nCountry : " << node->country /*<< "\nHeight : " << node->height*/ << endl;
		     return 1;
		}}

	void Edit (int value)
	{
		Edit(Root, value);
	}

	void Edit (Node* node, int value)
	{
		if ( node == NULL )	{
			cout << "Attendee " << value << " not found in the tree." << endl;
			return;
		}
		if ( node->id < value )
			Edit ( node->right,value );
		else if ( node->id > value )
			Edit ( node->left,value );
		else // Found!
		{
			cout << "What do you want to modify? \n";
			cout << "\t1 - Name\n\t2 - Address\n\t3 - School Name\n\t4 - City Name\n\t5 - Country Name\n";
			int opti;
			cin >> opti;
			cin.ignore();
			switch(opti)
			{
			case 1:
				//edit name
				cout << "The current name is : " << node->name << endl;
				do {
				cout << "Enter new name : ";
				getline (cin,node->name);
				} while (node -> name == "\0");
				break;
			case 2:
				//edit address
				cout << "The current address is : " << node->address << endl;
				do {
				cout << "Enter new address : ";
				getline(cin,node->address);
				} while (node -> address == "\0" );
				break;
			case 3:
				//edit school name
				cout << "The current school name is : " << node->school << endl;
				do {
				cout << "Enter new school name : ";
				getline(cin,node->school);
				} while (node -> school == "\0");
				break;
			case 4:
				//edit city
				cout << "The current city is : " <<node->city << endl;
				do {
				cout << "Enter new city name : ";
				getline(cin,node->city);
				} while (node ->city == "\0" );
				break;
			case 5:
				//edit country
				cout << "The current country name is : " << node->country << endl;
			do
			{	cout << "Enter new country name : ";
				getline(cin,node->country);

			} while (node->country ==  "\0");
				break;
			default:
				break;
			}

			cout << "Member ID : " << node->id << "\nName : " << node->name << "\nAddress : " << node->address << "\nSchool : " << node->school << "\nCity : " << node->city << "\nCountry : " << node->country <</* "\nHeight : " << node->height <<*/ endl;
		}
	}

	void DeleteTree ()
	{
		int i = DeleteTree(Root,0);
		Root = NULL;
		if (i!=0)cout << "All attendees have been deleted!\n";
		else if (i == 0) cout << "No attendees registered!\n";
	}

	int DeleteTree(Node * node, int del)
	{
		if (node == NULL) 
			return del;

		// using post  order (parent should be deleted last)
		del = DeleteTree(node->left,del+1);
		del = DeleteTree(node->right,del+1);

		delete node;
	}

	void HeightRoot()
	{
		cout << Root->height << endl;
	}

	void createfile(int fileID)
	{
		stringstream str;
		fileiD = fileID;
		str <<"People" << fileID <<".txt";
		filename = str.str();

		myfile.open(filename.c_str(), ios::out);
		myfile << maxid << " ";
		write(Root);
	}

	void write(Node*temp)
	{	
		if(myfile.is_open(), ios::out)
		{
			if(temp != NULL)
			{
				int len = temp->name.length();						
				while (len)
				{
					if(temp->name[len-1] == ' ')
						temp->name[len-1] = '_';
					len--;
				}
				int len2 = temp->address.length();
				while (len2)
				{
					if(temp->address[len2-1] == ' ')
						temp->address[len2-1] = '_';
					len2--;
				}
				int len3 = temp->school.length();
				while (len3)
				{
					if(temp->school[len3-1] == ' ')
						temp->school[len3-1] = '_';
					len3--;
				}
				int len4 = temp->city.length();
				while (len4)
				{
					if(temp->city[len4-1] == ' ')
						temp->city[len4-1] = '_';
					len4--;
				}
				int len5 = temp->country.length();
				while (len5)
				{
					if(temp->country[len5-1] == ' ')
						temp->country[len5-1] = '_';
					len5--;
				}
				write(temp->left);
				myfile << temp->id << " " << temp->name << " " << temp->address << " " << temp->school << " " << temp->city << " " << temp->country << " " << temp->height << endl;
				write(temp->right);
			}
		}
	}
	void read(int fileID,string filename)
	{
		stringstream str;
		str << filename ;
		string fylename = str.str();

		// CHANGES MADE
		ifstream IF ( fylename, ios::app );
		string s = "\0";
		getline (IF, s, '\0' );

		if ( s.length() <= 2 ) IF.close();

		else {
			IF.close();
			infile.open(fylename,ios::app);
			if(infile.is_open())
				infile>>this->maxid;
			Read(Root);
		}
	}	
	void Read(Node*root)
	{
		if(infile.is_open())   
		{
			while(!infile.eof())
			{
				infile >> id;
				Insert(id);
			}
		}
		else
			cout<<"file didnt open :(";
	}
};
#endif