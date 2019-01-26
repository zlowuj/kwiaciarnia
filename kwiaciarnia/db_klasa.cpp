#include "stdafx.h"
#include "db_klasa.h"


db_klasa::db_klasa()
{
	if (SQLITE_OK != (ret = sqlite3_open("bd_kwiaciarnia.db", &db)))
	{
		cout << "nie udalo sie wczytac bazy danych";
	}
}


db_klasa::~db_klasa()
{
}
