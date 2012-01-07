/*
 * Logic.cpp
 *
 *  Created on: 06-01-2012
 *      Author: Jacek
 */

#include "Logic.h"
#include "Settings.h"
#include <iostream>
#include "SlaveServerCommunication.h"
#include "MasterServerCommunication.h"

using namespace std;

Logic::Logic() {
	this->mainServer = new MasterServerCommunication(Settings::SERVER_ADDR,
			Settings::SERVER_PORT);
	this->localFiles = new LocalBase(Settings::FILELISTFILE_PATH,
			Settings::BASE_PATH);
	this->remoteFiles = new FilesBase();
	this->diffs = new vector<string>();
}

void Logic::onStart() {
	this->localFiles->generateFilesList();
	string remoteFilesStr = this->mainServer->getFilesList();
	this->remoteFiles->generateFilesList(remoteFilesStr);
	generateDiffs();
	showDiffs();
}

void Logic::onEnd() {
	this->localFiles->saveFilesList();
}

void Logic::getFile(string remoteFileName) {

	string result = this->mainServer->getFile(remoteFileName);
	if (result == Answers::CONNECTION_ERROR) {
		cout << "Connection error" << endl;
		return;
	} else if (result == Answers::FILE_NOT_FOUND) {
		cout << "File not found" << endl;
		return;
	}

	int position = result.find_last_of(':', 0);
	string link = link.assign(result, 0, position);
	string port = link.assign(result, position + 1, result.length() - position);

	SlaveServerCommunication *ssc = new SlaveServerCommunication(link, port);
	result = ssc->lockFile(remoteFileName);
	//TODO check result
	//if( )

	result = ssc->getFile(remoteFileName);
	//TODO check result ( result code )

	result = ssc->unlockFile(remoteFileName);
	//TODO check result
	//if( )

	//TODO parse file content from result
	//string file =

	//if( this->localFiles->saveFileToHDD(remoteFileName, file))

}

void Logic::putFile(string localFileName) {
	try {
		string content = this->localFiles->getFileContent(localFileName);
	} catch (string &exc) {
		if (exc.compare(Answers::FILE_NOT_FOUND)) {
			cout << "file open error";
		} else {
			cout << "unsupported exception";
		}
		return;
	}
	string result = this->mainServer->sendFile(localFileName);
	if (result == Answers::CONNECTION_ERROR) {
		cout << "Connection error" << endl;
		return;
	}

	int position = result.find_last_of(':', 0);
	string link = link.assign(result, 0, position);
	string port = link.assign(result, position + 1, result.length() - position);

	SlaveServerCommunication *ssc = new SlaveServerCommunication(link, port);
	const char *fileContent =
			this->localFiles->getFileContent(localFileName).c_str();

	ssc->sendFile(localFileName, (char *) fileContent);
	//TODO check result
	//if( )
	//if OK
	mainServer->sendFileACK(localFileName);

}

void Logic::deleteFile(string remoteFileName) {

	string result = this->mainServer->deleteFile(remoteFileName);
	if (result == Answers::CONNECTION_ERROR) {
		cout << "Connection error" << endl;
		return;
	} else if (result == Answers::FILE_NOT_FOUND) {
		cout << "File not found" << endl;
		return;
	}

	int position = result.find_last_of(':', 0);
	string link = link.assign(result, 0, position);
	string port = link.assign(result, position + 1, result.length() - position);

	SlaveServerCommunication *ssc = new SlaveServerCommunication(link, port);
	result = ssc->deleteFile(remoteFileName);
	//TODO check result
	//if( )
	{
		this->localFiles->deleteFile(remoteFileName);
		this->mainServer->deleteFileACK(remoteFileName);
	}

}

void Logic::showServerFiles() {
	map<string, int>::iterator it = this->remoteFiles->getFilesList()->begin();
	for (; it != this->remoteFiles->getFilesList()->end(); it++) {
		cout  << it->first << endl;
	}
}

void Logic::showMyFiles() {
	map<string, int>::iterator it = this->localFiles->getFilesList()->begin();
	for (; it != this->localFiles->getFilesList()->end(); it++) {
		cout << it->first << endl;
	}
}

void Logic::syncFiles() {
	vector<string>::iterator it = this->diffs->begin();
	for (; it != this->diffs->end(); it++) {
		this->getFile(*it);
	}
}

Logic::~Logic() {
	delete this->mainServer;
	delete this->localFiles;
	delete this->remoteFiles;
}

void Logic::generateDiffs() {
	map<string, int>::iterator it = this->remoteFiles->getFilesList()->begin();
	map<string, int>::iterator it2 = this->localFiles->getFilesList()->begin();
	bool found;
	for (; it != this->remoteFiles->getFilesList()->end(); it++) {
		found = false;
		for (; it2 != this->localFiles->getFilesList()->end(); it++) {
			if (it->first.compare(it2->first.c_str()) == 0) {
				found = true;
				break;
			}
		}
		if (!found)
			this->diffs->push_back(it->first);
	}
}

void Logic::showDiffs()
{
	cout << "PLIKI KTORE ISTNIEJA NA SERWERZE" << endl;
	vector<string>::iterator it = this->diffs->begin();
		for (; it != this->diffs->end(); it++) {
			cout << *it << endl;
		}
}
