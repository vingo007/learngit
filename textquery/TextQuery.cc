 ///
 /// @file    TextQuery.cc
 /// @author  stone(vingo007@126.com)
 /// @date    2018-02-19 21:21:51
 ///
 
#include "TextQuery.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::fstream;
using std::string;
using std::stringstream;


void TextQuery::readFile(const string filename,const string mword)
{
	_freq=0;
	fstream ifs(filename);
	if(!ifs.good())
	{
		cout << "error : bad filename" << endl;
		return;
	}
	string line;
	size_t line_num=1;
	int flag=0;
	while(getline(ifs,line))
	{
		flag=0;
		stringstream iss(line);
		string word;
		while(!iss.eof())
		{
			iss >> word;
			if(word==mword)
			{
				_freq++;
				if(flag==0)
				{
					wcount saveline;
					saveline.line=line;
					saveline.linenumber=line_num;
					_lines.push_back(saveline);
				}
				flag=1;
			}
		}
		++line_num;
	}
}

void TextQuery::display()
{
	size_t i;
	cout << "the word occur " << _freq << " times" << endl;
	if(_freq!=0)
	{
		for(i=0;i<_lines.size();++i)
		{
			cout << "( line "  << _lines[i].linenumber << " )" 
				 << _lines[i].line << endl;
		}	
		_lines.clear();
	}
}
