#ifndef SEMINAR_H
#define SEMINAR_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Linked_List.h"

using namespace std;

int idd=0;
int ReaD = 0;

int filEiD;
string filEname;

struct Node2
{

	int id;
	string venue;
	string start_time;
	string end_time;
	Linked_List speakers;
	int numofspeakers;

	Node2 *left;
	Node2 *right;
	int height;

	Node2()
	{
		left= NULL;
		right = NULL;
		numofspeakers=0;
		height  = 0;
	}

};

class Seminar
{
private: 
	Node2 * Root;

public:
	int maxid;
	ofstream myFile;
	ifstream inFile;
	Seminar () { Root = NULL; maxid = 0;}
	// A utility function to get height of the tree
	int height(Node2 *N)
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
	Node2* newNode(int value)
	{
		Node2 *newnode;
		newnode         = new Node2;																				
		newnode->id     = value;


		if(ReaD == 0)
		{


			if(inFile.is_open())
			{
				inFile >> newnode->venue >> newnode->start_time  >> newnode->end_time >> newnode->numofspeakers;

				string speakname, qualif;
				int IDENTITY;
				for(int i = 0; i < newnode->numofspeakers; i++)
				{
					inFile>> IDENTITY >>speakname>>qualif;
					newnode->speakers.Insert(IDENTITY,speakname,qualif);
				}
				inFile >> newnode->height; newnode->height = 1;
				int len2 = newnode->start_time.length();
				while (len2)
				{
					if(newnode->start_time[len2-1] == '_')
						newnode->start_time[len2-1] = ' ';
					len2--;
				}
				int len3 = newnode->end_time.length();
				while (len3)
				{
					if(newnode->end_time[len3-1] == '_')
						newnode->end_time[len3-1] = ' ';
					len3--;
				}

			}	

		}
		else
		{
			cout << "Enter the details below : \n";
			do {
			cout << "Venue : ";
			getline(cin, newnode->venue);
			} while (newnode -> venue == "\0") ;
			do {
			cout << "Starting time : " ;
			getline(cin, newnode->start_time);
			} while (newnode->start_time == "\0");
			do {
			cout << "Ending time : ";
			getline(cin, newnode->end_time);
			} while (newnode -> end_time == "\0");
			char yesno='1';
			string sp,q;
			while (yesno=='1')
			{
				do {
				cout << "Speaker's name : ";
				getline(cin, sp);
				} while (sp == "\0");
				//cout << sp;
				do
				{
				cout << "Qualification : ";
				getline(cin,q);
				} while (q == "\0");

				newnode->speakers.InsertFU(sp,q);
				newnode->numofspeakers++;
				cout << "Enter more speakers? (1-yes)";cin>>yesno;
				cin.ignore();
			}
		}
		newnode->left   = NULL;
		newnode->right  = NULL;
		newnode->height = 1;  // new node is initially added at leaf
		return(newnode);
	}
	// A utility function to right rotate subtree rooted with y
	// See the diagram given above.
	Node2 *rightRotate( Node2 *y)
	{
		Node2 *x = y->left;
		Node2 *T2 = x->right;

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
	Node2 *leftRotate(Node2 *x)
	{
		Node2 *y = x->right;
		Node2 *T2 = y->left;

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
	int getBalance(Node2 *N) 
	{
		if (N == NULL)
			return 0;
		return height(N->left) - height(N->right);
	}
	void Insert( int value )
	{
		Root = insert (Root,value);
		//int test4=0;
	}
	Node2* insert(Node2* node, int value)
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
	Node2 * minValueNode(Node2* node) // we have to give this node root->right // what this does is
		// it gets the minimum value from the right of the tree
	{
		Node2* current = node;

		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
			current = current->left;

		return current;
	}
	Node2 * maxValueNode(Node2* node) // we have to give this node root->left
		// gets the  maximum value from the left of the tree
	{
		Node2* current = node;

		/* loop down to find the rightmost leaf */
		while (current->right != NULL)
			current = current->right;

		return current;
	}	
	void Delete (int value)
	{
		Root = deleteNode(Root, value);
	}
	Node2* deleteNode(Node2* root, int value)
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
				Node2 *temp = root->left ? root->left : root->right;

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
				Node2* temp = minValueNode(root->right);
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
	void preOrder(Node2 *root)
	{
		if(root != NULL)
		{
			cout << "Seminar ID :" << root->id  << "\n" << "Venue: " << root->venue << "\n" << "Start time : "<< root->start_time << "\nEnd time: " << root->end_time << "\n"; 
			root->speakers.Display(); 
			cout << endl;
			preOrder(root->left);
			preOrder(root->right);
		}
	}
	void inOrder(Node2 *root)
	{
		if(root != NULL)
		{
			/*if(root == NULL)
				cout << "No seminars found!\n";*/
			inOrder(root->left);
			cout << "Seminar ID :" << root->id  << "\n" << "Venue: " << root->venue << "\n" << "Start time : "<< root->start_time << "\nEnd time: " << root->end_time << "\n"; 
			root->speakers.Display(); 
			cout << endl;
			inOrder(root->right);
		}
	}
	void postOrder (Node2 * root)
	{
		if(root != NULL)
		{
			postOrder(root->left);
			postOrder(root->right);

			cout << "Seminar ID :" << root->id  << "\n" << "Venue: " << root->venue << "\n" << "Start time : "<< root->start_time << "\nEnd time: " << root->end_time << "\n"; 
			root->speakers.Display(); 
			cout << endl;
			
		}
	}
	int Count ()
	{
		return Count(Root);
	}
	int Count(Node2 * node)
	{
		if ( node == NULL )
			return 0;

		return ( Count(node->left) + Count(node->right) + 1 );
	}
	int FindMin () // uses the binary search tree property of the AVL Tree
	{
		Node2* Temp = Root;
		while ( Temp->left != NULL )
			Temp = Temp->left;

		return Temp->id;
	}
	int FindMax () // uses the binary search tree property of the AVL Tree
	{
		Node2* Temp = Root;
		while ( Temp->right != NULL )
			Temp = Temp->right;

		return Temp->id;
	} 
	void Find (int value)
	{
		Find(Root, value);
	}
	void Find (Node2* node, int value)
	{
		if ( node == NULL )	
		{
			cout << "Seminar " << value <<" not found in the tree." << endl;
			return;
		}
		if ( node->id < value )
			Find ( node->right,value );
		else if ( node->id > value )
			Find ( node->left,value );
		else // Found!
		{
			cout << "Seminar ID : " << node->id << "\nVenue : " << node->venue << "\nStarting Time : " << node->start_time << "\nEnding Time : " << node->end_time << "\nNumber Of Speakers : " << node->numofspeakers <<"\nSpeakers are : \n" ; 
			node->speakers.Display(); 
		}
	}
	void Edit (int value)
	{
		Edit(Root, value);
	}
	void Edit (Node2* node, int value)
	{
		if ( node == NULL )	{
			cout << "Seminar " << value <<" does not exist!" << endl;
			return;
		}
		/// CHANGES MADE
		if ( node->id < value )
			Edit ( node->right,value );
		else if ( node->id > value )
			Edit ( node->left,value );
		else // Found!
		{
			cout << "What do you want to modify? \n";
			cout << "\t1 - Venue\n\t2 - Starting Time\n\t3 - Ending Time\n\t4 - Speakers\n";
			int opti;
			cin >> opti;
			cin.ignore();
			switch(opti)
			{
			case 1:
				//edit venue
				cout << "The current venue is : " << node->venue << endl;
				do {
				cout << "Enter new venue : ";
				getline (cin,node->venue);
				} while (node->venue == "\0");
				cout << "ID: " <<node->id << "\nVenue: " << node->venue << "\nStart time: " << node->start_time << "\nEnd Time: " << node->end_time << "\n" ; node->speakers.Display(); 
		
				break;
			case 2:
				//edit start_time
				cout << "The current starting time is : " << node->start_time << endl;
				do {
				cout << "Enter new starting time : ";
				getline(cin,node->start_time);
				} while (node -> start_time == "\0");
				cout << "ID: " <<node->id << "\nVenue: " << node->venue << "\nStart time: " << node->start_time << "\nEnd Time: " << node->end_time << "\n" ; node->speakers.Display(); 
		
				break;
			case 3:
				//edit end_time
				cout << "The current ending time is : " << node->end_time << endl;
				do {
				cout << "Enter new ending time : ";
				getline(cin,node->end_time);
				} while (node->end_time ==  "\0");
				cout << "ID: " <<node->id << "\nVenue: " << node->venue << "\nStart time: " << node->start_time << "\nEnd Time: " << node->end_time << "\n" ; node->speakers.Display(); 
		
				break;
			case 4:
				//edit speaker
				cout << "Enter the ID of the speaker : ";
				int spID;
				cin >> spID;
				// CHANGE
				cin.ignore();
				node->speakers.Edit(spID);
				break;

			default:
				break;
			}

			}
	}
	void DeleteTree ()
	{
		int i = DeleteTree(Root,0);
		Root = NULL;
		if (i!=0)cout << "All seminars have been deleted!\n";
		else if (i == 0) cout << "No seminars exist! \n";
	}
	int DeleteTree(Node2 * node,int del)
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
		filEiD = fileID;
		str <<"Seminar" << fileID <<".txt";
		filename = str.str();

		myFile.open(filename.c_str(), ios::out);
		myFile << maxid << " ";
		write(Root);
	}
	void write(Node2*temp)
	{	
		if(myFile.is_open(), ios::out)
		{
			if(temp != NULL)
			{
				int len = temp->venue.length();						
				while (len)
				{
					if(temp->venue[len-1] == ' ')
						temp->venue[len-1] = '_';
					len--;
				}
				int len2 = temp->start_time.length();
				while (len2)
				{
					if(temp->start_time[len2-1] == ' ')
						temp->start_time[len2-1] = '_';
					len2--;
				}
				int len3 = temp->end_time.length();
				while (len3)
				{
					if(temp->end_time[len3-1] == ' ')
						temp->end_time[len3-1] = '_';
					len3--;
				}

				write(temp->left);
				myFile << temp->id << " " << temp->venue << " " << temp->start_time << " " << temp->end_time << " "<<  temp->numofspeakers<< " " << temp->speakers.returnforfile() << temp->height << endl;
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
		// do nothing;
		// CHANGES MADE
		else
		{		IF.close();
		inFile.open(fylename,ios::app);
		if(inFile.is_open())
			inFile>>this->maxid;
		Read(Root);
		int test5 = 0;
		}
	}	
	void Read(Node2*root)
	{

		if(inFile.is_open())   
		{
			while(!inFile.eof())
			{
				inFile >> id;
				Insert(id);
			}
		}
		else
		{
			cout<<"File didn't open.";
			ReaD=1;
		}
	}
};
#endif