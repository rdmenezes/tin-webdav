/*
 * Logic.h
 *
 *  Created on: 06-01-2012
 *      Author: Jacek
 */

#ifndef LOGIC_H_
#define LOGIC_H_
#include "Communication.h"
#include "FilesBase.h"
#include "LocalBase.h"
#include "MasterServerCommunication.h"
#include <vector>

class Logic {
public:
	Logic();
	void onStart();
	void getFile(string remoteFileName);
	void putFile(string localFileName);
	void deleteFile(string remoteFileName);
	void showMyFiles();
	void showServerFiles();
	void syncFiles();
	void onEnd();

	virtual ~Logic();

private:
	void generateDiffs();
	void showDiffs();
	MasterServerCommunication *mainServer;
	LocalBase *localFiles;
	FilesBase *remoteFiles;
	vector<string> *diffs;

};


#endif /* LOGIC_H_ */
