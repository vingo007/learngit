 ///
 /// @file    statistic.cc
 /// @author  stone(vingo007@126.com)
 /// @date    2018-02-18 20:05:34
 ///
 
#include "statistic.h"
#include <fstream>
#include <sstream>
#include <algorithm>
using std::cout;
using std::endl;
using std::fstream;
using std::stringstream;
//using namespace std;
//


void ws::Display()
{
	size_t i;
	for(i=0;i<100;i++)
	{
		cout << _vec[i].word << "\t" << _vec[i].num << endl;
	}
}


void ws::Statistic(string word)
{
	size_t i;
	for(i=0;i<_vec.size();++i)
	{
//		cout << "i=" << i << endl;
		if(word==_vec[i].word)
		{
			++_vec[i].num;
			break;
		}
	}
	if(i==_vec.size())
	{
		wfluent flu;
		flu.word=word;
		flu.num=1;
		_vec.push_back(flu);
	}
}


void ws::Readfile()
{
	fstream ifs;
	ifs.open("The_Holy_Bible.txt");
	string s;
	while(getline(ifs,s))
	{
		stringstream iss(s);
		string word;
		while(!iss.eof())
		{
			iss >> word;
			if(!(word[0]>='0'&& word[0]<='9'))
			{
				Statistic(word);			
			}
		}
	}
	ifs.close();
	sort(_vec.begin(),_vec.end());
}

void ws::Writefile()
{
	fstream ofs;
	ofs.open("count.dat",std::ios::out | std::ios::trunc);
	for(size_t i=0;i<100;++i)
	{
		ofs << _vec[i].word << "\t" << _vec[i].num << endl;
	}
	ofs.close();
}

