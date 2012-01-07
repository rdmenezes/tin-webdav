/*
 * MasterServerCommunication.cpp
 *
 *  Created on: 07-01-2012
 *      Author: Jacek
 */

#include "MasterServerCommunication.h"

MasterServerCommunication::MasterServerCommunication(string address, string port) {
	Communication(address, port);
}

string MasterServerCommunication::sendFile(string localFileName) {
	string header = "SEND "+localFileName;
	return sendAndWaitForReply(header);
}

string MasterServerCommunication::sendFileACK(string localFileName) {
	string header = "SENT "+localFileName;
	return sendAndWaitForReply(header);
}

string MasterServerCommunication::getFile(string remoteFileName) {
	string header = "GET "+remoteFileName;
	return sendAndWaitForReply(header);
}

string MasterServerCommunication::deleteFile(string fileName) {
	string header = "DELETE "+fileName;
	return sendAndWaitForReply(header);
}

string MasterServerCommunication::deleteFileACK(string fileName) {
	string header = "DELETED "+fileName;
	return sendAndWaitForReply(header);
}

string MasterServerCommunication::getFilesList() {
	string header = "LIST";
	return sendAndWaitForReply(header);
}

MasterServerCommunication::~MasterServerCommunication() {
}

