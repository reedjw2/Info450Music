// Info450MusicList.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
// list Node Class
class node
{
	string data;
	node *next;
public:
	node(string x);
	friend class linkedList;
};

node::node(string x)
{
	data = x;
	next = NULL;
}

// Linked List Class
class linkedList
{
	node *head;
	node *tail;
public:
	linkedList();
	int ReadMusicList(string filename);
	int SaveMusicList(string filename);
	void addNodeToEnd(node *nptr);
	void addNodeToHead(node *nptr);
	int insertAfter(node *ptr, string i);
	int removeNode(string i);
	void showList();
	node * findItem(string i);
};

linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}

int linkedList::ReadMusicList(string filename)
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

			addNodeToEnd(new node(sname));
			count++;
		}
	}
	infile.close();
	return 0;
}

int linkedList::SaveMusicList(string filename)
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

void linkedList::showList()
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
		cout << "Next up! " << ptr->data << endl;
		cout << "(P)lay, (S)kip, (A)dd, (D)elete, (Q)uit" << endl;
		cin >> answer;
		if (answer == 'p' || answer == 'P')
		{
			cout << "Now Playing: " << ptr->data << endl;
			ptr = ptr->next;

		}
		else if (answer == 's' || answer == 'S')
		{
			int skipNumber;
			cout << "Skip how many songs?" << endl;
			cin >> skipNumber;
			for (int i = 0; i < skipNumber; i++)
			{
				if (ptr == NULL)
				{
					ptr = head;
				}
				cout << "Skipping: " << ptr->data << endl;
				ptr = ptr->next;


			}
		}

		else if (answer == 'a' || answer == 'A')
		{
			cin.ignore();
			cin.clear();
			string songTitle;
			cout << "What is the name of your new song?" << endl;
			getline(cin, songTitle);
			insertAfter(new node(songTitle), ptr->data);
			cout << "Song Added!" << endl;
		}

		else if (answer == 'd' || answer == 'D')
		{
			string deletenode = ptr->data;
			ptr = ptr->next;
			removeNode(deletenode);


		}
		else
		{
			return;
		}
	}
	if (ptr == NULL)
	{
		ptr = head;
		showList();
	}
}

void linkedList::addNodeToEnd(node *ptr)
{
	// if list is empty
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

void linkedList::addNodeToHead(node *ptr)
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

int linkedList::insertAfter(node *newnode, string i)
{
	node *ptr = head;
	while (ptr != NULL)
	{
		if (ptr->data == i) // we found the node to insert after
		{
			newnode->next = ptr->next;
			ptr->next = newnode;
			if (tail == ptr) // repoint tail if we added to end
				tail = newnode;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

node * linkedList::findItem(string i)
{
	node *ptr;
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->data == i)
		{
			cout << "found it!" << endl;
			return ptr;
		}
		ptr = ptr->next;
	}

	cout << "Not found" << endl;
	return NULL;
}


int linkedList::removeNode(string i)
{
	node *ptr = head;
	if (ptr == NULL)  // empty list
		return -1;

	// if node is at the head
	if (head->data == i)
	{
		//if only 1 node in the list
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
	linkedList *mylist = new linkedList();
	cout << "What is the file path to your music?" << endl;
	getline(cin, musicFile);
	mylist->ReadMusicList(musicFile);
	mylist->showList();
	mylist->SaveMusicList(musicFile);

	return 0;
}
