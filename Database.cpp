/*
 * Database.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: Chris Gregory
 */

#include "Database.h"

/*
 * Constructor
 */
Database::Database() {}

void deleteAll(Song * song) {
	delete song;
}

/*
 * Destructor
 */
Database::~Database() {
	for(std::vector<Song *>::iterator it = songs.begin(); 
			it != songs.end(); ++it)
		delete *it;
}

/*
 * Adds a song to the full list of songs that are kept in a vector
 */
void Database::add_song(Song * song) {
	songs.push_back(song);
}

/*
 * Adds the word with the song it is in to the hash table of song lists
 */
void Database::add_word(string word, Song * song) {
	top_lists.add(word, song);
}

/*
 * Prints out all songs with contexts given a search query
 */
void Database::print_results(string word) {
	TopList * list = top_lists.get(word);
	if(list == NULL)
		return;
	else {
		for(int i = 0; i < list->get_size(); i++) {
			Song * song = list->get_song(i);
			song->print_contexts(word, song->get_frequency(word));
		}
		cout << "<END OF REPORT>" << endl;
	}
}