#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <random>
#include "deklaracje.h"
using namespace std;

//Alicja Chmielewska gr. 1A
//plansze sudoku - zrodlo: http://pl.sudokuonline.eu/

int main()
{
	bool czy_koniec_gry = 0;
	while (czy_koniec_gry == 0)
	{
		czy_koniec_gry = glowne_menu();
		system("cls");

		Pole plansza[9][9]{};
		wypelnij_1(plansza);	//wypelnia pusta plansze: liczba = -1, czy_do_zmiany = 0

		string wylosowana_nazwa_planszy = wylosuj_plansze();
		bool czy_poprawnie_przepisane = 0;
		char wybor_przepisywanie;
		while (czy_poprawnie_przepisane == 0)
		{
			if (przepisz_z_pliku(wylosowana_nazwa_planszy, plansza) != 1)		//jesli plansza nie jest poprawnie przepisana 
			{
				cout << "blad przepisywania planszy z pliku" << endl;
				cout << "jesli chcesz zakonczyc gre wpisz 'n'" << endl;
				cin >> wybor_przepisywanie;

				if (wybor_przepisywanie == 'n' || wybor_przepisywanie == 'N')
				{
					czy_poprawnie_przepisane++;
					czy_koniec_gry++;
				}
				else
				{
					cout << "nie ma takiej opcji" << endl << endl;
					Sleep(250);
				}
			}
			else		//jesli plansza jest poprawnie przepisana
				czy_poprawnie_przepisane++;
		}

		while (czy_koniec_gry == 0)
		{
			char wybor;
			wypisz_plansze(plansza);
			cout << "W - wpisz nowa liczbe do planszy" << endl;
			cout << "S - sprawdz" << endl;
			cout << "M - powrot do menu" << endl;
			cout << "Z - zakoncz gre" << endl;

			cin >> wybor;
			if (wybor == 'w' || wybor == 'W')		//wpisz nowa liczbe
				wpisz_nowa_liczbe(plansza);
			else if (wybor == 's' || wybor == 'S')
			{
				if (sprawdz(plansza) == 2)			//sprawdz
					cout << "plansza nie jest w pelni wypelniona" << endl;
				else if (sprawdz(plansza) == 1)
				{
					gratulacje();
					Sleep(250);
				}
				else
					cout << "gdzies jest blad" << endl;
				Sleep(250);
			}
			else if (wybor == 'z' || wybor == 'Z')	//zakoncz gre
				czy_koniec_gry = 1;
			else if (wybor == 'm' || wybor == 'M')	//powrot do menu
			{
				system("cls");
				break;
			}
			else
				cout << "nie ma takiej opcji" << endl;
			Sleep(250);
			system("cls");
		}
	}
}
