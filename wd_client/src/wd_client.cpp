//============================================================================
// Name        : wd_client.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Logic.h"

using namespace std;

int main() {
	Logic *programLogic = new Logic();
	programLogic->onStart();
	string arg1, arg2;
	int x = 0;
	while (x > 5 || x < 1) {
		cout << "*******************MENU********************" << endl;
		cout << "1. Wyswietl lokaln¹ liste plikow " << endl;
		cout << "2. Wyswietl liste plikow na serwerze" << endl;
		cout << "3. Wyslij plik na serwer" << endl;
		cout << "4. Pobierz plik z serwera" << endl;
		cout << "5. Usun plik" << endl;
		cout << "6. Synchronizuj z serwerem" << endl;
		cout << "7. Wyjscie z programu" << endl;
		cout << "Wybieram : ";
		cin >> x;
	}

	switch (x) {
	case 1:
		cout << "LOKALNA LISTA PLIKOW" << endl;
		programLogic->showMyFiles();
		break;
	case 2:
		cout << "LISTA PLIKOW NA SERWERZE" << endl;
		programLogic->showServerFiles();
		break;
	case 3:
		cout << "WYSLIJ PLIK NA SERWER" << endl;
		cout << "PODAJ PELNA SCIEZKE DO PLIKU" << endl;
		cin >> arg1;
		programLogic->putFile(arg1);
		break;
	case 4:
		cout << "POBIERZ PLIK Z SERWERA" << endl;
		cout << "PODAJ RELATYWNA SCIEZKE DO PLIKU NA SERWERZE" << endl;
		cin >> arg1;
		programLogic->getFile(arg1);
		break;
	case 5:
		cout << "USUN PLIK (Z SERWERA I LOKALNIE)" << endl;
		cout << "PODAJ RELATYWNA SCIEZKE DO PLIKU" << endl;
		cin >> arg1;
		programLogic->deleteFile(arg1);
		break;
	case 6:
		cout << "SYNCHRONIZUJ PLIKI" << endl;
		cout << "PODAJ RELATYWNA SCIEZKE DO PLIKU NA SERWERZE" << endl;
		cin >> arg1;
		programLogic->getFile(arg1);
		break;
	case 7:
		programLogic->onEnd();
		return 0;
	}
}
