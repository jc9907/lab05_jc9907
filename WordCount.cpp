// WordCount.cpp

#include "WordCount.h"
#include <ostream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <ctype.h>
#include <bits/stdc++.h>
using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int count = 0;
	for(size_t k = 0; k<CAPACITY; k++){
		for(auto i = table[k].begin(); i != table[k].end(); i++){
		count+=i->second;
		}
	}
	return count;
}

int WordCount::getNumUniqueWords() const {
	int count = 0;
	for(size_t k = 0; k<CAPACITY; k++){
		for(auto i = table[k].begin(); i != table[k].end(); i++){
			if(i->second!=0)
				count++;
		}
	}
	return count;
}

int WordCount::getWordCount(std::string word) const {
	int count = 0;
	string w = stripWord(word);
	for(size_t i = 0; i<w.length();i++) w[i] = toupper(w[i]);
	for(size_t k = 0; k<CAPACITY; k++){
		for(auto i = table[k].begin(); i != table[k].end();i++){
			if(i->first == w)
				count=i->second;
		}
	}
	return count;
}

int WordCount::incrWordCount(std::string word) {
	string w = stripWord(word);
	if (w == "")
		return 0;
	
	for (size_t i = 0; i < w.size(); i++)
       w[i] = toupper(w[i]);
	
	int loc = hash(w);
	for (size_t i = 0 ; i <table[loc].size();i++){
		if(table[loc][i].first == w){
			table[loc][i].second ++;
			return table[loc][i].second;
		}
	}
	table[loc].push_back(pair<string, size_t> (w,1));
	return 1;
}


bool WordCount::isWordChar(char c) {
	return (isalpha(c));
}


std::string WordCount::stripWord(std::string word) {
	size_t count = 0;
	if (word == "") return "";
	for (size_t i = 0; i < word.length();i++){
		if(!isWordChar(word[i])) count ++;
	}
	if(count == word.length()) return "";
	else{
		while(!isWordChar(word.front())) word.erase(0,1);
		while(!isWordChar(word.back())) word.pop_back();
		for (size_t i =0; i < word.length(); i++){
			if(!isWordChar(word[i]) && word[i] != '\'' && word[i] != '-'){
				word.erase(i,1);
			}
		}
	}
	return word;
}
bool wayToSort1(pair<string, size_t> p1, pair<string, size_t> p2) { return p1.first < p2.first; }
void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	vector<pair<string, size_t>> v;
	for(size_t i = 0; i < CAPACITY; i++){
		if (!table[i].empty()){
			for (size_t k = 0; k<table[i].size();k++)
				v.push_back(table[i].at(k));
		}
	}

	sort(v.begin(), v.end(),wayToSort1);

	for(size_t i = 0; i<v.size(); i++){
		out<<v[i].first<<","<<v[i].second<<endl;}
}

bool wayToSort2(pair<string, size_t> p1, pair<string, size_t> p2) { 
	if (p1.second == p2.second){
		return wayToSort1(p1,p2);
	}
	return p1.second > p2.second; }

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	vector<pair<string, size_t>> v;
	for(size_t i = 0; i < CAPACITY; i++){
		if (!table[i].empty()){
			for (size_t k = 0; k<table[i].size();k++)
				v.push_back(table[i].at(k));
		}
	}

	sort(v.begin(), v.end(), wayToSort2);

	for(size_t i = 0; i<v.size(); i++){
		out<<v[i].first<<","<<v[i].second<<endl;}
}

void WordCount::addAllWords(std::string text) {
	string s = text.c_str();

	size_t index = 0;

	for(size_t i = 0; i < s.size(); i++){
		if(s[i] == ' '||s[i] == '\n'){
			this->incrWordCount(s.substr(index,  i-index));
			index = i;
		}
		}
	for(size_t i = 0; i < s.size(); i++){
		if (i == s.size()-1){
			this->incrWordCount(s.substr(index, s.size()-index));
		}
	}
	
}
