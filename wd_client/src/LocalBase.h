/*
 * LocalBase.h
 *
 *  Created on: 06-01-2012
 *      Author: Jacek
 */

#ifndef LOCALBASE_H_
#define LOCALBASE_H_
#include<string>
#include "Answers.h"
#include "FilesBase.h"
#include <map>

using namespace std;

class LocalBase : public FilesBase{
public:
	LocalBase(string filesListFile, string basePath);
	int getFileVersion(string localFile);
	bool generateFilesList();
	void addFile(string file);
	bool saveFilesList();
	bool deleteFile(string file);
	bool saveFileToHDD(string fileName, string fileContent);
	string getFileContent(string fileName);
	virtual ~LocalBase();

private:
	string basePath;
	string filesListFilePath;

};

#endif /* LOCALBASE_H_ */
