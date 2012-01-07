#include<string.h>
//#include
/*
 * Communication.h
 *
 *  Created on: 06-01-2012
 *      Author: Jacek
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_
#include <string>
#include "headers/RequestHeader.h"
using namespace std;

class Communication {
public:
	Communication();
	Communication(string addr, string port);
	virtual ~Communication();
protected:
	int connect();
	void disconnect(int sock);
	string sendAndWaitForReply(string message);
	string address;
	string port;
	RequestHeader *reqHeader;
};

#endif /* COMMUNICATION_H_ */
