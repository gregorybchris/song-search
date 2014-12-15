/*
 * ListTable.h
 *
 *  Created on: Nov 25, 2014
 *      Author: Chris Gregory
 */

#ifndef LISTTABLE_H_
#define LISTTABLE_H_

#define LOAD_FACTOR_LIMIT 0.5
#define INIT_TABLE_SIZE 10

#include "HashFunctions.h"
#include "TopList.h"
#include <iostream>
using namespace std;

class ListTable {
public:
	ListTable();
	~ListTable();
	
	bool contains(string word);
	TopList * get(string word);
	void add(string word, Song * song);

private:
	int capacity;
	int size;
	TopList ** table;
	
	void add(TopList * top_list);
	void expand();
	double get_load_factor();
};


#endif /* LISTTABLE_H_ */
