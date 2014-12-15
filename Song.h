/*
 * Song.h
 *
 *  Created on: Nov 24, 2014
 *      Author: Chris Gregory
 */

#ifndef SONG_H_
#define SONG_H_

#include <vector>
#include <iostream>
#include <sstream>
#include "FrequencyTable.h"
using namespace std;

class Song {
public:
	Song();
	Song(string artist, string title);
	~Song();

	string get_artist();
	void set_artist(string artist);
	string get_title();
	void set_title(string title);
	void add_lyric(string lyric);
	void add_word(string word);
	int get_frequency(string word);
	void print_contexts(string word, int frequency);
	bool equals(Song * other);
	string to_string();

private:
	string artist;
	string title;
	vector<string> lyrics;
	FrequencyTable frequency_table;
	
	string make_alpha(string lyric);
};

#endif /* SONG_H_ */
