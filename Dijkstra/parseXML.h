#ifndef PARSEXML_H
#define PARSEXML_H

#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
using namespace std;

#include"rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include"rapidxml_utils.hpp"
using namespace rapidxml;

class parseXML{
	public:
		int parse();			//parse downloaded XML (from xml to txt)
	private:
		void download();		//download real time xml
		int shift(string);
};
#endif