/#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;

class node
{
	string data;
	node *next;
public:
	node(string x);
	friend class linkList;
};

node::node(string x)
{
	data = x;
	next = NULL;
}


class linkList
{
	node *head;
	node *tail;
public:
	linkList();
	int ReadInList(string filename);
	int SaveList(string filename);
	void addEndNode(node *nptr);
	void addHeadNode(node *nptr);
	int insertAfterSong(node *ptr, string i);
	int nodeRemoval(string i);
	void showMusicList();
	node * findSong(string i);
};

linkList::linkList()
{
	head = NULL;
	tail = NULL;
}

int linkList::ReadInList(string filename)
{
	int count = 0;
	string sname;
	ifstream infile(filename, ios::in);

	if (!infile)
	{
		cout << "File could not be opened for reading" << endl;
		return READERROR;
	}

	while (!infile.eof())
	{
		getline(infile, sname);
		if (!sname.empty()) {
			if (count == 0)
			{
				node *newnode = new node(sname);
				count++;
			}

			addEndNode(new node(sname));
			count++;
		}
	}
	infile.close();
	return 0;
}

int linkList::SaveList(string filename)
{
	ofstream output(filename, ios::trunc);
	if (!output)
	{
		cout << "Could not write to file!" << endl;
		return WRITEERROR;
	}
	if (output)
	{
		node *ptr;
		ptr = head;
		while (ptr != NULL)
		{
			output << ptr->data << endl;
			ptr = ptr->next;
		}
	}
	output.close();
	return 0;
}

void linkList::showMusicList()
{
	node *ptr;
	ptr = head;
	char answer;
	if (ptr == NULL)
	{
		cout << "list is empty " << endl;
		return;
	}

	while (ptr != NULL)
	{
		cout << "Next Song " << ptr->data << endl;
		cout << "Press P for play, S for skip, A for add song, D to delete song, Q to quit song" << endl;
		cin >> answer;
		if (answer == 'p' || answer == 'P')
		{
			cout << "Current Song: " << ptr->data << endl;
			ptr = ptr->next;

		}
		else if (answer == 's' || answer == 'S')
		{
			int skipNumber;
			cout << "How many songs would you like to skip" << endl;
			cin >> skipNumber;
			for (int i = 0; i < skipNumber; i++)
			{
				if (ptr == NULL)
				{
					ptr = head;
				}
				cout << "Skipping song " << ptr->data << endl;
				ptr = ptr->next;


			}
		}

		else if (answer == 'a' || answer == 'A')
		{
			cin.ignore();
			cin.clear();
			string songTitle;
			cout << "What is the name of ths song you would like to add" << endl;
			getline(cin, songTitle);
			insertAfterSong(new node(songTitle), ptr->data);
			cout << "Your new song has been added" << endl;
		}

		else if (answer == 'd' || answer == 'D')
		{
			string deletenode = ptr->data;
			ptr = ptr->next;
			nodeRemoval(deletenode);


		}
		else
		{
			return;
		}
	}
	if (ptr == NULL)
	{
		ptr = head;
		showMusicList();
	}
}

void linkList::addEndNode(node *ptr)
{

	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

void linkList::addHeadNode(node *ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		ptr->next = head;
		head = ptr;
	}
}

int linkList::insertAfterSong(node *newnode, string i)
{
	node *ptr = head;
	while (ptr != NULL)
	{
		if (ptr->data == i) 
		{
			newnode->next = ptr->next;
			ptr->next = newnode;
			if (tail == ptr) 
				tail = newnode;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

node * linkList::findSong(string i)
{
	node *ptr;
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->data == i)
		{
			cout << "we found the song you were looking for" << endl;
			return ptr;
		}
		ptr = ptr->next;
	}

	cout << "Unable to find the song you were looking for" << endl;
	return NULL;
}


int linkList::nodeRemoval(string i)
{
	node *ptr = head;
	if (ptr == NULL)  
		return -1;

	
	if (head->data == i)
	{
		
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
		delete ptr;
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (ptr->next)->data == i)
		{
			if (tail == ptr->next)
				tail = ptr;
			node *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

int main()
{
	string musicFile;
	linkList *mylist = new linkList();
	cout << "What is the file location of your music playlist?" << endl;
	getline(cin, musicFile);
	mylist->ReadInList(musicFile);
	mylist->showMusicList();
	mylist->SaveList(musicFile);

	return 0;
}

