#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "autocomplete.h"

bool cmp(pair<string, int>a, pair<string, int>& b){
	return a.second > b.second;
}
void sortDictionary(vector<pair<string, int>>&dict){
	sort(dict.begin(), dict.end(), cmp);
}

AutoComplete::AutoComplete(config_t config){
    displayLimit = config.limit;
    io = createIoHandler(config.type, config.filename);
    if(!io){
        cout << "Failed creating file " << config.filename << endl;
        exit(1);
    }
}

vector<string> AutoComplete::findAll(string key){
    int i=0;
	vector<string> result;
	for(auto&  it : dictionary){
		if(it.first.substr(0, key.size()) == key){
		    if(displayLimit > 0 && (i++ >= displayLimit)){
		        break;
		    }
			result.push_back(it.first);
		}
	}
	return result;
}

void AutoComplete::addEntry(string key){
    if(key.empty()) return; // don't waste time on empty strings

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

int AutoComplete::writeDictionary(){
    if(io){
        io->write(dictionary);
    }
    return 0;
}

int AutoComplete::loadDictionary(){
    if(io){
        io->read(dictionary);
    }
    return 0;
}

void AutoComplete::dumpDictionary(){
    IoStd::dumpDictionary(dictionary);
}