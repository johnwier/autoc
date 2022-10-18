#include <iostream>
#include <vector>
#include <algorithm>
#include "autocomplete.h"

bool cmp(pair<string, int>a, pair<string, int>& b){
	return a.second > b.second;
}
void sortDictionary(vector<pair<string, int>>&dict){
	sort(dict.begin(), dict.end(), cmp);
}

vector<string> AutoComplete::findAll(string key){
	vector<string> result;
	for(auto&  it : dictionary){
		if(it.first.substr(0, key.size()) == key){
			result.push_back(it.first);
		}
	}
	return result;
}


void AutoComplete::addEntry(string key){
	vector<pair<string, int>>::iterator it;
	it = find_if(dictionary.begin(), dictionary.end(), [&key](const pair<string,int>&element){ return element.first == key;});
	if(it != dictionary.end()){
		it->second++;
	}
	else{
		dictionary.emplace_back(key, 1);
	}
	sortDictionary(dictionary);
}

void AutoComplete::dumpDictionary(){
	cout << "\tKEY\tWEIGHT\n";
	for(auto& it: dictionary){
		cout << '\t' << it.first << '\t' << it.second << '\n';
	}
}
