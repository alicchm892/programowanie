#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <random>
#include "deklaracje.h"
using namespace std;

void wypelnij_1(Pole plansza[9][9])		//wypelnienie pustej planszy liczba -1 (by pozniej moc sprawdzic czy wszystkie komorki zostaly uzupelnione przy przepisywaniu)
{
	for (int i = 0; i < 9; i++)	
	{
		for (int j = 0; j < 9; j++)
		{
			plansza[i][j].liczba = -1;
			plansza[i][j].czy_do_zmiany = 0;
		}
	}
}

string wylosuj_plansze()		//losowanie planszy z osmiu dostepnych plikow
{
	random_device device;
	mt19937 generator(device());
	uniform_int_distribution<int> ktora_plansza(1, 8);

	int nr_planszy = ktora_plansza(generator);
	switch (nr_planszy)
	{
	case 1:
		return "1.txt";
		break;
	case 2:
		return "2.txt";
		break;
	case 3:
		return "3.txt";
		break;
	case 4:
		return "4.txt";
		break;
	case 5:
		return "5.txt";
		break;
	case 6:
		return "6.txt";
		break;
	case 7:
		return "7.txt";
		break;
	case 8:
		return "8.txt";
		break;
	}
}

bool przepisz_z_pliku(string nazwa_pliku, Pole plansza[9][9])
{
	ifstream plik(nazwa_pliku);
	char pobierany_znak;
	Pole *wskaznik_na_plansze = &plansza[0][0];
	int i{};

	if (plik.is_open())
	{
		while (!plik.eof() && i < 81)			//przepisywnie cyfr z pliku do planszy - dopoki nie skonczy sie tekst w pliku lub nie zapelni sie cala tablica
		{
			plik.get(pobierany_znak);
			if (pobierany_znak >= '0' && pobierany_znak <= '9')		//zalozenie ze przepisywane beda jedynie cyfry od 0 do 9
			{
				if (pobierany_znak != '0')			//jesli cyfra jest rozna od 0 to uzytkownik nie moze jej zmienic podczas gry
					(wskaznik_na_plansze + i)->czy_do_zmiany = 0;
				else								//jesli cyfra jest rowna 0 to uzytkownik  moze ja podczas gry zmienic
					(wskaznik_na_plansze + i)->czy_do_zmiany = 1;

				(wskaznik_na_plansze + i)->liczba = pobierany_znak - 48;	//wpisanie cyfry do planszy z uwzglednieniem zamiany char -> int
				i++;
			}
		}

		for (int i = 0; i < 9; i++)		//sprawdzenie czy cala plansza jest wypelniona liczbami od 0 do 9
		{
			for (int j = 0; j < 9; j++)
			{
				if (plansza[i][j].liczba == -1)	//jesli ktoras z komorek jest wypelniona liczba -1, to plansza nie zostala poprawnie przepisana
				{
					plik.close();
					return 0;
				}
			}
		}
	}
	else
		cout << "nie mozna otworzyc pliku" << endl;
	plik.close();
	return 1;	
}

void wypisz_plansze(Pole plansza[9][9])
{
	HANDLE kolor_znakow;
	kolor_znakow = GetStdHandle(STD_OUTPUT_HANDLE);

	int nr_wiersza = 0;
	for (int i = 1; i < 21; i++)
	{
		if (i == 20)
		{
			cout << "   1  2  3     4  5  6     7  8  9   " << endl;
		}
		else if (i % 2 == 0) //wypisanie rzedu cyfr
		{
			for (int j = 0; j < 9; j++)
			{
				if (j == 0)
					cout << (char)0xBA;		// ║

				if (plansza[nr_wiersza][j].liczba != 0)			//jesli cyfra jest rozna od zera to ja wypisz
				{
					if (plansza[nr_wiersza][j].czy_do_zmiany == 0)		//zmiana kolorow cyfr ktorych uzytkownik nie moze zmienic
					{
						SetConsoleTextAttribute(kolor_znakow, 9);		
						cout.width(3);
						cout << plansza[nr_wiersza][j].liczba;
						SetConsoleTextAttribute(kolor_znakow, 15);
					}
					else		//wypisanie cyfr ktore gracz moze zmieniac
					{
						cout.width(3);
						cout << plansza[nr_wiersza][j].liczba;
					}
				}
				else		//jesli cyfra jest rowna 0 to jej nie wypisuj
				{
					cout.width(3);
					cout << " ";
				}

				if (j == 2 || j == 5 || j == 8)
					cout << "  " << (char)0xBA;
			}
			cout << "  [" << (nr_wiersza + 1) << "]";
			nr_wiersza++;
		}
		else if (i == 1)
		{
			cout << (char)0xC9;				// ╔
			for (int k = 0; k < 35; k++)
			{
				if (k == 11 || k == 23)
					cout << (char)0xCB;		// ╦
				else
					cout << (char)0xCD;		// ═
			}
			cout << (char)0xBB;				// ╗
		}
		else if (i == 7 || i == 13)
		{
			cout << (char)0xCC;				// ╠
			for (int k = 0; k < 35; k++)
			{
				if (k == 11 || k == 23)
					cout << (char)0xCE;		// ╬
				else
					cout << (char)0xCD;		// ═
			}
			cout << (char)0xB9;				// ╣
		}
		else if (i == 19)
		{
			cout << (char)0xC8;				// ╚
			for (int k = 0; k < 35; k++)
			{
				if (k == 11 || k == 23)
					cout << (char)0xCA;		// ╩
				else
					cout << (char)0xCD;		// ═
			}
			cout << (char)0xBC;				// ╝
		}
		else
		{
			cout << (char)0xBA << "           " << (char)0xBA << "           " << (char)0xBA << "           " << (char)0xBA;
		}
		cout << endl;
	}
}

void wpisz_nowa_liczbe(Pole plansza[9][9])
{
	int wiersz, kolumna;
	bool czy_poprawna_komorka = 0;
	cout << "podaj komorke do ktorej chcesz wpisac liczbe: " << endl;

	while (czy_poprawna_komorka == 0)
	{
		cout << "kolumna: ";		//pobranie od gracza wspolrzednych komorki
		cin >> kolumna;
		cout << "wiersz: ";
		cin >> wiersz;
	
		if (kolumna > 0 && kolumna < 10 && wiersz > 0 && wiersz < 10)		//sprawdzenie czy wspolrzedne sa prawidlowe
		{
			if (plansza[wiersz-1][kolumna-1].czy_do_zmiany == 0)		//jesli gracz nie moze zmienic zawartosci komorki
			{
				cout << "tej liczby zmienic nie mozesz" << endl;
				cout << "wybierz inna komorke" << endl;
			}
			else			//jesli gracz moze zmienic zawartosc komorki
			{
				int wpisywana_liczba;
				cout << "podaj liczbe ktora chcesz wpisac do tej komorki: ";
				cin >> wpisywana_liczba;
				plansza[wiersz-1][kolumna-1].liczba = wpisywana_liczba;
				czy_poprawna_komorka = 1;
			}
		}

	}
}

int sprawdz(Pole plansza[9][9])	//0 jesli blad, 1 jesli poprawnie, 2 jesli nie jest w pelni wypelniona
{
	for (int i = 0; i < 9; i++)		//sprawdzanie czy jest w pelni wypelniona
	{
		for (int j = 0; j < 9; j++)
		{
			if (plansza[i][j].liczba == 0)
				return 2;
		}
	}
	for (int i = 0; i < 9; i++)		//sprawdzanie rzedami
	{
		for (int j = 0; j < 9; j++)
		{
			int sprawdzana_liczba = plansza[i][j].liczba;
			for (int k = j + 1; k < 9; k++)
			{
				if (plansza[i][j].liczba == plansza[i][k].liczba)	//jesli liczba sie powtarza
					return 0;
			}
		}
	}
	for (int i = 0; i < 9; i++)		//sprazwdzanie kolumnami
	{
		for (int j = 0; j < 9; j++)
		{
			int sprawdzana_liczba = plansza[i][j].liczba;
			for (int k = j + 1; k < 9; k++)
			{
				if (plansza[j][i].liczba == plansza[k][i].liczba)	//jesli liczba sie powtarza
					return 0;
			}
		}
	}
	for (int i = 1; i <= 9; i++)	//sprawdzanie kwadratami 3x3
	{
		if (i % 3 == 1)
		{
			for (int j = 1; j <= 9; j++)
			{
				if (j % 3 == 1)
				{
					//sprawdzanie komorek 3x3
					for (int k = 1; k <= 9; k++)
					{
						int sprawdzana_liczba = k;
						int ile_powtorzen = 0;
						for (int m = 0; m < 3; m++)
						{
							for (int n = 0; n < 3; n++)
							{
								if (plansza[m + i - 1][n + j - 1].liczba == sprawdzana_liczba)
									ile_powtorzen++;
							}
						}
						if (ile_powtorzen > 1)
							return 0;	//jesli liczba sie powtarza
					}
				}
			}
		}
	}
	return 1;		//jesli liczby sie nie powtarzaja
}

bool glowne_menu()
{
	while (true)
	{
		cout << " _____  _   _   ____    _____   _   __  _   _ " << endl;
		cout << "|  __| | | | | |    \\  |  _  | | | / / | | | |" << endl;
		cout << "| |__  | | | | | |\\  | | | | | | |/ /  | | | |" << endl;
		cout << "|__  | | | | | | | | | | | | | |   <   | | | |" << endl;
		cout << " __| | | |_| | | |/  | | |_| | | |\\ \\  | |_| |" << endl;
		cout << "|____| |_____| |____/  |_____| |_| \\_\\ |_____|" << endl;
		cout << endl;

		char wybor_menu;
		cout.width(34);
		cout << "1. jak grac zeby wygrac?" << endl;
		cout.width(27);
		cout << "2. nowa gra" << endl;
		cout.width(28);
		cout << "3. zakoncz gre" << endl;
		cout << endl;
		cout << "co wybierasz? wpisz cyfre: ";
		cin >> wybor_menu;

		if (wybor_menu == '1')	//wypisanie instrukcji
		{
			system("cls");
			
			cout << "INSTRUKCJA GRY: " << endl;
			cout << endl;
			cout << "Musisz wypelnic wszystkie komorki cyframi od 0 do 9, tak by:" << endl;
			cout << "1. W kazdym wierszu kazda cyfra wystepowala tylko raz" << endl;
			cout << "2. W kazdej kolumnie kazda cyfra wystepowala tylko raz" << endl;
			cout << "3. W kazdym kwadracie 3x3 kazda cyfra wystepowala tylko raz" << endl;
			cout << endl;
			cout << "Nie musisz zgadywac, wystarczy logiczne myslenie!" << endl;
			cout << endl;
			cout << "WSKAZOWKA: \nJesli po wybraniu numeru komorki i numeru wiersza stwierdzisz, \nze jednak nie chcesz do tej komorki wpisywac zadnej cyfry, wpisz cyfre 0" << endl;
			cout << endl;
			system("pause");
		}
		else if (wybor_menu == '2')		//nowa gra (czy_koniec_gry = 0)
			return 0;
		else if (wybor_menu == '3')		//koniec gry (czy_koniec_gry = 1)
			return 1;
		else
		{
			cout << "nie ma takiej opcji" << endl;
			Sleep(550);
		}
		system("cls");
	}
	return 0;
}

void gratulacje()
{
	cout << "  _____   _____     ____   ________                     ____      _____   ______    ______   " << endl;
	cout << " /       |     \\   /    \\     |     |      |  |        /    \\    /              |  |         " << endl;
	cout << "|  ___   |   ___| |______|    |     |      |  |       |______|  |               |  |____     " << endl;
	cout << "|     |  |   \\    |      |    |     |      |  |       |      |  |               |  |         " << endl;
	cout << " \\____|  |    \\   |      |    |      \\____/   |_____  |      |   \\_____   |____/   |______   " << endl;
}
