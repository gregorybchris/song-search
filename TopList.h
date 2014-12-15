/*
 * TopList.h
 *
 *  Created on: Nov 25, 2014
 *      Author: Chris Gregory
 */

#ifndef TOPLIST_H_
#define TOPLIST_H_

#define MAX_LIST_SIZE 10

#include <iostream>
#include "Song.h"
using namespace std;

class TopList {
public:
	TopList(string words);
	~TopList();
	
	int get_size();
	string get_word();
	void add_song(Song * song);
	Song * get_song(int index);
	
private:
	string word;
	int size;
	int capacity;
	Song ** songs;
	
	bool contains(Song * song);
};

#endif /* TOPLIST_H_ */
