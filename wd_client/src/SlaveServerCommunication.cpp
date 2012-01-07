/*
 * SlaveServerCommunication.cpp
 *
 *  Created on: 07-01-2012
 *      Author: Jacek
 */

#include "SlaveServerCommunication.h"

SlaveServerCommunication::SlaveServerCommunication(string address, string port) {
	Communication(address, port);
}

string SlaveServerCommunication::sendFile(string localFileName, char *fileContent) {
	reqHeader->makePutHeader(localFileName, address, Settings::TEXT_FILE_TYPE, sizeof(fileContent) );
	string header = reqHeader->getHeader();
	return sendAndWaitForReply(header);
}

string SlaveServerCommunication::getFile(string remoteFileName) {
	reqHeader->makeGetHeader(remoteFileName, address);
	string header = reqHeader->getHeader();
	return sendAndWaitForReply(header);
}

string SlaveServerCommunication::deleteFile(string fileName) {
	reqHeader->makeDeleteHeader(fileName, address);
	string header = reqHeader->getHeader();
	return sendAndWaitForReply(header);
}

string SlaveServerCommunication::lockFile(string remoteFileName) {
	reqHeader->makeLockHeader(remoteFileName, address, Settings::LOCK_TIME);
	string header = reqHeader->getHeader();
	return sendAndWaitForReply(header);
}

string SlaveServerCommunication::unlockFile(string remoteFileName) {
	reqHeader->makeUnlockHeader(remoteFileName, address, Settings::LOCK_TIME);
	string header = reqHeader->getHeader();
	return sendAndWaitForReply(header);
}

SlaveServerCommunication::~SlaveServerCommunication() {
}

