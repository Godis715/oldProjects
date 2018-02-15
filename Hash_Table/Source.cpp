#include <iostream>
#include "hashtable.h"

using namespace std;

int main() {
	int size = 3870;
	Hashtable *hashtable = ht::create(size);
	fillHashtable(hashtable);

	int j = 0;
	for (int i = 0; i < size; ++i) {
		if (hashtable->table[i].size() > 1) {
			j += hashtable->table[i].size();
		}
		
	}

	cout << j;


	while (true) {
		string str;
		cin >> str;
		if (findStr(hashtable, str)) {
			cout << "Yes";
		}
		else {
			cout << "No";
		}
		cout << endl;
	}



	return 0;
}