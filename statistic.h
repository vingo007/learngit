 ///
 /// @file    statistic.h
 /// @author  stone(vingo007@126.com)
 /// @date    2018-02-18 20:06:11
 ///
 
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;
//using namespace std;


typedef struct wfluent{
	string word;
	int num;
}wfluent;

inline bool operator<(const wfluent & lhs , const wfluent & rhs)
{
	return lhs.num > rhs.num;
}

class ws
{
public:

	void Readfile();
	void Writefile();
	void Statistic(string);
	void Display();
private:
	vector <wfluent> _vec;
};





