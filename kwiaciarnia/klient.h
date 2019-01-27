#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "db_klasa.h"
using namespace std;
class klient : public db_klasa
{
public:
	klient();
	~klient();
	static int pokaz_callback(void *nie_uzywane, int ile, char **data, char **kolumny) {
		int i = 0;
		for (i = 0; i < ile; i++)
		{
			cout << kolumny[i] << " = " << data[i] << endl;
		}
		if (i > 0) return 1;
		else return 0;
	}
	static int ukryty_callback(void *nie_uzywane, int ile, char **data, char **kolumny) {
		int i = 0;
		for (i = 0; i < ile; i++)
		{
			cout << kolumny[i] << " = " << data[i] << endl;
		}
		if (i > 0) return 1;
		else return 0;
	}
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
	int string_na_int(string zamiana)
	{
		int suma = 0;
		for (int i = 0; i < zamiana.length(); i++)
		{
			suma += (zamiana[i] - 48)*(pow(10, zamiana.length() - (i + 1)));
		}
		return suma;
	}
	void dodaj(string ID, string kwiat_id, string cena)
	{
		int wybor;
		string elem[9];
		elem[0] = "zamowienia";
		elem[1] = "id_klient";
		elem[2] = "id_kwiat";
		elem[3] = "sztuk_kwiatow";
		elem[4] = "cena";
		elem[5] = ID;
		elem[6] = kwiat_id;
		cout << "podaj ilosc sztuk kwiatow ktore chcesz kupic: ";
		cin >> elem[7];
		elem[7] = this->poprawnosc_liczba(elem[7], elem[3]);
		int razem = string_na_int(cena)*string_na_int(elem[7]);
		//cout << "RAZEM = " << razem << endl;
		int czy_zero = 0;
		char cyfra = (razem / 1000) + 48;
		string nowa_wartosc = "";
		if (cyfra == 48) czy_zero = 1;
		else nowa_wartosc += cyfra;
		razem = razem - (razem / 1000)*1000;
		cyfra = (razem / 100) + 48;
		if (cyfra == 48 && czy_zero == 1);
		else nowa_wartosc += cyfra;
		razem = razem - (razem / 100)*100;
		cyfra = (razem / 10) + 48;
		razem = razem - (razem / 10)*10;
		nowa_wartosc += cyfra;
		cyfra = (razem % 10) + 48;
		nowa_wartosc += cyfra;
		//cout << "nowa wartosc = " << nowa_wartosc << endl;
		//system("pause");
		elem[8] = nowa_wartosc;
		int length = sizeof(elem) / sizeof(string);
		db_klasa dodaj_zamowienie = db_klasa();
		dodaj_zamowienie.dodaj(elem, length);
	}
};

