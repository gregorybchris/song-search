/*
 * FrequencyTable.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: Chris Gregory
 */

#include "FrequencyTable.h"

/*
 * Constructor
 */
FrequencyTable::FrequencyTable() {
	capacity = INIT_TABLE_SIZE;
	size = 0;
	table = new WordFreqPair*[capacity];
	for(int i = 0; i < capacity; i++)
		table[i] = NULL;
}

/*
 * Destructor
 */
FrequencyTable::~FrequencyTable() {
	for(int i = 0; i < capacity; i++)
		if(table[i] != NULL)
			delete table[i];
	delete[] table;
}

/*
 * Returns whether the hash table contains the given word
 */
bool FrequencyTable::contains(string word) {
	uint32_t hash = hash_string(word);
	int location = hash % capacity;
	// Goes through hash table array until an empty spot is found
	for(int i = location; i < location + capacity; i++) {
		// Empty spot found, not in array
		if(table[i % capacity] == NULL)
			return false;
		// Word found
		else if(table[i % capacity]->word == word)
			return true;
	}
	return false;
}

/*
 * Gets the frequency of a given word (zero if not found)
 */
int FrequencyTable::get(string word) {
	uint32_t hash = hash_string(word);
	int location = hash % capacity;
	// Goes through hash table array until an empty spot is found
	for(int i = location; i < location + capacity; i++) {
		// Empty spot found, not in array
		if(table[i % capacity] == NULL)
			return 0;
		// Word found
		else if(table[i % capacity]->word == word)
			return table[i % capacity]->frequency;
	}
	return 0;
}

/*
 * Adds a word to the frequency table
 * 		The frequency is set to one if the word did not already exist
 * 		If the word is found the frequency is incremented
 */
void FrequencyTable::add(string word) {
	uint32_t hash = hash_string(word);
	int location = hash % capacity;
	// Goes through hash table array until an empty spot is found
	for(int i = location; i < location + capacity; i++) {
		// Empty spot found, not in array
		if(table[i % capacity] == NULL) {
			WordFreqPair * new_pair = new WordFreqPair;
			new_pair->word = word;
			new_pair->frequency = 1;
			table[i % capacity] = new_pair;
			size++;
			break;
		}
		// Word found
		else if(table[i % capacity]->word == word) {
			table[i % capacity]->frequency++;
			break;
		}
	}

	if(get_load_factor() > LOAD_FACTOR_LIMIT)
		expand();
}

/*
 * Private function used to populate an array with a WordFreqPair
 * 		This is only used when rehashing during expansion
 */
void FrequencyTable::add(WordFreqPair * pair) {
	uint32_t hash = hash_string(pair->word);
	int location = hash % capacity;
	// Goes through hash table array until an empty spot is found
	for(int i = location; i < location + capacity; i++) {
		// Empty spot found, can be added here
		if(table[i % capacity] == NULL) {
			table[i % capacity] = pair;
			size++;
			break;
		}
	}
}

/*
 * Doubles the size of the array in the hash table
 * 		Expansion should only happen with the LOAD_FACTOR_LIMIT is reached
 */
void FrequencyTable::expand() {
	// Save off all old data
	int old_capacity = capacity;
	WordFreqPair ** old_table = table;
	// Change properties of hash table
	capacity *= 2;
	table = new WordFreqPair*[capacity];
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
double FrequencyTable::get_load_factor() {
	return (double)size / capacity;
}
