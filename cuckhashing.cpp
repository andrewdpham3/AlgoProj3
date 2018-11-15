#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std; 

const int tablesize=17;
bool ontable1=true;
string table1[tablesize],
	table2[tablesize];

void place(string word){
	cout<<"computing value for "<<word<<endl;
	unsigned long int val=0;
	
	//function 1
	if(ontable1)
		for(double i=0;i<word.length();i++){
			val+=word.at(i)*pow(31,i);
			cout<<val<<"="<<word.at(i)<<"*"<<pow(31,i)<<"+ val"<<endl;
		}
	//function 2
	else
		for(double i=0;i<word.length();i++)
			val+=word.at(word.size()-i-1)*pow(31,i);
	cout<<"big val="<<val<<endl;

	//bring val into range
	val%=tablesize;
	if(val<0)
		val+=tablesize;
	cout<<"val="<<val<<endl;

	//place in table
	if(ontable1){
		if(table1[val]!=""){
			ontable1=!ontable1;
			place(table1[val]);
		}
		cout<<word<<" placed on table 1 at "<<val<<endl;
		table1[val]=word;
	}
	else{
		if(table2[val]!=""){
			ontable1=!ontable1;
			place(table2[val]);
		}
		cout<<word<<" placed on table 2 at "<<val<<endl;
		table2[val]=word;
	}
	
	//reset for next word
	ontable1=true;
}

int main() {  
    string word, filename; 
	
	fstream file;
    filename = "in5.txt";
    file.open(filename.c_str()); 
  
	string input[100];
	int w=0;
    while (file >> word) { 
		input[w]=word;
		w++;
    } 

	for(int i=0;i<w;i++)
		cout<<input[i]<<endl;

	for(int i=0;i<w;i++)
		place(input[i]);
	
	for(int i=0;i<tablesize;i++)
		cout<<table1[i]<<endl;
	for(int i=0;i<tablesize;i++)
		cout<<table2[i]<<endl;

    return 0; 
} 