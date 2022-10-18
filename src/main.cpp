#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include "autocomplete.h"

AutoComplete list;

string read_input(){
	string input;
	char c;
	vector<string> choices;
	int done = false;
	system("stty raw");
	while(!done){
		if(input.size() > 0){
			system("clear");
			choices = list.findAll(input);
			for(const auto& entry : choices){
				cout << entry << ' ';
			}
			cout << "\r\nEnter word: " << input;
		}
		c=getchar();
		switch(c){
			case '\r':
			case '\n':
				done = true;
				break;
			case '\t':	// TAB complete the word w the top choice
				input = choices.front();
				break;
			case 3: 	// ^C quit
				system("stty cooked");
				exit(1);
			case 127: 	// BACKSPACE
				input.pop_back();
				break;
			default:
				input += c;
		};
	}
	system("stty cooked");
	return input;
}

int main(int argc ,char** argv){
	string input;
	for(;;){
		input = "";
		cout << "Enter word: ";
		input = read_input();
		system("clear");
		list.addEntry(input);
	}
	return 0;
}
