#ifndef HashTable_H
#define HashTable_H

# include <iostream>
# include <vector>
# include <fstream>
# include <string>
# include <cmath>
#include <sstream>
#include "People.h"
#include "Seminar.h"
#include <Windows.h>

using namespace std;


class HashTable;
string FileName = "HashTable.txt";
vector <string> Files; 
int ID = 0;

struct Node1
{
public:
	People P;
	Seminar S;
	int id;
	string Name;
	string startdate;
	string enddate;
	string PeopleFileName;
	string SeminarFileName;
	Node1 *Next;
	Node1 ()
	{
		Next = NULL;
		Name = startdate = enddate = "\0";
		id = 0;
		SeminarFileName = PeopleFileName = Name = "\0";
	}
	void getdata ()
	{
		cin.ignore();
		cout << "Enter the following information about the conference : \n";

		do {
			cout << "Name : ";
			getline(cin,Name); 
		} while (Name == "\0");
		do {
			cout << "Starting date : ";		getline(cin,startdate);
		} while (startdate == "\0");
		do {cout << "Ending date : ";		getline(cin,enddate); } while (enddate == "\0");
		cout << "The Conference ID is : "  << ID << endl;
		id = ID;
		SeminarFileName = "Seminars" + Name + ".txt";
		PeopleFileName = "People" + Name + ".txt";

		string Result;          // string which will contain the result
		ostringstream convert;   // stream used for the conversion
		convert << id;      // insert the textual representation of 'Number' in the characters in the stream
		Result = convert.str();
		string test = "People" + Result + ".txt";
		ofstream OutFile (test,ios::app);
		test = "Seminar" + Result + ".txt";
		OutFile.close();
		OutFile.open(test, ios::app);
		OutFile.close();

	}
};
class LinkedList 
{
	Node1 * Head;
public:
	LinkedList () {  Head = NULL; }

	void Insert ()
	{
		Node1 * New = new Node1;
		New->getdata(); 

		// insert at head

		if (Head == NULL)
			Head = New;
		else
		{
			New->Next = Head->Next;
			Head->Next = New;
		}
	}
	void Insert (int id, string name, string start, string end)
	{
		Node1 * New = new Node1;
		New->id = id;
		New ->Name = name;
		New->startdate=start;
		New->enddate=end;

		stringstream str,str1;

		str<<"People"<<id<<".txt";
		New->PeopleFileName=str.str();

		str1<<"Seminar"<<id<<".txt";
		New->SeminarFileName =str1.str();


		if (Head == NULL)
			Head = New;
		else
		{
			New->Next = Head->Next;
			Head->Next = New;
		}
	}
	void Delete (int identity)
	{
		Node1 * Temp = Head;
		Node1 * T = NULL;
		while (  Temp != NULL && Temp->id != identity) 
		{
			T = Temp;
			Temp = Temp->Next;
		}

		if ( Temp == NULL  )
		{
			cout << "Conference does not exist." << endl;
			return;
		}
		else if ( Head ->id == identity )
		{

			string Result;          // string which will contain the result
			ostringstream convert;   // stream used for the conversion
			convert << Head->id;      // insert the textual representation of 'Number' in the characters in the stream
			Result = convert.str();
			string test = "People" + Result + ".txt";
			const char * p ;
			p = test.c_str();
			int A = remove (p);
			if ( A != 0 )
			{
				ofstream InFile (test, ios::out);
				InFile << "\0";
				InFile.close();
			}
			test = "Seminar" + Result + ".txt";
			const char * c ;
			c = test.c_str();
			A = remove (c);
			if ( A != 0 )
			{
				ofstream InFile (test, ios:: out);
				InFile << "\0";
				InFile.close();
			}

			delete Head;
			Head = NULL;
			cout << "Conference has been deleted!\n";

		}
		else
		{
			/// CHANGES MADE

			// number to be converted to a string
			string Result;          // string which will contain the result
			ostringstream convert;   // stream used for the conversion
			convert << identity;      // insert the textual representation of 'Number' in the characters in the stream
			Result = convert.str();
			string test = "People" + Result + ".txt";
			const char * p ;
			p = test.c_str();
			int A = remove (p);
			if ( A != 0 )
			{
				ofstream InFile (test, ios:: out);
				InFile << "\0";
				InFile.close();
			}
			test = "Seminar" + Result + ".txt";
			const char * c ;
			c = test.c_str();
			A = remove (c);
			if ( A != 0 )
			{
				ofstream InFile (test, ios:: out);
				InFile << "\0";
				InFile.close();
			}

			T->Next = Temp->Next;
			delete Temp;
			Temp = NULL;
		}
	}

	int Delete ()
	{
		if ( Head == NULL )
			return 0;
		else
		{
			Node1 * Temp = Head;
			Node1 * T = NULL;
			if(Temp == NULL)
			{
				return 0;
			}
			while (  Temp != NULL ) 
			{
				T = Temp;
				Temp = Temp->Next;

				string Result;          // string which will contain the result
				ostringstream convert;   // stream used for the conversion
				convert << T->id;      // insert the textual representation of 'Number' in the characters in the stream
				Result = convert.str();
				string test = "People" + Result + ".txt";
				const char * p ;
				p = test.c_str();
				int	A = remove (p);
				if ( A != 0 )
				{
					ofstream InFile (test, ios:: out);
					InFile << "\0";
					InFile.close();
				}
				test = "Seminar" + Result + ".txt";
				const char * c ;
				c = test.c_str();
				A = remove (c);
				if ( A != 0 )
				{
					ofstream InFile (test, ios:: out);
					InFile << "\0";
					InFile.close();
				}
				delete T;
				
			}
			Head = NULL;
			cout << "All conferences have been deleted!\n";
			return 1;
		}

	}

	void Search ( int identity )// we search, given the identity
	{
		Node1 * Temp = Head;
		while (  Temp != NULL && Temp->id != identity ) 
			Temp = Temp->Next;

		if ( Temp == NULL )
			cout << "Conference does not exist." << endl;
		else if ( Temp->id == identity  )
		{
			//cout << "Conference found!" << endl;
			Temp->S.InOrder();
		}
	}

	int  FINDUSER ( int identity, int userid )// we search, given the identity
	{
		Node1 * Temp = Head;
		while (  Temp != NULL && Temp->id != identity ) 
			Temp = Temp->Next;

		if ( Temp == NULL )
			{cout << "Conference does not exist." << endl;
		return 0;
		}
		else if ( Temp->id == identity  )
		{
			// check if user exists,
			int check  = Temp->P.Find(userid);
			return check;
		}
	}
	void Searchtowrite (  )
	{
		Node1 * Temp = Head;
		while ( Temp!= NULL )
		{
			Temp->P.createfile(Temp->id);
			Temp->S.createfile(Temp->id);
			Temp = Temp->Next;
		}
	}
	void Modify ( int identity )
	{
		Node1 * Temp = Head;		
		while (  Temp != NULL && Temp->id != identity ) 
			Temp = Temp->Next;

		if ( Temp == NULL )
			cout << "Conference does not exist." << endl;
		else if ( Temp->id == identity  )
		{
			cout << "Conference found!" << endl;
	
				switch(opties())
				{
				case '1':
					cout << "The current name is : " << Temp->Name << endl;
					do {
						cout << "Enter new name : "; 
						cin.ignore();
						getline(cin,Temp->Name);
					} while (Temp->Name == "\0");
					break;
				case '2':
					cout << "The current starting date is : " << Temp->startdate << endl;
					do {
						cout << "Enter new starting date : "; 
						cin.ignore();
						getline(cin,Temp->startdate);
					} while (Temp->startdate == "\0");
					break;
				case '3':
					cout << "The current ending date is : " << Temp->enddate << endl;
					do 
					{
						cout << "Enter new ending date : "; 
						cin.ignore();
						getline(cin,Temp->enddate);
					} 
					while (Temp->enddate == "\0");
					break;
				
				default:
					cout << "Invalid option! "<< endl;
					Sleep(1000);
					cout << "Select Again!\n";
					Modify(identity);

				}
				


		}
	}

	void ModifyAttendees(int identity)
	{
		Node1 * Temp = Head;		
		while (  Temp != NULL && Temp->id != identity ) 
			Temp = Temp->Next;

		if ( Temp == NULL )
			cout << "Conference does not exist." << endl;
		else if ( Temp->id == identity  )
		{
			cout << "Conference found!" << endl;
			switch(options())
			{
			case '1':
				//register new member
				Temp->P.Insert(Temp->P.maxid++);
				break;
			case '2':
				//modify a member														✓check
				cout << "Enter the ID of the member to be modified : ";
				int iid ;
				cin >> iid;
				Temp->P.Edit(iid);
				break;
			case '3':
				//view a member															✓check
				cout << "Enter the ID of the member to be found : ";
				int Id ;				
				cin >> Id;				
				Temp->P.Find(Id);
				break;
			case '4':
				//view all members														✓check
				Temp->P.InOrder();
				break;
			case '5':
				//delete an attendee													UNCHECKED!!!!
				cout << "Enter the ID of the member to be deleted : ";
				int IdD; cin >> IdD;
				Temp->P.Delete(IdD);
				break;
			case '6':
				//delete all members													✓check
				Temp->P.DeleteTree();
				break;
			default:
				cout << "Invalid option! "<< endl;
				Sleep(1000);
				cout << "Select Again!\n";
				ModifyAttendees(identity);
				break;

			}
		}
	}

	void Modifyseminar ( int identity )// we search, given the identity
	{
		Node1 * Temp = Head;		
		while (  Temp != NULL && Temp->id != identity ) 
			Temp = Temp->Next;

		if ( Temp == NULL )
			cout << "Conference does not exist." << endl;
		else if ( Temp->id == identity  )
		{
			cout << "Conference found!" << endl;

			switch(optionx())
			{
			case '1':
				//add a seminar
				Temp->S.Insert(Temp->S.maxid++);
				break;
			case '2':
				//modify a seminar
				cout << "Enter the ID of the seminar to be modified : ";				//✓check
				int iid;
				cin >> iid;
				Temp->S.Edit(iid);
				break;
			case '3':
				//view a seminar
				cout << "Enter the ID of the seminar to be found : ";					//✓check
				int Id; cin >> Id;
				Temp->S.Find(Id);
				break;
			case '4':										
				//view all seminars														//✓check
				Temp->S.InOrder();
				break;
			case '5':
				//delete a seminar
				cout << "Enter the ID of the seminar to be deleted : ";					//UNCHECKED!!!!! 1-seminar not found 2-seminar deleted
				int IdD; cin >> IdD;
				Temp->S.Delete(IdD);
				break;
			case '6':
				//delete all seminar													//✓check						
				Temp->S.DeleteTree();
				break;
			default:
				cout << "Invalid option! "<< endl;
				Sleep(1000);
				cout << "Select Again!\n";
				Modifyseminar(identity);
				break;
			}
		}
	}
	void createtree ( int identity )
	{
		Node1 * Temp = Head;		
		while (  Temp != NULL && Temp->id != identity ) 
			Temp = Temp->Next;

		if ( Temp == NULL )
			cout << "Conference does not exist!." << endl;
		else if ( Temp->id == identity  )
		{
			Temp->P.read(identity+1,Temp->PeopleFileName);
			Temp->S.read(identity+1,Temp->SeminarFileName);
		}
	}
	char ops;
	char opties()
	{
		cout << "What do you want to change? \n";
		cout << "\t1-Name\n";
		cout << "\t2-Starting Date\n";
		cout << "\t3-Ending Date\n";

		cin>>ops;
		return ops;
	}

	char options()
	{

		cout << "Select your option :\n";
		cout << "\t1 - Register new attendee \n";
		cout << "\t2 - Edit an existing attendee \n";
		cout << "\t3 - View an attendee's info \n";
		cout << "\t4 - View all attendees \n";
		cout << "\t5 - Delete an existing attendee \n";
		cout << "\t6 - Delete all attendees \n";
		char op;
		cin >> op;
		return op;
	}
	char optionx()
	{
		cout << "Select your option :\n";
		cout << "\t1 - Add new seminar \n";
		cout << "\t2 - Edit an existing seminar \n";
		cout << "\t3 - View a seminar's info \n";
		cout << "\t4 - View all seminars \n";
		cout << "\t5 - Delete an existing seminar \n";
		cout << "\t6 - Delete all seminars \n";
		char num1;
		cin>>num1;
		cin.ignore();
		return num1;
	}
	void AddToFiles ()
	{
		Node1 * Temp = Head;
		while ( Temp != NULL )
		{
			string  name;
			stringstream ss;
			ss << Temp->id<< " "<<  Temp->Name << " "  << Temp->startdate << " " << Temp->enddate;
			name = ss.str() ;

			Files.push_back(name);
			Temp = Temp ->Next;
		}

	}
	int Display ()
	{
		Node1 * Temp = Head;
		if(Temp == NULL)
			return 0;
		else while ( Temp!= NULL )
		{
			cout << "Conference ID : " << Temp->id  << "\nConference Name : " <<  Temp->Name  << "\nStarting Date : " << Temp->startdate<< "\nEnding Date : " << Temp->enddate << endl;
			Temp = Temp->Next;
		}
		return 1;
	}
	void Display (int v)
	{
		Node1 * Temp = Head;
		while ( Temp!= NULL && Temp ->id != v )
		{
			Temp = Temp->Next;
		}
		if ( Temp == NULL )
			cout << "Conference not found." << endl;
		else if ( Temp ->id == v )
			cout << "Conference ID : " << Temp->id  << "\nConference Name : " <<  Temp->Name  << "\nStarting Date : " << Temp->startdate<< "\nEnding Date : " << Temp->enddate << endl;

	}
};
int HashFunction(int value)
{
	return (value%10);
}	
class HashTable
{
	LinkedList Arr[10];
public:
	
	void Insert ( )
	{
		++ID;
		Arr[HashFunction(ID)].Insert();
	}

	void InsertFromFile (int id, string name, string st, string end)
	{
		Arr[HashFunction(id)].Insert(id, name, st, end);
	}

	void Find (int identity )
	{
		Arr[HashFunction(identity)].Search(identity);
	}

	int FindUSER (int identity, int userid )
	{
		return Arr[HashFunction(identity)].FINDUSER(identity, userid);
	}

	void Edit (int identity )
	{
		Arr[HashFunction(identity)].Modify(identity);
	}

	void AttendeeMenu(int identity)
	{
		Arr[HashFunction(identity)].ModifyAttendees(identity);
	}

	void Modify(int identity)
	{
		Arr[HashFunction(identity)].Modifyseminar(identity);
	}

	void Delete ( int identity ) 
	{
		Arr[HashFunction(identity)].Delete(identity);
	}
	void DisplayAllSeminars (int confID)
	{
			Arr[HashFunction(confID)].Search(confID);

	}
	void DeleteAll()
	{
		int asdf=0;
		for(int i = 0; i<10; i++)		
			asdf += Arr[HashFunction(i)].Delete();
		if (asdf == 0)
			cout << "No conferences Exist!\n";
		ID = 0;
	}

	void AddToFiles ()
	{
		Files.clear();
		for ( int i = 0; i < 10; i ++ )
			Arr[i].AddToFiles();

		int ind_max = 0;
		int val_at_indmax =0;
		if ( Files.size() > 0 )
		{
			for ( int i  = 0; i < Files.size()-1; i++ ) // looking for the largest value  (so that we are able to compare the last two values
			{ 
				int pos =  Files[i].find (' ');
				string sub = Files[i].substr(0,pos);
				string name = Files[i].substr(pos, Files[i].size()-1);
				int value = 0;
				for ( int j = sub.length()-1; j >= 0; j-- )// starting from the end
					value += (sub[j]-48) * pow(10.0, static_cast<double>(sub.length()-1-j));

				pos =  Files[i+1].find (' ');
				sub = Files[i+1].substr(0,pos);
				name = Files[i+1].substr(pos, Files[i+1].size()-1);
				int value1 = 0;
				for ( int j = sub.length()-1; j >= 0; j-- )// starting from the end
					value1 += (sub[j]-48) * pow(10.0, static_cast<double>(sub.length()-1-j));

				if ( val_at_indmax < value1 || val_at_indmax < value )
				{
					if ( value1 > value )
					{
						ind_max = i+1;
						val_at_indmax = value1;
					}
					else
					{
						ind_max = i;
						val_at_indmax = value;
					}
				}
			}
			if ( ind_max != Files.size()-1 )// we shall swap
			{
				string temp = "\0";
				temp = Files[Files.size()-1];
				Files[Files.size()-1] = Files[ind_max];
				Files[ind_max] = temp;
			}
		}
	}

	void DisplayAll()
	{
		int qwerty=0;
		for ( int i = 0; i < 10; i++ )
		{
			qwerty += Arr[HashFunction(i)].Display();
			cout << endl;
		}
		if(qwerty==0)
			cout << "No Conferences Exist!\n";
	}

	void Display(int num)
	{
		// CHANGES MADE  HERE
		Arr[HashFunction(num)].Display(num);
	}

	void ConstructTree(int confID)
	{
		int test2=0;
		Arr[HashFunction(confID)].createtree(confID);
		int test3=0;
	}

	void Writetrees()
	{
		for ( int i = 0; i < 10; i++ )
		{
			Arr[HashFunction(i)].Searchtowrite();
		}
	}
};
#endif