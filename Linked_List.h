#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;


int ID1 = 0;
struct Node3
{
public:
	int id;
	string speakername;
	string qualification;

	Node3 *Next;
	Node3 ()
	{
		Next = NULL;
		id = 0;
	}
	
	
};
class Linked_List 
{
	Node3 * Head;
	int ID1;
public:
	
	Linked_List () 
	{  
		Head = NULL;
		ID1 = 0;
	}

	
	void Insert (int id, string spname, string qual)
	{
		Node3 * New = new Node3;

		New->id = id;
		New ->speakername = spname;
		New->qualification=qual;
		ID1 = id;

		if (Head == NULL)
			Head = New;
		else
		{
			New->Next = Head->Next;
			Head->Next = New;
		}

	}
	  void InsertFU ( string spname, string qual)
	{
		Node3 * New = new Node3;

		New->id = ++ID1;
		New ->speakername = spname;
		New->qualification=qual;
		

		if (Head == NULL)
			Head = New;
		else
		{
			New->Next = Head->Next;
			Head->Next = New;
		}
	  }
		
	void Delete (int identity) // given just the ID
	{
		Node3 * Temp = Head;
		Node3 * T = NULL;
		while (  Temp != NULL && Temp->id != identity) 
		{
			T = Temp;
			Temp = Temp->Next;
		}
		
		if ( Temp == NULL  )
			cout << "Seminar does not exist." << endl;
		else if ( Head ->id = identity )
		{
			delete Head;
			Head = NULL;
		}
		else
		{
			T->Next = Temp->Next;
			delete Temp;
			Temp = NULL;
		}
		
	}
		
	void Search ( int identity )// we search, given the identity
	{
		Node3 * Temp = Head;		
		while (  Temp != NULL && Temp->id != identity ) 
			Temp = Temp->Next;
		
		if ( Temp == NULL )
			cout << "No speakers." << endl;
		else if ( Temp->id == identity  )
		{
			cout << "Speaker found!" << endl;
			cout << "Speaker Name : " << Temp->speakername << endl;
			cout << "Qualification : " << Temp->qualification << endl;
		}
	}
			
	void Edit ( int identity )// we search, given the identity
	{
		Node3 * Temp = Head;		
		while (  Temp != NULL && Temp->id != identity ) 
			Temp = Temp->Next;
		
		if ( Temp == NULL )
			cout << "Speaker does not exist." << endl;
		else if ( Temp->id == identity  )
		{
			cout << "Speaker found!" << endl;
			cout << "Speaker Name : " << Temp->speakername << endl;
			cout << "Qualification : " << Temp->qualification << endl;
			
			do {
				cout << "Enter new speaker name : " ;
			getline(cin, Temp->speakername);
			} while (Temp->speakername == "\0");
			do {
			cout << "Enter new qualification : ";
			
			getline(cin,Temp->qualification);
			} while (Temp->qualification == "\0" );
		}
	}
	
	string returnforfile ()// we search, given the identity
	{
		stringstream ss;
		Node3 * Temp = Head;
		while ( Temp!= NULL )
		{
			ss  << Temp->id << " " << Temp->speakername  << " " << Temp->qualification << " ";
			Temp = Temp->Next;
		}
		string strring;
		strring=ss.str();
		return strring;
	}
	
	void Display ()
	{
		Node3 * Temp = Head;
		while ( Temp )
		{
			cout << "Speaker ID : " << Temp->id  << " \nSpeaker Name : " <<  Temp->speakername  << "\nQualification : " << Temp->qualification<<endl;
			Temp = Temp->Next;
		}
	}
};

#endif