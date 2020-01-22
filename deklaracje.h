#pragma once
using namespace std;

struct Pole 
{
	int liczba;
	bool czy_do_zmiany;
};

string wylosuj_plansze();
bool przepisz_z_pliku(string nazwa_pliku, Pole plansza[9][9]);
void wypelnij_1(Pole plansza[9][9]);
void wypisz_plansze(Pole plansza[9][9]);
void wpisz_nowa_liczbe(Pole plansza[9][9]);
int sprawdz(Pole plansza[9][9]);
bool glowne_menu();
void gratulacje();
