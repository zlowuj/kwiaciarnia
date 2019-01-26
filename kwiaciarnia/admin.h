#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "db_klasa.h"
using namespace std;
class admin
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
		elem[10] = "nowe";
		int length = sizeof(elem) / sizeof(string);
		db_klasa dodaj_uzytkownik = db_klasa();
		dodaj_uzytkownik.dodaj(elem, length);
	}
};

