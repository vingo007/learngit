 ///
 /// @file    TextQuery.h
 /// @author  stone(vingo007@126.com)
 /// @date    2018-02-19 21:10:16
 ///
 
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::set;

typedef struct wcount{
	string line;
	int linenumber;
}wcount;

class TextQuery
{
public:
	void readFile(const string filename,const string mword);
	void query(const string & word);
	void display();
private:

	vector<wcount> _lines;
	int _freq;
	map<string, set<int> > _word2Line;
	map<string, int> _wordFreq;


};
