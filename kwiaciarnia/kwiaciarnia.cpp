// kwiaciarnia.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <algorithm>
#include "db_klasa.h"
#include "admin.h"
//#include "sqlite3.h"
using namespace std;

int konto = 0, nowe = 0;
string id, uprawnienia, czy_nowe;
int haslo_callback (void *unused, int ile, char **data, char **kolumny) {
	for (int i = 0; i < ile; i++)
	{
		czy_nowe = data[5];
		id = data[0];
		if (czy_nowe == "nowe") nowe = 1;
		//cout << "nowe = " << nowe << endl;
		//cout << kolumny[i] << " = " << data[i] << endl;
	}
	return 0;
}
int nie_pisz_callback(void *unused, int ile, char **data, char **kolumny) {
	for (int i = 0; i < ile; i++)
	{
		id = data[0];
		uprawnienia = data[3];
		konto = 1;
	}
	return 0;
}
int callback(void *unused, int ile, char **data, char **kolumny) {
	for (int i = 0; i < ile; i++)
	{
		cout << kolumny[i] << " = " << data[i] << endl;
	}
	return 0;
}
int djb2(string s)
{
	unsigned long hash = 5381;
	char c;
	for (int i = 0; i<s.size(); i++)
	{
		c = s[i];
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return hash;
}
string poprawnosc_haslo(string sprawdz, string nazwa)
{
	char znak;
	string ukrycie;
	int poprawnosc = 1;
	for (int i = 0; i < sprawdz.length(); i++)
	{
		if (sprawdz[i] == 32) poprawnosc = 0;
		//cout << sprawdz[i] << endl;
	}
	while (poprawnosc == 0)
	{
		cout << endl;
		cout << "niepoprawne haslo(wykryto spacje), wprowadz haslo jeszcze raz: ";
		sprawdz = "";
		while ((znak = _getch()) != 13)
		{
			ukrycie += znak;
		}
		for (int i = 0; i < ukrycie.length(); i++)
		{
			if (ukrycie[i] != 0)
			{
				sprawdz += ukrycie[i];
			}
		}
		poprawnosc = 1;
		for (int i = 0; i < sprawdz.length(); i++)
		{
			if (sprawdz[i] == 32) poprawnosc = 0;
			//cout << sprawdz[i] << endl;
		}
	}

	return sprawdz;
}
void stworz_haslo()
{
	char znak;
	string ukrycie, haslo1, skrot, haslo2;
	cout << "wpisz nowe haslo(bez spacji): ";
	while ((znak = _getch()) != 13)
	{
		ukrycie += znak;
	}
	for (int i = 0; i < ukrycie.length(); i++)
	{
		if (ukrycie[i] != 0)
		{
			haslo1 += ukrycie[i];
		}
	}
	haslo1 = poprawnosc_haslo(haslo1, "haslo");
	cout << endl;
	cout << "powtorz haslo: ";
	ukrycie = "";
	while ((znak = _getch()) != 13)
	{
		ukrycie += znak;
	}
	for (int i = 0; i < ukrycie.length(); i++)
	{
		if (ukrycie[i] != 0)
		{
			haslo2 += ukrycie[i];
		}
	}
	cout << endl;
	//cout << "HASLO1 = " << haslo1 << endl << "HASLO2 = " << haslo2 << endl;
	while(haslo1 != haslo2)
	{
		cout << "nie poprawnie wprowadzono hasla" << endl;
		cout << "wpisz haslo(bez spacji): ";
		while ((znak = _getch()) != 13)
		{
			ukrycie += znak;
		}
		for (int i = 0; i < ukrycie.length(); i++)
		{
			if (ukrycie[i] != 0)
			{
				haslo1 += ukrycie[i];
			}
		}
		haslo1 = poprawnosc_haslo(haslo1, "haslo");
		cout << endl;
		cout << "wpisz ponownie haslo: ";
		while ((znak = _getch()) != 13)
		{
			ukrycie += znak;
		}
		for (int i = 0; i < ukrycie.length(); i++)
		{
			if (ukrycie[i] != 0)
			{
				haslo2 += ukrycie[i];
			}
		}
		cout << endl;
	}
	//cout << "HASLO: " << haslo1 << endl;
	skrot = djb2(haslo1);
	/*string pytanie = "UPDATE konta SET haslo = ";
	pytanie += skrot;
	pytanie += "' where ";*/
	cout << "id = " << id << endl;
	system("pause");
}
void wpisz_haslo(string login)
{
	sqlite3 *db;
	sqlite3_open("bd_kwiaciarnia.db", &db);
	char znak;
	string ukrycie, haslo, skrot;
	cout << "haslo: ";
	while ((znak = _getch()) != 13)
	{
		ukrycie += znak;
	}
	for (int i = 0; i < ukrycie.length(); i++)
	{
		if (ukrycie[i] != 0)
		{
			haslo += ukrycie[i];
		}
	}
	skrot = djb2(haslo);
	string pytanie = "SELECT * FROM konta WHERE login = '";
	pytanie += login;
	pytanie += "' AND haslo = '";
	pytanie += skrot;
	pytanie += "'";
	const char *select = pytanie.c_str();
	//cout << select << endl;
	sqlite3_exec(db, select, nie_pisz_callback, NULL, NULL);
	sqlite3_close(db);
}
void logowanie()
{
	sqlite3 *db;
	sqlite3_open("bd_kwiaciarnia.db", &db);
	char znak;
	string login, ukrycie, haslo, skrot;
	cout << "KWIACIARNIA" << endl << "login: ";
	cin >> login;
	string pytanie = "SELECT * FROM konta WHERE login = '";
	pytanie += login;
	pytanie += "'";
	const char *select = pytanie.c_str();
	sqlite3_exec(db, select, haslo_callback, NULL, NULL);
	if (nowe == 1)
	{
		stworz_haslo();
	}
	else
	{
		wpisz_haslo(login);
	}
	nowe = 0;
	sqlite3_close(db);
}
int main()
{
	sqlite3 *db;
	logowanie();
	while (konto == 0)
	{
		system("cls");
		cout << "niepoprawny login lub haslo" << endl;
		logowanie();
	}
	//cout << "id = " << id << endl;
	//cout << "uprawnienia = " << uprawnienia << endl;
	//system("pause");
	system("cls");
	cout << "dane zalogowanego uzytkownika:" << endl;
	sqlite3_open("bd_kwiaciarnia.db", &db);
	string pytanie = "SELECT imie, nazwisko FROM konta WHERE id = ";
	pytanie += id;
	const char *select = pytanie.c_str();
	//cout << select << endl;
	sqlite3_exec(db, select, callback, NULL, NULL);
	sqlite3_close(db);
	if (uprawnienia == "1")
	{
		cout << "ADMINISTRATOR" << endl;
	}
	else
	{
		cout << "KLIENT" << endl;
	}
	while (uprawnienia=="1")
	{
		int wybor = 0;
		cout << "1-stworz nowe konto" << endl;
		cin >> wybor;
		if (wybor == 1)
		{
			admin nowy_uzytkownik = admin();
			nowy_uzytkownik.dodaj();
		}
		system("cls");
		cout << "dane zalogowanego uzytkownika:" << endl;
		sqlite3_open("bd_kwiaciarnia.db", &db);
		string pytanie = "SELECT imie, nazwisko FROM konta WHERE id = ";
		pytanie += id;
		const char *select = pytanie.c_str();
		//cout << select << endl;
		sqlite3_exec(db, select, callback, NULL, NULL);
		sqlite3_close(db);
	}
	while (uprawnienia == "0")
	{
		int wybor = 0;
		cout << "1-zloz zamowienie" << endl;
		cin >> wybor;
	}
    return 0;
}

