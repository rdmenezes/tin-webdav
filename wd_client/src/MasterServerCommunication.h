/*
 * MasterServerCommunication.h
 *
 *  Created on: 07-01-2012
 *      Author: Jacek
 */

#ifndef MASTERSERVERCOMMUNICATION_H_
#define MASTERSERVERCOMMUNICATION_H_
#include "Communication.h"
#include <string>

class MasterServerCommunication : public Communication {
public:
	MasterServerCommunication(string address, string port);
	string getFilesList();
	string sendFile(string localFileName);
	string sendFileACK(string localFileName);
	string getFile(string remoteFileName);
	string deleteFile(string fileName);
	string deleteFileACK(string fileName);

	virtual ~MasterServerCommunication();
};

#endif /* MASTERSERVERCOMMUNICATION_H_ */
