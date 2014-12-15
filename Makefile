#
# Makefile for SongSearch, Assignment 6
#
CXX = clang++
FLAGS = -g -Wall

songsearch: Database.cpp Database.h FrequencyTable.cpp FrequencyTable.h \
		HashFunctions.cpp HashFunctions.h ListTable.cpp ListTable.h \
		Song.cpp Song.h TopList.cpp TopList.h main.cpp
	${CXX} ${FLAGS} -o songsearch Database.cpp FrequencyTable.cpp \
		HashFunctions.cpp ListTable.cpp Song.cpp TopList.cpp main.cpp
	
clean:
	rm -f songsearch

provide_design:
	provide comp15 hw6_design songsearch_design.txt

provide:
	provide comp15 hw6 main.cpp Database.cpp Database.h \
		FrequencyTable.cpp FrequencyTable.h HashFunctions.cpp HashFunctions.h \
		ListTable.cpp ListTable.h Song.cpp Song.h TopList.cpp TopList.h \
		Makefile ReadMe.md

