#pragma once
#include <list>
#include <string>
#include <fstream>
#include <iostream>

typedef std::list<std::string> Table;

struct Hashtable {
	Table *table = nullptr;
	int absSize = 0;
	int size = 0;
};

namespace ht {
	Hashtable *create(int size) {

		Hashtable *hashtable = new Hashtable;
		hashtable->table = new Table[size];
		hashtable->absSize = size;
		hashtable->size = 0;

		return hashtable;
	}

	long long hashCalc(std::string str) {
		long long p = 11;
		long long hash = 0;
		for (int i = 0; str[i] != '\0'; ++i) {
			hash += (str[i] * p);
			p *= 11;
		}
		return abs(hash);
	}

	void push(Hashtable *hashtable, std::string str) {
		long long hash = hashCalc(str) % hashtable->absSize;
		if (hashtable->table[hash].size() != 0) {
			for (auto i = hashtable->table[hash].begin(); i != hashtable->table[hash].end(); i = next(i)) {
				if (*i == str) {
					return;
				}
			}
		}
		hashtable->table[hash].push_back(str);
		hashtable->size++;
	}
}

void fillHashtable(Hashtable *hashtable) {
	std::ifstream inp;
	inp.open("files.txt");

	std::string str;
	while (inp >> str) {
		ht::push(hashtable, str);
	}

	inp.close();
}
bool findStr(Hashtable *hashtable, std::string str) {
	long long hash = ht::hashCalc(str) % hashtable->absSize;
	if (hashtable->table[hash].size() != 0) {
		for (auto i = hashtable->table[hash].begin(); i != hashtable->table[hash].end(); i = next(i)) {
			if (*i == str) {
				return true;
			}
		}
	}
	return false;
}