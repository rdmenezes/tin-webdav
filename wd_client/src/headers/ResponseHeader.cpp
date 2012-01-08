
#include "ResponseHeader.h"
#include <sstream>
#include <exception>

using namespace std;

ResponseHeader::ResponseHeader(){
}

ResponseHeader::~ResponseHeader(){
}


void ResponseHeader::makePutResponse(int code){
	header = "HTTP/1.1 ";
	
	if(code == 201){
		header += "201 Created";
	} else if(code == 204){
		header += "204 No Content";
	} else if(code == 403){
		header += "403 Forbidden";
	} else if(code == 500){
		header += "500 Internal Server Error";
	} else if(code == 423){
		header += "423 Locked";
	} else {
		throw "Niepoprawny kod odpowiedzi";
	}
	header += "\n";
}

void ResponseHeader::makeDeleteResponse(int code){
	header = "HTTP/1.1 ";
	
	if(code == 204){
		header += "204 No Content";
	} else if(code == 403){
		header += "403 Forbidden";
	} else if(code == 423){
		header += "423 Locked";
	} else if(code == 500){
		header += "500 Internal Server Error";
	} else if(code == 404){
		header += "404 Not Found";
	} else {
		throw "Niepoprawny kod odpowiedzi";
	}
	header += "\n";
}

void ResponseHeader::makeMkcolResponse(int code){
	header = "HTTP/1.1 ";
	
	if(code == 201){
		header += "201 Created";
	} else if(code == 403){
		header += "403 Forbidden";
	} else if(code == 500){
		header += "500 Internal Server Error";
	} else if(code == 405){
		header += "405 Method Not Allowed";
	} else if(code == 409){
		header += "409 Conflict";
	} else {
		throw "Niepoprawny kod odpowiedzi";
	}
	header += "\n";
}

void ResponseHeader::makeUnlockResponse(int code){
	header = "HTTP/1.1 ";
	
	if(code == 204){
		header += "204 No Content";
	} else if(code == 403){
		header += "403 Forbidden";
	} else if(code == 404){
		header += "404 Not Found";
	} else if(code == 400){
		header += "400 Bad Request";
	} else if(code == 500){
		header += "500 Internal Server Error";
	} else {
		throw "Niepoprawny kod odpowiedzi";
	}
	header += "\n";
}

void ResponseHeader::makeGetResponse(int code, string type, int len){
	header = "HTTP/1.1 ";
	
	if(code == 200){
		header += "200 OK\n";
		header += "Content-Type: ";
		header += type;
		header += "\nContent-Lenght: ";
		stringstream ss;
		ss << len;
		header += ss.str();
		header += "\n";
	} else if(code ==  403){
		header += "403 Forbidden";
	} else if(code == 404){
		header += "404 Not Found";
	} else if(code == 423){
		header += "423 Locked";
	} else if(code == 500){
		header += "500 Internal Server Error";
	} else {
		throw "Niepoprawny kod odpowiedzi";
	}
	header += "\n";
}

void ResponseHeader::makeLockResponse(int code){
	header = "HTTP/1.1 ";
	
	if(code == 200){
		header += "200 OK\n";
		header += "Content-Type: ";
		header += "text/xml; charset=\"utf-8\"";
		header += "\nContent-Lenght: ";
		header += "XXXX";
		header += "\n";
	} else if(code == 403){
		header += "403 Forbidden";
	} else if(code == 404){
		header += "404 Not Found";
	} else if(code == 423){
		header += "423 Locked";
	} else if(code == 500){
		header += "500 Internal Server Error";
	} else {
		throw "Niepoprawny kod odpowiedzi";
	}
	header += "\n";
}

string ResponseHeader::getResponseHeader(){
	return header;
}

int ResponseHeader::getResponseCode(){
		string help = header.substr(9, 3);
		int i;
		istringstream iss(help);
		iss >> i;
		return i;
}

string ResponseHeader::getType(){
	if(getResponseCode() != 200)
		return NULL;
	size_t found1 = header.find("Content-Type");
	size_t found2 = header.find("\n", found1);
	
	string ret = header.substr(found1 + 14, found2 - (found1 + 14));
	
	return ret;
}

int ResponseHeader::getLenght(){
	if(getResponseCode() != 200)
		return -1;
	size_t found1 = header.find("Content-Lenght");
	size_t found2 = header.find("\n", found1);
	
	string ret = header.substr(found1 + 16, found2 - (found1 + 16));
	
	int i;
	istringstream iss(ret);
	iss >> i;
	return i;
}

int ResponseHeader::recvResponse(char* buf, int len, bool getOrLock, bool cont){
	if((buf[9] == '2' && buf[10] == '0' && buf[11] == '0') || getOrLock == true){
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
