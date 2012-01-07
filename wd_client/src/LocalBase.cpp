/*
 * LocalBase.cpp
 *
 *  Created on: 06-01-2012
 *      Author: Jacek
 */

#include "LocalBase.h"
#include <fstream>
#include <iostream>

LocalBase::LocalBase(string filesListFile, string basePath) {
	this->filesListFilePath = filesListFile;
	this->basePath = basePath;
	this->generateFilesList();
}

//deprecated
/*int LocalBase::getFileVersion(string localFile)
 {
 map<string, int>::iterator it = this->filesMap->find(localFile);
 if( it != this->filesMap->end())
 return it->second;
 else
 return -1;
 }*/

bool LocalBase::generateFilesList() {
	ifstream filesListStream;
	filesListStream.open(this->filesListFilePath.c_str());
	istream & iss = (istream &) filesListStream;
	if (filesListStream.is_open()) {
		bool result = ((FilesBase *) this)->generateFilesList(iss);
		filesListStream.close();
		return result;
	}
	return false;
}

void LocalBase::addFile(string file) {
	if (this->filesMap->find(file) != this->filesMap->end()) {
		this->filesMap->insert(pair<string, int>(file, 0));
	}
}

bool LocalBase::deleteFile(string file) {
	if (this->filesMap->find(file) != this->filesMap->end()) {
		this->filesMap->insert(pair<string, int>(file, 0));
		return true;
	}
	return false;
}

bool LocalBase::saveFilesList() {
	//TODO
	//saves current map to file
	//false if we cannot write to the file
}

bool LocalBase::saveFileToHDD(string fileName, string fileContent) {
	//TODO
	//save file to HDD
	//false if we cannot write to the file
}

string LocalBase::getFileContent(string fileName) {
	//TODO
	//get file content and put it back as string
}

LocalBase::~LocalBase() {
}

