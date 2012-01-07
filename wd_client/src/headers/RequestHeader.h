#ifndef REQUESTHEADER_H
#define REQUESTHEADER_H

#include <string>

using namespace std;

class RequestHeader {
	/* Content-Lenght
	 * Content-Type
	 * Host
	 * nazwa metody, sciezka, http/1.1
	 * charset
	 * Timeout(LOCK)
	 * Lock-Token
	 */
private:
	string header;	//zawartosc nagłówka
	

public:
	RequestHeader();
	~RequestHeader();
	
	/*Należy zapewnić poprawność przekazywanych danych*/
	
	void makeGetHeader(string path, string host);
	void makePutHeader(string path, string host, string type, int len/*, string token*/);
	void makeDeleteHeader(string path, string host);
	void makeLockHeader(string path, string host, string time); 	//w zasadzie time nie jest zbyt wazny, ale mozna podac to: "Infinity, Second-4100000000"
	void makeUnlockHeader(string path, string host, string token);
	void makeMkcolHeader(string path, string host);
	
	string getHeader(); //zwraca nagłówek, trzeba w kliencie przeformatowac na tablice char,
						//np. tak: strcpy(buf, s.c_str()), s - zwrocony string

	string getHeaderFieldValue(string field);	//Ważne: przekazac nazwę bez dwukropka i spacji

	string getMethod();	//zwraca metodę jaką dotyczy dane zapytanie
	

	/*
	 * zwraca miejsce od poczatku tablicy, w którym konczy się nagłówek, a zaczyna zawartość pliku,
	 *-1 jeśli w buforze jest tylko nagłówek lub 0 jeśli jest tylko nagłówek i się kończy.
	 * 
	 * Parametry:
	 * buf - odebrana tablica
	 * len - ilosc odebranych bajtow
	 * put - czy to metoda put(okreslane, jesli poprzednie wywolanie tej funkcji zwroci jakas liczbe dodatnia rozna od 0)
	 * cont - czy kontynuacja odbierania naglowka
	 * UWAGA: put i cont za pierwszym razem zawsze false
	 */
	int recvHeader(char* buf, int len, bool put, bool cont);		//TYLKO DLA SERWERA
};
#endif
