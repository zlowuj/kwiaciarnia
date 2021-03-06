// kwiaciarnia.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <cmath>
#include <math.h>
#include <cstdio>
#include <vector>
#include <list> 
#include <iterator> 
#include <algorithm>
#include "db_klasa.h"
#include "admin.h"
#include "klient.h"
//#include "sqlite3.h"
using namespace std;

list <int> lista_cen;
int konto = 0, nowe = 0, srednia = 0, ilosc;
string id, uprawnienia, czy_nowe, id_kwiatka, ilosc_zamowienie, ilosc_kwiatka, cena_kwiatka;
int ceny[128];
int string_na_int(string zamiana)
{
	int suma = 0;
	for (int i = 0; i < zamiana.length(); i++)
	{
		suma += (zamiana[i] - 48)*(pow(10, zamiana.length() - (i + 1)));
	}
	return suma;
}
int klient_srednia_callback(void *unused, int ile, char **data, char **kolumny) {
	int i = 0;
	for (i = 0; i < ile; i++)
	{
		//ceny[ilosc]= string_na_int(data[i]);
		lista_cen.push_back(string_na_int(data[i]));
		ilosc++;
		srednia += string_na_int(data[i]);
		//cout << kolumny[i] << " = " << data[i] << endl;
	}
	//srednia = srednia / i;
	 return 0;
}
int cena_callback(void *unused, int ile, char **data, char **kolumny) {
	int i = 0;
	for (i = 0; i < ile; i++)
	{
		cena_kwiatka = data[3];
		//cout << kolumny[i] << " = " << data[i] << endl;
	}
	if (i > 0) return 1;
	else return 0;
}
int zatwierdz_callback(void *unused, int ile, char **data, char **kolumny) {
	int i = 0;
	for (i = 0; i < ile; i++)
	{
		id_kwiatka = data[2];
		ilosc_zamowienie = data[4];
		cout << kolumny[i] << " = " << data[i] << endl;
	}
	if (i > 0) return 1;
	else return 0;
}
int kwiatek_callback(void *unused, int ile, char **data, char **kolumny) {
	for (int i = 0; i < ile; i++)
	{
		ilosc_kwiatka = data[2];
		cout << kolumny[i] << " = " << data[i] << endl;
	}
	return 0;
}
int haslo_callback (void *unused, int ile, char **data, char **kolumny) {
	for (int i = 0; i < ile; i++)
	{
		czy_nowe = data[5];
		id = data[0];
		uprawnienia = data[3];
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
		//cout << kolumny[i] << " = " << data[i] << endl;
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
	sqlite3 *db;
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
	string pytanie = "UPDATE konta SET haslo = '";
	pytanie += skrot;
	pytanie += "' where id = ";
	pytanie += id;
	const char *select = pytanie.c_str();
	sqlite3_open("bd_kwiaciarnia.db", &db);
	sqlite3_exec(db, select, nie_pisz_callback, NULL, NULL);
	sqlite3_close(db);
	//cout << "id = " << id << endl;
	konto = 1;
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
	//system("pause");
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
	sqlite3_close(db);
	if (nowe == 1)
	{
		stworz_haslo();
	}
	else
	{
		wpisz_haslo(login);
	}
	nowe = 0;
	
}
void pokaz_zamowienie()
{
	sqlite3 *db;
	sqlite3_open("bd_kwiaciarnia.db", &db);
	sqlite3_exec(db, "SELECT * FROM zamowienia", callback, NULL, NULL);
	sqlite3_close(db);
}
void pokaz_zamowienie(string ID)
{
	sqlite3 *db;
	string pytanie = "SELECT * FROM zamowienia WHERE id = ";
	pytanie += ID;
	const char *select = pytanie.c_str();
	sqlite3_open("bd_kwiaciarnia.db", &db);
	sqlite3_exec(db, select, callback, NULL, NULL);
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
	//cout << "konto = " << konto << endl;
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
		cout << "1-stworz nowe konto" << endl << "2-zarzadzaj kwiatami" << endl << "3-zarzadzaj zamowieniami" << endl;
		cin >> wybor;
		if (wybor == 1)
		{
			admin nowy_uzytkownik = admin();
			nowy_uzytkownik.dodaj();
		}
		else if (wybor == 2)
		{
			system("cls");
			cout << "1-wyswietl wszystkie kwiaty" << endl << "2-zmien liczbe sztuk danego kwiatka" << endl << "3-dodaj nowy kwiat" << endl;
			cin >> wybor;
			if (wybor == 1)
			{
				system("cls");
				sqlite3_open("bd_kwiaciarnia.db", &db);
				sqlite3_exec(db, "SELECT * from kwiaty", callback, NULL, NULL);
				sqlite3_close(db);
				system("pause");
			}
			else if (wybor == 2)
			{
				cout << "1-pokaz wszystkie kwiaty" <<endl<< "2-nie pokazuj" << endl;
				cin >> wybor;
				if (wybor == 1)
				{
					system("cls");
					sqlite3_open("bd_kwiaciarnia.db", &db);
					sqlite3_exec(db, "SELECT * from kwiaty", callback, NULL, NULL);
					sqlite3_close(db);
				}
				admin zmien_ilosc = admin();
				zmien_ilosc.zmien();
			}
			else if (wybor == 3)
			{
				admin nowy_kwiat = admin();
				nowy_kwiat.dodaj_kwiat();
			}
		}
		else if (wybor == 3)
		{
			system("cls");
			cout << "1-wypisz wszystkie zamowienia" << endl << "2-przejdz do zatwierdzania zamowien" << endl << "3-wypisz szczegoly zamowienia o podanym id" << endl;
			cin >> wybor;
			if (wybor == 1)
			{
				pokaz_zamowienie();
				system("pause");
			}
			else if (wybor == 2)
			{
				string ID;
				system("cls");
				sqlite3_open("bd_kwiaciarnia.db", &db);
				sqlite3_exec(db, "SELECT * FROM zamowienia WHERE stan = 'nie potwierdzone'", callback, NULL, NULL);
				sqlite3_close(db);
				cout << endl << "1-zatwierdz zamowienie" << endl << "2-wyjdz z zatwierdzania zamowien" << endl;
				cin >> wybor;
				while (wybor == 1)
				{
					cout << "podaj id zamowienia ktore chcesz zatwierdzic: ";
					cin >> ID;
					string pytanie = "SELECT * FROM zamowienia WHERE stan = 'nie potwierdzone' AND id = ";
					pytanie += ID;
					const char *select = pytanie.c_str();
					system("cls");
					sqlite3_open("bd_kwiaciarnia.db", &db);
					//cout << select << endl;
					int czy_jest = sqlite3_exec(db, select, zatwierdz_callback, NULL, NULL);
					sqlite3_close(db);
					//cout << 
					if (czy_jest == 0)
					{
						cout << "nie ma takiego id zamowienia lub zamowienie jest potwierdzone" << endl;
					}
					else if (czy_jest == 4)
					{
						cout << endl;
						pytanie = "SELECT * FROM kwiaty WHERE id = ";
						pytanie += id_kwiatka;
						select = pytanie.c_str();
						sqlite3_open("bd_kwiaciarnia.db", &db);
						sqlite3_exec(db, select, kwiatek_callback, NULL, NULL);
						sqlite3_close(db);
						//cout << "kwiatow jest " << ilosc_kwiatka << endl;
						//cout << "w zamowieniu jest " << ilosc_zamowienie << endl;
						if (string_na_int(ilosc_kwiatka) < string_na_int(ilosc_zamowienie))
						{
							cout << "w magazynie nie ma wystarczajaco duzo kwiatow aby potwierdzic zamowienie" << endl;
						}
						else
						{
							int wynik = string_na_int(ilosc_kwiatka) - string_na_int(ilosc_zamowienie);
							//cout << "WYNIK = " << wynik << endl;
							int czy_zero = 0;
							char cyfra = (wynik / 1000) + 48;
							string nowa_wartosc = "";
							if (cyfra == 48) czy_zero = 1;
							else nowa_wartosc += cyfra;
							wynik = wynik - (wynik / 1000) * 1000;
							cyfra = (wynik / 100) + 48;
							if (cyfra == 48 && czy_zero == 1);
							else nowa_wartosc += cyfra;
							wynik = wynik - (wynik / 100) * 100;
							cyfra = (wynik / 10) + 48;
							wynik = wynik - (wynik / 10) * 10;
							nowa_wartosc += cyfra;
							cyfra = (wynik % 10) + 48;
							nowa_wartosc += cyfra;
							//cout << "WYNIK STRING = " << nowa_wartosc << endl;
							pytanie = "UPDATE zamowienia SET stan = 'potwierdzone' WHERE id = ";
							pytanie += ID;
							select = pytanie.c_str();
							//cout << select << endl;
							sqlite3_open("bd_kwiaciarnia.db", &db);
							sqlite3_exec(db, select, NULL, NULL, NULL);
							sqlite3_close(db);
							pytanie = "UPDATE kwiaty SET sztuk = ";
							pytanie += nowa_wartosc;
							pytanie += " WHERE id = ";
							pytanie += id_kwiatka;
							select = pytanie.c_str();
							//cout << select << endl;
							sqlite3_open("bd_kwiaciarnia.db", &db);
							sqlite3_exec(db, select, NULL, NULL, NULL);
							sqlite3_close(db);
						}
					}
					system("pause");
					system("cls");
					sqlite3_open("bd_kwiaciarnia.db", &db);
					sqlite3_exec(db, "SELECT * FROM zamowienia WHERE stan = 'nie potwierdzone'", callback, NULL, NULL);
					sqlite3_close(db);
					cout << endl << "1-zatwierdz kolejne zamowienie" << endl << "2-wyjdz z zatwierdzania zamowien" << endl;
					cin >> wybor;
				}
			}
			else if (wybor==3)
			{
				string poka_id;
				cout << "podaj id zamowienia ktore chcesz zobaczyc: ";
				cin >> poka_id;
				pokaz_zamowienie(poka_id);
				system("pause");
			}
		}
		else break;
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
		string podaj_id;
		cout << "1-zloz zamowienie" << endl << "2-wszystkie zamowienia klienta" << endl << "3-pokaz dwie statystyki odnoscnie twojego konta" << endl;
		cin >> wybor;
		//int jest_zamowienie=lista_cen.size();
		//cout << "czy zamowienie = " << jest_zamowienie << endl;
		if (wybor == 1)
		{
			cout << "1-pokaz wszystkie kwiaty" << endl << "2-nie pokazuj" << endl;
			cin >> wybor;
			if (wybor == 1)
			{
				system("cls");
				sqlite3_open("bd_kwiaciarnia.db", &db);
				sqlite3_exec(db, "SELECT * from kwiaty", callback, NULL, NULL);
				sqlite3_close(db);
			}
			cout << "podaj id kwiatu ktorego chcesz zamowic: ";
			cin >> podaj_id;
			string pytanie = "SELECT * FROM kwiaty WHERE id = ";
			pytanie += podaj_id;
			const char *select = pytanie.c_str();
			sqlite3_open("bd_kwiaciarnia.db", &db);
			int czy_jest = sqlite3_exec(db, select, cena_callback, NULL, NULL);
			sqlite3_close(db);
			while (czy_jest != 4)
			{
				cout << "nie ma takiego id kwiatka, podaj id jeszcze raz: ";
				cin >> podaj_id;
				pytanie = "SELECT * FROM kwiaty WHERE id = ";
				pytanie += podaj_id;
				select = pytanie.c_str();
				sqlite3_open("bd_kwiaciarnia.db", &db);
				czy_jest = sqlite3_exec(db, select, cena_callback, NULL, NULL);
				//cout << czy_jest << endl;
				sqlite3_close(db);
			}

			klient nowe_zamowienie = klient();
			nowe_zamowienie.dodaj(id, podaj_id, cena_kwiatka);

		}
		else if (wybor == 2)
		{
			system("cls");
			pytanie = "SELECT zamowienia.id, nazwa, sztuk_kwiatow, stan, zamowienia.cena FROM zamowienia, kwiaty WHERE kwiaty.id = zamowienia.id_kwiat AND id_klient = ";
			pytanie += id;
			select = pytanie.c_str();
			sqlite3_open("bd_kwiaciarnia.db", &db);
			sqlite3_exec(db, select, callback, NULL, NULL);
			sqlite3_close(db);
			system("pause");
		}
		else if (wybor==3)
		{
			lista_cen.clear();
			srednia = 0;
			ilosc = 0;
			system("cls");
			pytanie = "SELECT  zamowienia.cena FROM zamowienia, kwiaty WHERE kwiaty.id = zamowienia.id_kwiat AND id_klient = ";
			pytanie += id;
			select = pytanie.c_str();
			sqlite3_open("bd_kwiaciarnia.db", &db);
			sqlite3_exec(db, select, klient_srednia_callback, NULL, NULL);
			sqlite3_close(db);
			int jest_zamowienie = lista_cen.size();
			//cout << "czy zamowienie = " << jest_zamowienie << endl;
			if (jest_zamowienie > 0)
			{
				srednia = srednia / ilosc;
				cout << "srednia wydanych pieniedzy na jedne zakupy = " << srednia << endl;
				lista_cen.sort();
				//list <int> ::iterator it;
				/*for (it = lista_cen.begin(); it != lista_cen.end(); ++it)
				cout << *it << endl;*/
				int rozmiar = lista_cen.size();
				if (rozmiar % 2 == 1)
				{
					for (int i = 0; i < rozmiar / 2; i++)
					{
						lista_cen.pop_front();
					}
					cout << "mediana cen twoich zamowien wynosi: " << lista_cen.front() << endl;
				}
				else if (rozmiar % 2 == 0)
				{
					for (int i = 0; i < (rozmiar / 2) - 1; i++)
					{
						lista_cen.pop_front();
					}
					int pierwsza = lista_cen.front();
					lista_cen.pop_front();
					int druga = lista_cen.front();
					auto Lambda = [](int pierwsza, int druga)
					{
						return (pierwsza + druga) / 2;
					};
					int mediana = Lambda(pierwsza, druga);
					cout << "mediana cen twoich zamowien wynosi: " << mediana << endl;
				}
				system("pause");
			}
			else
			{
				cout << "brak zamowien u klienta" << endl;
				system("pause");
			}
			
		}
		else break;
		system("cls");
		cout << "dane zalogowanego uzytkownika:" << endl;
		sqlite3_open("bd_kwiaciarnia.db", &db);
		pytanie = "SELECT imie, nazwisko FROM konta WHERE id = ";
		pytanie += id;
		select = pytanie.c_str();
		//cout << select << endl;
		sqlite3_exec(db, select, callback, NULL, NULL);
		sqlite3_close(db);
	}
	//cout << "uprawnienia = " << uprawnienia << endl;
    return 0;
}

