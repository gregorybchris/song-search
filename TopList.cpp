/*
 * TopList.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: Chris Gregory
 */

#include "TopList.h"

/*
 * Constructor
 */
TopList::TopList(string word) {
	this->word = word;
	capacity = MAX_LIST_SIZE;
	size = 0;
	songs = new Song*[capacity];
	for(int i = 0; i < capacity; i++)
		songs[i] = NULL;
}

/*
 * Destructor
 */
TopList::~TopList() {
	delete[] songs;
}

/*
 * Gets the number of songs currently in the list
 */
int TopList::get_size() {
	return size;
}

/*
 * Gets corresponding word of the list
 */
string TopList::get_word() {
	return word;
}

/*
 * Gets a song from the list array at a given index
 */
Song * TopList::get_song(int index) {
	return songs[index];
}

/*
 * Does a linear search of the array to see if it contains a given song
 */
bool TopList::contains(Song * song) {
	for(int i = 0; i < size; i++)
		if(song->equals(songs[i]))
			return true;
	return false;
}

/*
 * Adds a song to the list
 * 		If the song is already in the list the position of the song
 * 		is checked and then updated.
 * 		If the song is not already in the list it has the potential 
 * 		to bump another song off the list, be inserted, or appended
 */
void TopList::add_song(Song * song) {
	int frequency = song->get_frequency(word);
	// No songs, just added to the beginning
	if(size == 0) {
		songs[0] = song;
		size++;
	}
	// Song is in the list, check to see if it is in the right place
	else if(contains(song)) {
		// Find location of song
		int index = -1;
		for(int i = size - 1; i >= 0; i--) {
			if(songs[i]->equals(song)) {
				index = i;
				break;
			}
		}
		// Move song into correct position based on word frequency
		for(int i = index; i >= 1; i--) {
			if(frequency > songs[i - 1]->get_frequency(word)) {
				songs[i] = songs[i - 1];
				songs[i - 1] = song;
			}
			else
				break;
		}
	}
	// Song is not in the list
	else {
		// Not full array, need to add element at end
		if(size < capacity) {
			songs[size] = song;
			size++;
			// Bubble element into correct position
			for(int i = size - 2; i >= 0; i--) {
				if(frequency > songs[i]->get_frequency(word)) {
					songs[i + 1] = songs[i];
					songs[i] = song;
				}
				else
					break;
			}
		}
		// Full array, element must be inserted after shifting
		else {
			// Shift elements over and place song in correct position
			for(int i = size - 1; i >= 0; i--) {
				if(frequency > songs[i]->get_frequency(word)) {
					// Shift needed, in bounds
					if(i + 1 < capacity)
						songs[i + 1] = songs[i];
					songs[i] = song;
				}
				else
					break;
			}
		}
	}
}