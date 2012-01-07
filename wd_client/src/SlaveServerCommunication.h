/*
 * SlaveServerCommunication.h
 *
 *  Created on: 07-01-2012
 *      Author: Jacek
 */

#ifndef SLAVESERVERCOMMUNICATION_H_
#define SLAVESERVERCOMMUNICATION_H_
#include "Communication.h"
#include <string>
#include "Settings.h"
using namespace std;

class SlaveServerCommunication: public Communication {
public:
	SlaveServerCommunication(string address, string port);
	string sendFile(string localFileName, char *fileContent);
	string getFile(string remoteFileName);
	string deleteFile(string fileName);
	string lockFile(string remoteFileName);
	string unlockFile(string remoteFileName);

	virtual ~SlaveServerCommunication();

};

#endif /* SLAVESERVERCOMMUNICATION_H_ */
