/*
 * main.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: Chris Gregory
 */

#include <iostream>
#include "Database.h"
#include "Song.h"
#include <sstream>
#include <fstream>
using namespace std;

#include "ListTable.h"

/* ~ ~ ~ ~ Important Constants ~ ~ ~ ~ */
string file_name = "lyrics_fulldb.txt";
const bool show_progress = false;
const int skip_size = 1000;
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

void populate_database(string file_name, Database * database);
string make_alpha(string lyric);

int main(int argc, char *argv[]) {
	Database * database = new Database;
	
	if(argc == 2)
		file_name = argv[1];
	populate_database(file_name, database);

	// Keep getting search query input
	while(true) {
		string search;
		cin >> search;
		if(search == "<BREAK>")
			break;
		search = make_alpha(search);
		// Stop getting input

		//TODO: format input (multiple words, only symbols etc.)
		string word_to_search = search;

		database->print_results(word_to_search);
	}

	delete database;
	return 0;
}

/*
 * Adds all songs and their lyrics to the database from a file
 */
void populate_database(string file_name, Database * database) {
	const char * file_name_array = file_name.c_str();
	ifstream in(file_name_array);
	int song_count = 0;
	string artist, title, lyric;

	while (!in.eof()) {
		// Input artist
		getline(in, artist);
		if(in.fail())
			break;
		// Input title
		getline(in, title);
		if(in.fail())
			break;
		if(show_progress) {
			song_count++;
			if(song_count % skip_size == 0) {
				cout << "At " << song_count << " Artist: " << artist << 
						" Title: " << title << endl;
			}
		}
		Song * song = new Song(artist, title);
		// Read all lyrics until special <BREAK> token
		while(in >> lyric && lyric != "<BREAK>") {
			// Add the word to the song
			song->add_lyric(lyric);
			string word = make_alpha(lyric);
			song->add_word(word);
			// Add the word to the database
			database->add_word(word, song);
		}
		// Add the song to the database
		database->add_song(song);
		// Skip the newline left behind
		in.ignore();
	}
}

/*
 * Takes a string, converts it to lowercase, and removes all symbols
 */
string make_alpha(string lyric) {
	ostringstream oss;
	for(size_t i = 0; i < lyric.length(); i++)
		if(isalnum(lyric[i]))
			oss << (char) tolower(lyric[i]);
	return oss.str();
}