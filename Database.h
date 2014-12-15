/*
 * Database.h
 *
 *  Created on: Nov 24, 2014
 *      Author: Chris Gregory
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <vector>
#include "Song.h"
#include "TopList.h"
#include "ListTable.h"
using namespace std;

class Database {
public:
	Database();
	~Database();
	
	void add_song(Song * song);
	void add_word(string word, Song * song);
	void print_results(string word);

private:
	vector<Song *> songs;
	ListTable top_lists;
};

#endif /* DATABASE_H_ */
