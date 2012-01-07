
#include "RequestHeader.h"

#include <sstream>

using namespace std;

RequestHeader::RequestHeader(){
	//header();
}

RequestHeader::~RequestHeader(){
	
}

void RequestHeader::makeGetHeader(string path, string host){
	header += "GET ";
	header += path;
	header += " HTTP/1.1\n";
	header += "Host: ";
	header += host;
	header += "\n";
}

void RequestHeader::makePutHeader(string path, string host, string type, int len){
	header += "PUT ";
	header += path;
	header += " HTTP/1.1\n";
	header += "Host: ";
	header += host;
	header += "\nContent-Type: ";
	header += type;
	header += "\nContent-Lenght: ";
	stringstream ss;
	ss << len;
	header += ss.str();
	header += "\n\n";
}

void RequestHeader::makeDeleteHeader(string path, string host){
	header += "DELETE ";
	header += path;
	header += " HTTP/1.1\n";
	header += "Host: ";
	header += host;
	header += "\n";
}


void RequestHeader::makeLockHeader(string path, string host, string time = "Infinite, Second-4100000000"){
	header += "LOCK ";
	header += path;
	header += " HTTP/1.1\n";
	header += "Host: ";
	header += host;
	header += "\nTimeout: ";
	header += time;
	header += "\n";
}

void RequestHeader::makeUnlockHeader(string path, string host, string token){
	header += "UNLOCK ";
	header += path;
	header += " HTTP/1.1\n";
	header += "Host: ";
	header += host;
	header += "\nLock-Token: ";
	header += token;
	header += "\n";
}

void RequestHeader::makeMkcolHeader(string path, string host){
	header += "MKCOL ";
	header += path;
	header += " HTTP/1.1\n";
	header += "Host: ";
	header += host;
	header += "\n";
}

string RequestHeader::getHeader(){
	//char buf[header.size()];
	//header.copy(buf,header.size());
	return header;
}

string RequestHeader::getHeaderFieldValue(string field){
	size_t found;
	size_t help;
	string ret;
	found = header.find(field);
	if(found != string::npos){
		help = header.find("\n", found);
		if(help != string::npos){
			ret = header.substr(found+field.size()+2, (help - found+field.size()+2));
			return ret;
		}
	}
	return NULL;
}

string RequestHeader::getMethod(){
	if(header.empty())
		return NULL;
	int help = header.find(" ");
	string ret = header.substr(0, help);
	return ret;
}

int RequestHeader::recvHeader(char* buf, int len, bool put, bool cont){
	if((buf[0] == 'P' && buf[1] == 'U' && buf[2] == 'T') || put == true){
		for(int i = 0; i<len; i++){
			if(i != len - 1){
				if(buf[i] == '\n' && buf[i+1] == '\n'){
					if(cont == false)
						header.assign(buf, i);
					else
						header.append(buf, i);
					if(i != len - 2)
						return i+2;
					else
						return 0;
				}
			} else {
				if(cont == false)
					header.assign(buf);
				else
					header.append(buf);
			}
		}
		return -1;
	} else {
		for(int i = 0; i<len; i++){
				if(buf[i] == '\n' && buf[i+1] == '\0'){
					if(cont == false)
						header.assign(buf, i);
					else
						header.append(buf, i);
					return 0;
				}
		}
		header.assign(buf);
		return -1;
	}
}
			

