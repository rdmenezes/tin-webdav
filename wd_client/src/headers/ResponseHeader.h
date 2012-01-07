#ifndef RESPONSEHEADER_H
#define RESPONSEHEADER_H

#include <string>

using namespace std;

class ResponseHeader{

private:
	string header;
	
public:

	ResponseHeader();
	~ResponseHeader();
	
	//wszystkie rzucaja wyjatek w przypadku nieprawidłowego kodu, ale i tak lepiej zapewnic dobry
	
	/*
	 * Nie wszystkie kody odpowiedzi sa potrzebne, ale na wszelki wypadek dalem je juz
	 * 
	 * Kody odpowiedzi:
	 * 403 - Forbidden (np. jesli nie mozna z jakiegos powodu wykonac zapytania) - wszystkie
	 * 500 - Internal Server Error - wszystkie
	 * 423 - Locked (zasob zablokowany przez innego uzytkownika) - wszystkie
	 * 404 - Not Found (nie ma takiego pliku na serwerze) - get, delete, lock, unlock
	 * 201 - Created(utworzono plik, folder) - put(przy tworzeniu nowego pliku), mkcol
	 * 204 - No Content(pozytywna odpowiedz) - put(przy zastępowaniu pliku), delete, unlock
	 * 405 - Method Not Allowed(taki folder juz istnieje) - mkcol
	 * 409 - Conflict(np. przy tworzeniu /ha/he/aa, gdzie /he nie istnieje, zdecyduj Sajmon, czy chcesz tego uzywac:P) - mkcol
	 * 200 - OK(pozytywna odpowiedz z zawartoscia, przesylany plik lub xml przy locku) - get, lock
	 */
	
	void makePutResponse(int code);
	void makeDeleteResponse(int code);
	void makeLockResponse(int code);
	void makeGetResponse(int code, string type, int len);	//jesli kod odpowiedzi inny od 200, podac byle jakie wartosci type i len
	void makeMkcolResponse(int code);
	void makeUnlockResponse(int code);
	
	string getResponseHeader();		//zwraca naglowek odpowiedzi
	
	int getResponseCode();	//zwraca kod odpowiedzi
	
	/* Obie funkcje tylko dla pozytywnej odpowiedzi zapytania GET */ 
	string getType();	//typ pliku
	int getLenght();	//dlugosc pliku
	
	
	/*
	 * zwraca miejsce od poczatku tablicy, w którym konczy się nagłówek, a zaczyna zawartość pliku,
	 *-1 jeśli w buforze jest tylko nagłówek lub 0 jeśli jest tylko nagłówek i się kończy.
	 * 
	 * Parametry:
	 * buf - odebrana tablica
	 * len - ilosc odebranych bajtow
	 * getOrLock - czy to pozytywna odpowiedz na get/lock(okreslane, jesli poprzednie wywolanie tej funkcji zwroci jakas liczbe dodatnia rozna od 0)
	 * cont - czy kontynuacja odbierania naglowka
	 * UWAGA: put i cont za pierwszym razem zawsze false
	 */
	int recvResponse(char* buf, int len, bool getOrLock, bool cont);	//TYLKO DLA KLIENTA
	
};

#endif
