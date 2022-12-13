#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include "autocomplete.h"

AutoComplete* list;

string read_input(config_t* config){
	string input;
	char c;
	vector<string> choices;
	int done = false;
	system("stty raw");
	while(!done){
		if(input.size() > 0){
			system("clear");
			choices = list->findAll(input);
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
				list->writeDictionary();
				exit(1);
			case 27:
				system("stty cooked");
			    list->dumpDictionary();
			    break;
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

int parse_cli(int argc, char** argv, config_t* config){
    int opt;
    while((opt = getopt(argc, argv, "n:f:t:")) > 0){
        switch(opt){
            case 'n': config->limit = atoi(optarg); break;
            case 'f': config->filename = optarg; break;
            case 't': config->type = (handlerType_e)atoi(optarg); break;
            default: break;
        };
    }
    return 0;
}

int main(int argc ,char** argv){
    config_t config = {0};
	string input;
	parse_cli(argc, argv, &config);
	list = new AutoComplete(config);
	list->loadDictionary();
	for(;;){
		input = "";
		cout << "Enter word: ";
		input = read_input(&config);
		system("clear");
		list->addEntry(input);
	}
	return 0;
}
