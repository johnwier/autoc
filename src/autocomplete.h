#include <string>
#include <vector>
#include <iterator>
using namespace std;

class AutoComplete{
	vector<pair<string,int>> dictionary;

	public:
		void addEntry(string key);
		vector<string> findAll(string key);
		void dumpDictionary();
};
