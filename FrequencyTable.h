/*
 * FrequencyTable.h
 *
 *  Created on: Nov 25, 2014
 *      Author: Chris Gregory
 */

#ifndef FREQUENCYTABLE_H_
#define FREQUENCYTABLE_H_

#define LOAD_FACTOR_LIMIT 0.5
#define INIT_TABLE_SIZE 10

#include "HashFunctions.h"
#include <iostream>
using namespace std;

struct WordFreqPair {
	string word;
	int frequency;
};

class FrequencyTable {
public:
	FrequencyTable();
	~FrequencyTable();

	bool contains(string word);
	int get(string word);
	void add(string word);
	
private:
	int capacity;
	int size;
	WordFreqPair ** table;

	void add(WordFreqPair * pair);
	void expand();
	double get_load_factor();
};

#endif /* FREQUENCYTABLE_H_ */
