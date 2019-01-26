#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "db_klasa.h"
using namespace std;
class admin : public db_klasa
{
public:
	admin();
	~admin();
	string poprawnosc_liczba(string sprawdz, string nazwa)
	{
		int x, y = 0;
		for (int i = 0; i<sprawdz.length(); i++)
		{
			x = sprawdz[i] - 48;
			if (x > 9 || x<0) y = 1;
		}
		while (y == 1)
		{
			cout << "niepoprawnie wprowadzono " << nazwa << ", podaj jeszcze raz: " << endl;
			cin >> sprawdz;
			y = 0;
			for (int i = 0; i<sprawdz.length(); i++)
			{
				x = sprawdz[i] - 48;
				if (x > 9) y = 1;
			}
		}
		return sprawdz;
	}
	string poprawnosc_string(string sprawdz, string nazwa)
	{
		int x, y = 0;
		for (int i = 0; i<sprawdz.length(); i++)
		{
			x = sprawdz[i] - 48;
			if (x < 10 && x >= 0) y = 1;
		}
		while (y == 1)
		{
			cout << "niepoprawnie wprowadzono " << nazwa << ", podaj jeszcze raz: " << endl;
			cin >> sprawdz;
			//getline(cin, sprawdz);
			y = 0;
			for (int i = 0; i<sprawdz.length(); i++)
			{
				x = sprawdz[i] - 48;
				if (x < 10 && x >= 0) y = 1;
			}
		}
		return sprawdz;
	}
	string poprawnosc_login(string sprawdz, string nazwa)
	{
		int poprawnosc = 1;
		for (int i = 0; i < sprawdz.length(); i++)
		{
			if (sprawdz[i] == 32) poprawnosc = 0;
			//cout << sprawdz[i] << endl;
		}
		while (poprawnosc == 0)
		{
			cout << "niepoprawny login(wykryto spacje), wprowadz login jeszcze raz: ";
			getline(cin, sprawdz);
			poprawnosc = 1;
			for (int i = 0; i < sprawdz.length(); i++)
			{
				if (sprawdz[i] == 32) poprawnosc = 0;
				//cout << sprawdz[i] << endl;
			}
		}
		
		return sprawdz;
	}
	static int powtorzenie_callback(void *nie_uzywane, int ile, char **data, char **kolumny) {
		int i = 0;
		for (i = 0; i < ile; i++)
		{
			//cout << kolumny[i] << " = " << data[i] << endl;
		}
		if (i > 0) return 1;
		else return 0;
	}
	static int wypisz_callback(void *nie_uzywane, int ile, char **data, char **kolumny) {
		int i = 0;
		for (i = 0; i < ile; i++)
		{
			cout << kolumny[i] << " = " << data[i] << endl;
		}
		if (i > 0) return 1;
		else return 0;
	}
	string male_litery(string tekst)
	{
		int ascii;
		for (int i = 0; i < tekst.length(); i++)
		{
			if (tekst[i] <= 90 && tekst[i] >= 65) tekst[i] += 32;
		}
		return tekst;
	}
	void dodaj()
	{
		string elem[11];
		string sprawdz;
		int poprawnosc;
		int ostatnia;
		elem[0] = "konta";
		elem[1] = "imie";
		elem[2] = "nazwisko";
		elem[3] = "administrator";
		elem[4] = "login";
		elem[5] = "haslo";
		cout << "podaj imie uzytkownika: ";
		cin >> elem[6];
		elem[8] = this->poprawnosc_string(elem[6], elem[1]);
		while (elem[6].length() < 3)
		{
			cout << "zbyt krotkie imie, podaj jeszcze raz: " << endl;
			cin >> elem[6];
			elem[6] = this->poprawnosc_string(elem[6], elem[1]);
		}
		cout << "podaj nazwisko uzytkownika: ";
		cin >> elem[7];
		elem[9] = this->poprawnosc_string(elem[7], elem[2]);
		while (elem[7].length() < 3)
		{
			cout << "zbyt krotkie nazwisko, podaj jeszcze raz: " << endl;
			cin >> elem[7];
			elem[7] = this->poprawnosc_string(elem[7], elem[2]);
		}
		cout << "0-klient, 1-administrator: ";
		cin >> elem[8];
		while (elem[8] != "0" && elem[8] != "1")
		{
			cout<<"zle wybrana opcja, wybierz jeszcze raz" <<endl << "0-klient, 1-administrator: ";
			cin >> elem[8];
		}
		cout << "podaj login uzytkownika, spacje nie dozwolone: ";
		getline(cin, elem[9]);
		getline(cin, elem[9]);
		elem[9] = this->poprawnosc_login(elem[9], elem[4]); 
		string pytanie = "SELECT * FROM konta WHERE login = '";
		pytanie += elem[9];
		pytanie += "'";
		const char *select = pytanie.c_str();
		sqlite3_open("bd_kwiaciarnia.db", &db);
		int zajete = sqlite3_exec(db, select, powtorzenie_callback, NULL, NULL);
		sqlite3_close(db);
		while (zajete == 4)
		{
			cout << "podany login jest juz zajety, wprowadz login jeszcze raz: " << endl;
			getline(cin, elem[9]);
			//getline(cin, elem[9]);
			elem[9] = this->poprawnosc_login(elem[9], elem[4]);
			pytanie = "SELECT * FROM konta WHERE login = '";
			pytanie += elem[9];
			pytanie += "'";
			select = pytanie.c_str();
			sqlite3_open("bd_kwiaciarnia.db", &db);
			zajete = sqlite3_exec(db, select, powtorzenie_callback, NULL, NULL);
			sqlite3_close(db);
		}
		elem[10] = "nowe";
		int length = sizeof(elem) / sizeof(string);
		db_klasa dodaj_uzytkownik = db_klasa();
		dodaj_uzytkownik.dodaj(elem, length);
	}
	void zmien()
	{
		string elem[3], ID;
		elem[0] = "kwiaty";
		elem[1] = "sztuk";
		cout << "podaj id kwiatka: ";
		cin >> ID;
		string pytanie = "SELECT * FROM kwiaty WHERE id = ";
		pytanie += ID;
		const char *select = pytanie.c_str();
		system("cls");
		sqlite3_open("bd_kwiaciarnia.db", &db);
		int istnieje = sqlite3_exec(db, select, wypisz_callback, NULL, NULL);
		sqlite3_close(db);
		while(istnieje == 0)
		{
			cout << "nie istnieje podany kwiatek w bazie danych, wpisz id jeszcze raz: ";
			cin >> ID;
			pytanie = "SELECT * FROM kwiaty WHERE id = ";
			pytanie += ID;
			select = pytanie.c_str();
			system("cls");
			sqlite3_open("bd_kwiaciarnia.db", &db);
			istnieje = sqlite3_exec(db, select, wypisz_callback, NULL, NULL);
			sqlite3_close(db);
		}
		cout << "podaj ilosc sztuk kwiatka: ";
		cin >> elem[2];
		elem[2] = this->poprawnosc_liczba(elem[2], elem[1]);
		int length = sizeof(elem) / sizeof(string);
		db_klasa zmien_kwiaty = db_klasa();
		zmien_kwiaty.aktualizuj(elem, length, ID);
	}
	void dodaj_kwiat()
	{
		string elem[5];
		elem[0] = "kwiaty";
		elem[1] = "nazwa";
		elem[2] = "sztuk";
		cout << "podaj nazwe kwiatka: ";
		getline(cin, elem[3]);
		getline(cin, elem[3]);
		elem[3] = male_litery(elem[3]);
		string pytanie = "SELECT * FROM kwiaty WHERE nazwa = '";
		pytanie += elem[3];
		pytanie += "'";
		const char *select = pytanie.c_str();
		//system("cls");
		sqlite3_open("bd_kwiaciarnia.db", &db);
		int istnieje = sqlite3_exec(db, select, wypisz_callback, NULL, NULL);
		sqlite3_close(db);
		while (istnieje == 4)
		{
			cout << "istnieje juz kwiat o takiej nazwie, wpisz ponownie nazwe: ";
			getline(cin, elem[3]);
			elem[3] = male_litery(elem[3]);
			pytanie = "SELECT * FROM kwiaty WHERE nazwa = '";
			pytanie += elem[3];
			pytanie += "'";
			select = pytanie.c_str();
			system("cls");
			sqlite3_open("bd_kwiaciarnia.db", &db);
			istnieje = sqlite3_exec(db, select, wypisz_callback, NULL, NULL);
			sqlite3_close(db);
		}
		cout << "podaj ilosc sztuk dostepnych do sprzedazy: ";
		cin >> elem[4];
		elem[4] = this->poprawnosc_liczba(elem[4], elem[2]);
		int length = sizeof(elem) / sizeof(string);
		db_klasa dodaj_kwiat = db_klasa();
		dodaj_kwiat.dodaj(elem, length);
	}
};

