 ///
 /// @file    wtest.cc
 /// @author  stone(vingo007@126.com)
 /// @date    2018-02-20 10:00:42
 ///
 
#include "TextQuery.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::string;


int main()
{
	TextQuery search;
	cout << "query file:" << endl;
	string filename;
	cin >> filename;
	
	string word;
	while(cout << "query word:",cin>> word )
	{
		search.readFile(filename,word);
		search.display();
	}
	return 0;
}
