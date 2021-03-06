//cuckoo hashing by andrew pham
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

const int tablesize = 17;
bool ontable1 = true;//keeps track of what table we're on
string table1[tablesize], table2[tablesize];

void place(string word) {
	size_t po=1, i=0;
	int val = 0, temp;
	if (ontable1)
		val = word.at(i);
	else
		val = word.at(word.length() - i - 1);
	val %= tablesize;
	if (val < 0) 
		val += tablesize;
	for (i = 1; i < word.length(); i++){
		if (ontable1)
			temp = word.at(i);//function 1
		else
			temp = word.at(word.length()-i-1);//function 2
		po *= 31;
		po %= tablesize;
		if (po < 0) 
			po += tablesize;
		val += temp * po;
		val %= tablesize;
		if (val < 0) 
			val += tablesize;
	}
	//place in table
	string* currenttable; 
	if (ontable1) {
		currenttable = table1;
		cout << word << " placed on table 1 at spot " << val << endl;
	}
	else {
		currenttable = table2;
		cout << word << " placed on table 2 at spot " << val << endl;
	}
	if (currenttable[val] != "") {//colission handler
		ontable1 = !ontable1;//switching tables
		place(currenttable[val]);//push to other table
	}
	currenttable[val] = word;//placement
	ontable1 = true;//reset for next word
}

void main() {
	//open read and store file
	fstream file;
	string input[100];
	file.open("in6.txt");
	int w = 0;
	while (!file.eof()) {
		getline(file,input[w]);
		w++;
	}
	//hash and place into tables
	for (int i = 0; i<w; i++)
		place(input[i]);
	//print tables
	cout << "table 1:" << endl;
	for (int i = 0; i<tablesize; i++)
		cout << i <<" " <<table1[i] << endl;
	cout << "table 2:" << endl;
	for (int i = 0; i<tablesize; i++)
		cout << i << " " << table2[i] << endl;
	system("pause");
}