// MyMusic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>




using namespace std;





	class MyMusic 
	{
	public:



		string getArtist;
		string getSong;
		string getAlbum;
		string getWriters;

		

		
	

	

private:
	
	
	//record
	string artist;
	string song;
	string album;
	string writers;


	string getSong();

	}

 



	class MyCollection
	{
	public:

		//constructor
		MyCollection();


		//destructor
		~MyCollection();


		void add(string, string, string, string);

		void remove();


		//move to next song in list
		void nextSong()


			//write to file
			void write(ofstream& ofs);
	



	private:


	
		MyMusic* head; //head of list
		MyMusic* currentSong;
	}


	//constructor
	MyMusic::MyMusic(string artist, string song, string album, string writers) {
		this->artist = artist;
		this->song = song;
		this->album = album;
		this->writers = writers;
		next = NULL;
	


	//get artist
		string MyMusic::getArtist()
		{
	
		return artist;
	}

	//get song
	string MyMusic::getSong() 
	{
		return song;
	}


	//get writers
	string MyMusic::getWriters() {
		return writers;
	}

	//get producers
	string MyMusic::getAlbum() {
		return album;
	}


	//go to next song
	MyMusic* MyMusic::getNext() {
		return next;
	}


	//set next
	void MyMusic::setNext(MyMusic* next) {
		this->next = next;
	}

	MyCollection::MyCollection() {
		head = NULL;
		currentSong = NULL;
	}


	MyCollection::~MyCollection() {
		MyMusic* temp; //delete node
		MyMusic* current = head;


		while (current != NULL)
		{
			temp = current;
			current = current->getNext();


			delete (temp);
		}
	}


	//add record
	void    MyCollection::add(string artist, string song, string writers, string album) {
		SongNode *newNode = new SongNode(artist, song, writers, album);
		if (head == NULL)
		{
			head = newNode;
			currentSong = newNode;
		}
		else {

			MyMusic *current = head;
			while (current->getNext() != NULL)
			{
				current = current->getNext();
			}

			current->setNext(newNode);
		}
	}

	void MyCollection::remove()
	{
	


	//remove current
	}
void MyCollection::remove() {

	if (head == NULL)
	{
		return;
	}


	MyMusic *prev = NULL;
	MyMusic *current = head;


	while (current != currentSong)
	{
		prev = current;
		current = current->getNext();
	}


	//current gets deleted
	if (prev == NULL)
	{//delete head node


		if (currentSong == head)
		{
			currentSong = head->getNext();
		}
		head = head->getNext();
	}
	
	else 
	{
			prev->setNext(current->getNext());
			currentSong = currentSong->getNext();
			if (currentSong == NULL)
			{
				currentSong = head;
			}
		}
	


	delete current;
}


void MyCollection::skip(int n) {


	if (head == NULL)
	{
		return;
	}


	for (int i = 0; i < n; i++)
	{
		//move current to end of list
		MyMusic *prev = NULL;
		MyMusic *current = head;


		while (current != currentSong)
		{
			prev = current;
			current = current->getNext();
		}



		//find tail node
		MyMusic *tail = head;
		while (tail != NULL && tail->getNext() != NULL)
		{
			tail = tail->getNext();
		}



		if (current == tail)
		{
			return;
		}



		if (prev == NULL)
		{


			head = head->getNext();


			current->setNext(NULL);
			tail->setNext(current);


			currentSong = head;
		}
		else {


			//set current song
			currentSong = currentSong->getNext();
			if (currentSong == NULL)
			{
				currentSong = head;
			}


			prev->setNext(current->getNext());
			current->setNext(NULL);
			tail->setNext(current);




		}
	}
}


//move to next song in list
void MyMusic::nextSong() {
	if (currentSong != NULL)
	{
		currentSong = currentSong->getNext();


		if (currentSong == NULL)
		{
			currentSong = head;
		}
	}
}


//get current song
SongNode* MyMusic::getCurrentSong() {
	return currentSong;
}


//write to file
void MyCollection::write(ofstream& ofs) {

	MyMusic *current = head;


	while (current != NULL)
	{
		//write to stream
		ofs << current->getArtist() << "," << current->getSong() << endl;


		current = current->getNext();
	}
}


int main() {


	//linked list
	MyCollection list;

	string filename;

	string line;

	string artist, song, writers, album;

	MyMusic *currentSong;


	//prompt for file name
	cout << "Please enter a full path filename of an existing Collections text file: ";
	getline(cin, filename);


	ifstream infile;
	infile.open(filename.c_str());


	if (infile.is_open()) {
		//read line by line
		while (!infile.eof()) {


			getline(infile, line);


			stringstream ss(line);
			getline(ss, artist, ',');
			getline(ss, song);
			getline(ss, album);
			getline(ss, writers);


			list.add(artist, song);
		}


		//close the opened file
		infile.close();
	}
	else {
		cout << "File not found" << endl;
	}


	//display menu
	string command = "";

	while (command != "0") {


		cout << "1. add song" << endl;
		cout << "2. next song" << endl;
		cout << "3. delete song" << endl;
		cout << "4. save to file" << endl;
		cout << "0. quit" << endl;


		cout << "Select ";
		getline(cin, command);


		if (command == "1")
		{
			cout << "Enter Artist Name: ";
			getline(cin, artist);


			cout << "Enter Song Title: ";
			getline(cin, song);

			cout << "Enter Album Title: ";
			getline(cin, album);

			cout << "Enter Writers: ";
			getline(cin, writers);


			list.add(artist, song, album, writers);

		}
	}

		else if (command == "2") {
			cout << "Enter n: ";
			getline(cin, line);


			istringstream iss(line);
			int n;
			iss >> n;


			list.skip(n);
		}
		else if (command == "3") {
			list.remove();
		}
		else if (command == "4") {


			ofstream outfile;
			outfile.open(filename.c_str());

			if (outfile.is_open()) {


				list.write(outfile);


				outfile.close();
			}
			else {
				cout << "Could not write to file" << endl;
			}
		}
		else if (command == "0") {


		}
		else {
			cout << "Invalid selection" << endl;




			return 0;

		}


		