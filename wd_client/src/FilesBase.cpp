/*
 * FilesBase.cpp
 *
 *  Created on: 07-01-2012
 *      Author: Jacek
 */

#include "FilesBase.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

FilesBase::FilesBase() {
	this->filesMap = new map<string, int>();
}

bool FilesBase::generateFilesList(string str) {
	istringstream iss(str);
	const istream & iss2 = (istream &) iss;
	return generateFilesList(iss2);
}

bool FilesBase::generateFilesList(const istream &s) {
	istringstream & iss = (istringstream &) s;
	while (iss) {
		//int version;
		//iss >> version;
		//if (!iss)
		//	return false;
		string path;
		iss >> path;
		this->filesMap->insert(pair<string, int>(path, 0));
	}
	return true;
}

map<string, int> * FilesBase::getFilesList() {
	return this->filesMap;
}

string FilesBase::toString() {
	stringbuf *buffer = new stringbuf();
	map<string, int>::iterator it = this->filesMap->begin();
	for (; it != this->filesMap->end(); ++it) {
		buffer->sputn(it->first.c_str(), sizeof(it->first.c_str()) - 1);
		//buffer->sputn(" ", 1);
		//char str[10];
		//itoa(it->second, str, 10);
		//buffer->sputn(str, sizeof(str));
		buffer->sputn("\n", 1);
	}
	string result = buffer->str();
	delete buffer;
	return result;
}

FilesBase::~FilesBase() {
	delete this->filesMap;
}

