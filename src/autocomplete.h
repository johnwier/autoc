#include <string>
#include <vector>
#include <map>
#include <iterator>
#include "IoHandler.h"
using namespace std;


typedef struct _config {
    int limit;
    string filename;
    handlerType_e type;
}config_t;

class AutoComplete{
	vector<pair<string,int>> dictionary;
	int displayLimit; // max choices to display
	IoHandler* io;

	public:
	    AutoComplete(config_t);
		void addEntry(string key);
		vector<string> findAll(string key);
		void dumpDictionary();
		int writeDictionary();
		int loadDictionary();
};
