#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
using namespace std;
class db_klasa
{
private:
	int sprawdz(string dana)
	{
		int x, y = 0;
		for (int i = 0; i<dana.length(); i++)
		{
			x = dana[i] - 48;
			if (x > 9 || x<0) y = 1;
			//if (dana.length() == 11) y = 1;
		}
		return y;
	}
public:
	int ret, czy_liczba;
	sqlite3 *db;
	db_klasa();
	~db_klasa();
	void dodaj(string elem[], int length)
	{
		string dodaj = "INSERT INTO ";
		dodaj += elem[0];
		dodaj += " (";
		for (int i = 1; i < length / 2; i++)
		{
			dodaj += elem[i];
			dodaj += ", ";
		}
		dodaj += elem[length / 2];
		dodaj += ") VALUES (";
		for (int i = length / 2 + 1; i < length - 1; i++)
		{
			czy_liczba = this->sprawdz(elem[i]);
			if (czy_liczba == 0)
			{
				dodaj += elem[i];
				dodaj += ", ";
			}
			else
			{
				dodaj += "'";
				dodaj += elem[i];
				dodaj += "', ";
			}
		}
		czy_liczba = this->sprawdz(elem[length - 1]);
		if (czy_liczba == 0)
		{
			dodaj += elem[length - 1];
			dodaj += ");";
		}
		else
		{
			dodaj += "'";
			dodaj += elem[length - 1];
			dodaj += "');";
		}
		cout << dodaj << endl;
		//system("pause");
		sqlite3_stmt *insertStmt;
		sqlite3_prepare(this->db, dodaj.c_str(), -1, &insertStmt, NULL);
		//int cos=
		sqlite3_step(insertStmt);
		sqlite3_errmsg(db);
		/*if (cos == 1)
		{
		cout << "istnieje jedna lub wiecej komorek z taka sama unikalna dana(sprawdz czy nie powtorzona zostala komorka specjalizacja, PESEL)!" << endl;
		}
		cout << "cos wynosi: " << cos << endl;*/

		system("pause");
	}
	void aktualizuj(string elem[], int length, string ID)
	{
		string dodaj = "UPDATE ";
		dodaj += elem[0];
		dodaj += " SET ";
		for (int i = 1; i < length / 2; i++)
		{
			dodaj += elem[i];
			dodaj += " = ";
			czy_liczba = this->sprawdz(elem[i + (length / 2)]);
			if (czy_liczba == 0)
			{
				dodaj += elem[i + (length / 2)];
				dodaj += ", ";
			}
			else
			{
				dodaj += "'";
				dodaj += elem[i + (length / 2)];
				dodaj += "', ";
			}
		}
		dodaj += elem[length / 2];
		dodaj += " = ";
		czy_liczba = this->sprawdz(elem[length - 1]);
		if (czy_liczba == 0)
		{
			dodaj += elem[length - 1];
			dodaj += " WHERE ID = ";
			dodaj += ID;
			dodaj += ";";
		}
		else
		{
			dodaj += "'";
			dodaj += elem[length - 1];
			dodaj += "' WHERE ID =  ";
			dodaj += ID;
			dodaj += ";";
		}
		cout << dodaj;
		system("pause");
		sqlite3_stmt *insertStmt;
		sqlite3_prepare(this->db, dodaj.c_str(), dodaj.size(), &insertStmt, NULL);
		sqlite3_step(insertStmt);
	}
	void usun(string tablica, string ID)
	{
		string dodaj = "DELETE FROM ";
		dodaj += tablica;
		dodaj += " WHERE id = ";
		dodaj += ID;
		dodaj += ";";
		cout << dodaj << endl;
		system("pause");
		sqlite3_stmt *insertStmt;
		sqlite3_prepare(this->db, dodaj.c_str(), dodaj.size(), &insertStmt, NULL);
		sqlite3_step(insertStmt);
	}

};

