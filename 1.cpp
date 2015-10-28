#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <conio.h>
#include "HashTable.h"
#include "People.h"
#include "Dijkstra.h"
#include <Windows.h>

using namespace std;

void ConstructTable();
void readfile();
void writefile();
int select_options();
HashTable Table;
void startup ();
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void password();
void Accounts();


int main()
{
	system( "color 3F" );
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	SetConsoleTitle("Conference Management System - Data Structures and Algorithms ");
	startup();	
	reaD=0;	
	cout << "Loading data..." << endl;
	ConstructTable();
	
	system("cls");
	reaD=1;
	ReaD=1;
	Accounts();
	system ("pause");
	return 0;
}





void startup()	
{
	string str = "\n\n\n\t\t\t DATA STRUCTURES AND ALGORITHMS    \n  \n\t\t\t      END SEMESTER PROJECT     \n\n\t\t\t  CONFERENCE MANAGEMENT SYSTEM \n \n\n\t\t\t BY: \n\n\t\t\tASBAH ASHFAQ  256\n\t\t\tFARIA KALIM   259\n\n\n\n\n\n\n \t\t\t\t    BESE-2A\n";

	for(int index = 0; index < str.length(); index++ )
		cout << str[index];
}

void Accounts ()
{

	int num = 0;

	do
	{
		cout << "Press 1 for attendees \nPress 2 for admin:" << endl;
		cout << "Press 3 to exit:" << endl;
		cin >> num;
		if ( num == 1 )					//attendees
		{
			system ("cls");
			cout << "Attendee ID: ";
			cin >> num;
			cout << "Conference ID : ";
			int confID =0;
			cin >> confID;
			if ( Table.FindUSER(confID, num) )
			{
				int n = 0;
				do {

					cout << "Press 1 to see the shortest paths around NUST:" << endl;						//menu alert!!!
					cout << "Press 2 to view your conference schedule:" << endl;			
					cout << "Press 3 to return to accounts: "<< endl;
					cout << "Press any other number to exit:" << endl;
					cin >> n;


					if ( n == 1)
						NUSTShortestPath();
					else if ( n== 2 )
						Table.DisplayAllSeminars(confID);
					else if ( n == 3 )
						Accounts();
					else
						{
							cout << "Shutting down..." << endl;
							Table.AddToFiles();
							writefile();
							exit (0);
					}

				} while (n == 1 || n== 2 );

			}
			else
			{
				num = 3;
				cout <<  "Please select account again: "<< endl;
			}
		}
		else if ( num == 2 )				//admin
		{

			password();
			
			int option;
			char again='y';
			do{
				int option = select_options();												//menu alert!!!!
				
				switch (option)
				{
				case 1:
					//create new conference
					Table.Insert();

					break;
				case 2:																	
					//modify a conference											✓Check
					int IDtomodify;
					cout << "Enter the ID of the conference : ";
					cin >> IDtomodify;
					Table.Edit(IDtomodify);
					break;
				case 3:
					//modify attendees
					int iD;
					cout << "Enter the ID of the conference : ";
					cin >> iD;
					Table.AttendeeMenu(iD);
					break;
				case 4:
					//modify seminars													"delete a seminar" is left. 
					cout << "Enter the ID of the conference : ";
					int num;
					cin >> num;
					Table.Modify(num);
					break;
				case 5:
					//view a conference's details										✓check
					int IDtodisplay;
					cout << "Enter the ID of the conference to display : ";
					cin>>IDtodisplay;
					Table.Display(IDtodisplay);		
					break;
				case 6:
					//view all conferences												✓check
					Table.DisplayAll();
					break;
				case 7:
					//delete an existing conference										✓check
					int p;
					cout << "Please enter the ID of the conference to be deleted:" << endl;
					cin >> p;
					Table.Delete(p);
					break;
				case 8:
					//delete all the conferences										✓check
					Table.DeleteAll();													
					break;
				case 9:
					Accounts();
					break;
				case 10:
					cout << "Shutting down..." << endl;
					Table.AddToFiles();
					writefile();
					exit (0);
					break;
				default:
					cout << "Incorrect choice!" << endl;
					break;

				}
				cout << "Press 'y' to continue, any other key to exit:";
				again = getch();
				system ("cls");
			}
			while(again == 'y'||again == 'Y');
			cout << "Shutting down..." << endl;
			Table.AddToFiles();
			writefile();
			exit (0);
		}
		else if  ( num == 3 ){
			cout << "Shutting down..." << endl;
			Table.AddToFiles();
			writefile();
			exit (0);
			}
		else
			cout << "Incorrect choice: " << endl;
	} while ( num != 1 && num != 2);
}

void password()
{
	string password ="";
	char ch;
	int number=-1;

	cout << "Please Note that password should not exceed 10 digits" << endl;
	cout << "Enter your password: ";
	ch = _getch();
	for (int i =1; i<10; i++)
	{
		password.push_back(ch);
		
		cout << "*";
		
		ch = getch();
		while (ch == '\b')
		{
			if(i>0)
			{
				password.pop_back();
				i--;
				cout << "\b" << " " << "\b";
			}
			ch=getch();
		}

	}
	cout << endl;

	if(password == "nustseecs")
	{ 
		cout << "Access Granted." << endl;
	}
	else 
	{
		cout << "Access Denied." << endl; 
		system ("pause");
		Accounts();
	}

}

void ConstructTable () 
{

	readfile();
	for ( int i = 0; i < Files.size(); i ++ )
	{
		int asdf = 0;
		if ( Files[i].size() > 0 )
		{
			int pos =  Files[i].find (' ');
			string sub = Files[i].substr(0,pos);
			Files[i].erase (0, pos+1);
			pos = Files[i].find(' ');
			string name = Files[i].substr(0, pos);
			Files[i].erase(0, pos+1);
			pos = Files[i].find(' ');
			string startdate =  Files[i].substr(0,pos);
			Files[i].erase(0,pos+1);
			string enddate = Files[i].substr(0, Files[i].size());
			int value = 0;
			for ( int i = sub.length()-1; i >= 0; i-- )// starting from the end
				value += (sub[i]-48) * pow(10.0, static_cast<double>(sub.length()-1-i));

			Table.InsertFromFile(value, name, startdate, enddate);
			Table.ConstructTree(value);
		}
	}
}

void readfile ()
{
	ifstream InFile(FileName, ios::app);
	if ( InFile.good())
	{
		while  ( !InFile.eof() )
		{
			string Name;
			getline (InFile, Name, '\n' );				//simple int n string			
			Files.push_back(Name);
		}
		InFile.close();
		if ( Files.size ()  <= 1 )
			ID = 0; 
		else
		{
			string temp = Files[Files.size()-2/*1*/];
			int pos =  temp.find (" ", 0);
			string sub ;
			sub = temp.substr(0,pos);
			int value = 0;
			for ( int i = sub.length()-1; i >= 0; i-- )// starting from the end
				value += (sub[i]-48) * pow(10.0, static_cast<double>(sub.length()-1-i));
			ID = value;
		}
	}
	else
		cout << "Error: File did not open." << endl;
}

void writefile ()
{
	ofstream OutFile;
	OutFile.open(FileName);
	if ( OutFile.good() )
	{
		for ( int i = 0; i < Files.size(); i++ )
		{OutFile << Files[i] << endl;

		}

	}
	else
		cout << "Error: File did not open"<< endl;
	Table.Writetrees();
}

int select_options()
{
	cout << "Select an option : \n";
	cout << "\t1 - Create a new conference \n";
	cout << "\t2 - Modify a conference\n";
	cout << "\t3 - Attendees\n";
	cout << "\t4 - Seminars\n";
	cout << "\t5 - View a conference \n";
	cout << "\t6 - View all conferences \n";
	cout << "\t7 - Delete a conference \n";
	cout << "\t8 - Delete all conferences \n";
	cout << "\t9 - Exit to accounts menu \n";
	cout << "\t10 - Exit \n";
	

	int option;
	cin>>option;

	return option;
}
