/*
 * FilesBase.h
 *
 *  Created on: 07-01-2012
 *      Author: Jacek
 */

#ifndef FILESBASE_H_
#define FILESBASE_H_
#include<string>
#include <sstream>
#include "Answers.h"
#include <map>

using namespace std;

class FilesBase {
public:
	FilesBase();
	bool generateFilesList(string str);
	bool generateFilesList(const istream &s);
	map<string, int> *getFilesList();
	string toString();
	virtual ~FilesBase();
protected:
	map<string, int> *filesMap;
};

#endif /* FILESBASE_H_ */
