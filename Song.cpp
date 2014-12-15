/*
 * Song.cpp
 *
 *  Created on: Nov 24, 2014
 *      Author: Chris Gregory
 */

#include "Song.h"

/*
 * Constructor
 */
Song::Song() {}

/*
 * Constructor when artist and title are known in advance
 */
Song::Song(string artist, string title) {
	this->artist = artist;
	this->title = title;
}

/*
 * Destructor
 */
Song::~Song() {}

/*
 * Gets the song artist
 */
string Song::get_artist() {
	return artist;
}

/*
 * Sets the song artist
 */
void Song::set_artist(string artist) {
	this->artist = artist;
}

/*
 * Gets the song title
 */
string Song::get_title() {
	return title;
}

/*
 * Sets the song title
 */
void Song::set_title(string title) {
	this->title = title;
}

/*
 * Adds a lyric (with symbols) to the vector of all original song lyrics
 */
void Song::add_lyric(string lyric) {
	lyrics.push_back(lyric);
}

/*
 * Adds a word to the hash table of words and frequencies
 */
void Song::add_word(string word) {
	frequency_table.add(word);
}

/*
 * Gets the frequency of a word in the song using the hash table
 */
int Song::get_frequency(string word) {
	return frequency_table.get(word);
}

/*
 * Goes through all lyrics in the vector and prints out the words 
 * 		surrounding a given word until the number occurrences matches
 * 		the frequency given
 */
void Song::print_contexts(string word, int frequency) {
	// Number of words to left and right of word to print
	int radius = 5;
	// Counts the number of words traversed by the vector iterator
	int words = 0;
	// Counts the number of times the word has been printed
	int appearances = 0;
	int vector_size = lyrics.size();
	for(std::vector<string>::iterator it = lyrics.begin(); 
			it != lyrics.end(); ++it) {
		string s = *it;
		s = make_alpha(s);
		// Word found, print context
		if(s == word) {
			cout << "Title: " << title << endl;
			cout << "Artist: " << artist << endl;
			cout << "Context: ";
			for(int i = -radius; i <= radius; i++) {
				int array_index = words + i;
				// Only print if the context word index is found in the vector
				if(array_index >= 0 && array_index < vector_size) {
					string line = *(it + i);
					cout << line << " ";
				}
			}
			cout << endl << endl;
			appearances++;
		}
		words++;
		if(appearances == frequency)
			return;
	}
}

/*
 * Takes a string, converts it to lowercase, and removes all symbols
 */
string Song::make_alpha(string lyric) {
	ostringstream oss;
	for(size_t i = 0; i < lyric.length(); i++)
		if(isalnum(lyric[i]))
			oss << (char) tolower(lyric[i]);
	return oss.str();
}

/*
 * Checks the artist and title to see whether the song matches another
 */
bool Song::equals(Song * other) {
	return other->artist == this->artist && other->title == this->title;
}

/*
 * Returns a formatted string using the artist and the song
 */
string Song::to_string() {
	ostringstream oss;
	oss << artist << " - " << title;
	return oss.str();
}