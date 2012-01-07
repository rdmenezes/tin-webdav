/*
 * Communication.cpp
 *
 *  Created on: 06-01-2012
 *      Author: Jacek
 */

#include "Communication.h"
//#include <sys/types.h>
//#include <sys/socket.h>
#include <string>
#include "headers/RequestHeader.h"
#include "Answers.h"
#include "Settings.h"

using namespace std;
Communication::Communication()
{
}

Communication::Communication(string address, string port) {
	this->address = address;
	this->port = port;
	reqHeader = new RequestHeader();
}

int Communication::connect() {
	int sock = -1;
	//struct sockaddr_in server;
	//struct hostent *hp;
	return sock;

	/* Create socket. */
	/*sock = socket( AF_INET, SOCK_STREAM, 0 );
	 if (sock == -1) {
	 perror("opening stream socket");
	 return -1;
	 }

	 // uzyskajmy adres IP z nazwy ...
	 server.sin_family = AF_INET;
	 hp = gethostbyname(argv[1]);
	 // hostbyname zwraca strukture zawierajaca adres danego hosta
	 if (hp == (struct hostent *) 0) {
	 fprintf(stderr, "%s: unknown host\n", argv[1]);
	 return -1;
	 }
	 memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	 server.sin_port = htons(atoi( argv[2]));
	 if (connect(sock, (struct sockaddr *) &server, sizeof server) == -1) {
	 perror("connecting stream socket");
	 return -1;
	 }*/

}

void Communication::disconnect(int sock) {
//	close(sock);
}


Communication::~Communication() {
	delete reqHeader;
}

string Communication::sendAndWaitForReply(string message){
	int socket = this->connect();
	char *charMessage = new char[message.size() + 1];
	char receive[1024];
	//ofstream result;

	strcpy(charMessage, message.c_str());
//	if (write( sock, charMessage, sizeof(charMessage) ) == -1)
	{
		//	perror("writing on stream socket");
		delete[] charMessage;
		return Answers::CONNECTION_ERROR;
	}
	//TODO read all result in loop ( -> stream ->string )
//	if( read(sock,receive,1024) == -1);
	{
		//	perror("ERROR reading from socket");
		delete[] charMessage;
		return Answers::CONNECTION_ERROR;
	}
	delete[] charMessage;
	disconnect(socket);
	return receive;
}
