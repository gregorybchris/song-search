/*
 * ListTable.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: Chris Gregory
 */

#include "ListTable.h"

/*
 * Constructor
 */
ListTable::ListTable() {
	capacity = INIT_TABLE_SIZE;
	size = 0;
	table = new TopList*[capacity];
	for(int i = 0; i < capacity; i++)
		table[i] = NULL;
}

/*
 * Destructor
 */
ListTable::~ListTable() {
	for(int i = 0; i < capacity; i++)
		if(table[i] != NULL)
			delete table[i];
	delete[] table;
}

/*
 * Returns whether the hash table contains the given word
 */
bool ListTable::contains(string word) {
	uint32_t hash = hash_string(word);
	int location = hash % capacity;
	// Goes through hash table array until a good spot is found
	for(int i = location; i < location + capacity; i++) {
		// Empty spot found, not in array
		if(table[i % capacity] == NULL)
			return false;
		// Word found
		else if(table[i % capacity]->get_word() == word)
			return true;
	}
	return false;
}

/*
 * Gets the TopList of a given word (NULL if not found)
 */
TopList * ListTable::get(string word) {
	uint32_t hash = hash_string(word);
	int location = hash % capacity;
	// Goes through hash table array until a good spot is found
	for(int i = location; i < location + capacity; i++) {
		// Empty spot found, not in array
		if(table[i % capacity] == NULL)
			return NULL;
		// Word found
		else if(table[i % capacity]->get_word() == word)
			return table[i % capacity];
	}
	return NULL;
}

/*
 * Adds a word to the TopList table
 * 		A new TopList is created if the word did not already exist
 * 		If the word is found the song is added to that list
 */
void ListTable::add(string word, Song * song) {
	uint32_t hash = hash_string(word);
	int location = hash % capacity;
	// Goes through hash table array until a good spot is found
	for(int i = location; i < location + capacity; i++) {
		// Empty spot found, not in array
		if(table[i % capacity] == NULL) {
			TopList * new_top_list = new TopList(word);
			new_top_list->add_song(song);
			table[i % capacity] = new_top_list;
			size++;
			break;
		}
		// Word found
		else if(table[i % capacity]->get_word() == word) {
			table[i % capacity]->add_song(song);
			break;
		}
	}

	if(get_load_factor() > LOAD_FACTOR_LIMIT)
		expand();
}

/*
 * Private function used to populate an array with a TopList
 * 		This is only used when rehashing during expansion
 */
void ListTable::add(TopList * top_list) {
	uint32_t hash = hash_string(top_list->get_word());
	int location = hash % capacity;
	// Goes through hash table array until an empty spot is found
	for(int i = location; i < location + capacity; i++) {
		// Empty spot found, can be added here
		if(table[i % capacity] == NULL) {
			table[i % capacity] = top_list;
			size++;
			break;
		}
	}
}

/*
 * Doubles the size of the array in the hash table
 * 		Expansion should only happen with the LOAD_FACTOR_LIMIT is reached
 */
void ListTable::expand() {
	// Save off all old data
	int old_capacity = capacity;
	TopList ** old_table = table;
	// Change properties of hash table
	capacity *= 2;
	table = new TopList*[capacity];
	for(int i = 0; i < capacity; i++)
		table[i] = NULL;
	size = 0;
	// Add all elements to new, expanded array by rehashing
	for(int i = 0; i < old_capacity; i++)
		if(old_table[i] != NULL)
			add(old_table[i]);
	// Clean up old, smaller array
	delete[] old_table;
}

/*
 * Returns a ratio of number of elements in table to capacity of the table
 */
double ListTable::get_load_factor() {
	return (double)size / capacity;
}
