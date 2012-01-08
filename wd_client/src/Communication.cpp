/*
 * Communication.cpp
 *
 *  Created on: 06-01-2012
 *      Author: Jacek
 */

#include "Communication.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include "headers/RequestHeader.h"
#include "Answers.h"
#include "Settings.h"
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>

using namespace std;
Communication::Communication() {
}

Communication::Communication(string address, string port) {
	this->address = address;
	this->port = port;
	reqHeader = new RequestHeader();
}

void Communication::connectMe() {
	struct sockaddr_in server;
	struct hostent *hp;

	/* Create socket. */
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock == -1) {
		perror("opening stream socket");
		return ;
	}

	// uzyskajmy adres IP z nazwy ...
	server.sin_family = AF_INET;
	hp = gethostbyname(this->address.c_str());
	// hostbyname zwraca strukture zawierajaca adres danego hosta
	if (hp == (struct hostent *) 0) {
		fprintf(stderr, "%s: unknown host\n", this->address.c_str());
		return ;
	}
	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port = htons(atoi(this->port.c_str()));
	if (connect(this->sock, (struct sockaddr *) &server, sizeof server) == -1) {
		perror("connecting stream socket");
		return ;
	}

}

void Communication::disconnectMe() {
	close(this->sock);
}

Communication::~Communication() {
	delete reqHeader;
}

string Communication::sendAndWaitForReply(string message) {
	this->connectMe();
	char *charMessage = new char[message.size() + 1];
	char receive[1024];
	//ofstream result;

	strcpy(charMessage, message.c_str());
	if (write(this->sock, charMessage, sizeof(charMessage)) == -1) {
		perror("writing on stream socket");
		delete[] charMessage;
		return Answers::CONNECTION_ERROR;
	}
	//TODO read all result in loop ( -> stream ->string )
	if (read(this->sock, receive, sizeof(receive)) == -1)
	{
		perror("ERROR reading from socket");
		delete[] charMessage;
		return Answers::CONNECTION_ERROR;
	}
	delete[] charMessage;
	disconnectMe();
	return receive;
}
