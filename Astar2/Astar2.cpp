#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	ifstream plik;
	plik.open("grid.txt");
	int LZ[20][20];
	int LO[20][20];
	int R[20][20];		//rodzice
	int M[20][20];		//grid
	double F[20][20];
	int G[20][20];
	double H[20][20];
	int x = 0; //aktualne wspó³rzêdne
	int y = 0; //
	int trasa[20][20];
	int policz3 = 0;
	int help = 0;
	double tempF = 2000;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i<20; i++) //wypelnianie tablic zerami
		for (int j = 0; j<20; j++)
		{
			LZ[i][j] = 0;
			LO[i][j] = 0;
			R[i][j] = 0;
			M[i][j] = 0;
			G[i][j] = 0;
			H[i][j] = 0;
			F[i][j] = 0;
			plik >> M[i][j];
		}
	// rodzice
	// prawo,  dó³,   lewo,	  góra
	//	1		2		3		4
	//kolejnosc: prawo, dol, lewo, góra
	while ((x <= 19) && (y <= 19))
	{
		LZ[x][y] = 1;
		F[x][y] = 0;
		LO[x][y] = 0;
		if ((M[x][y + 1] != 5) && (y + 1 <20))	//jezeli z prawej nie ma przeszkody i nie konczy sie mapa
		{
			if (LZ[x][y + 1] == 0)		//jezeli pkt po prawej nie znajduje sie na LZ
			{
				LO[x][y + 1] = 1;			//to dodaj do LO
				if (G[x][y + 1]==0)			//jesli nie ma obliczonego G
					G[x][y + 1]=G[x][y]+1;	//oblicza G
				if (R[x][y + 1] == 0)		// jezeli nie ma ustawionego R
					R[x][y + 1] = 3;		// ustawia R na 3
			}
				
			H[x][y + 1] = sqrt(pow((x - 19), 2) + pow((y + 1 - 19), 2)); //obliczanie heurystyki dla pkt z prawej
			if (LO[x][y+1] == 1) //je¿eli pkt z prawej dodany do LO
				F[x][y + 1] = G[x][y + 1] + H[x][y + 1]; //oblicz F
		}
		if ((M[x + 1][y] != 5) && (x + 1<20)) //jezeli z do³u nie ma przeszkody i nie konczy sie mapa
		{
			if (LZ[x + 1][y] == 0)
			{
				LO[x + 1][y] = 1;
				if (G[x + 1][y] == 0)
					G[x + 1][y]=G[x][y] + 1;
				if (R[x + 1][y] == 0)
					R[x + 1][y] = 4;
			}
			H[x + 1][y] = sqrt(pow((x + 1 - 19), 2) + pow((y - 19), 2));
			if (LO[x + 1][y] == 1)
				F[x + 1][y] = G[x + 1][y] + H[x + 1][y];
		}
		if ((M[x][y - 1] != 5) && (y - 1 > -1))
		{
			if (LZ[x][y - 1] == 0)
			{
				LO[x][y - 1] = 1;
				if (G[x][y - 1] == 0)
					G[x][y - 1]= G[x][y] + 1;
				if (R[x][y-1] == 0)
					R[x][y-1] = 1;
			}
				
			H[x][y - 1] = sqrt(pow((x - 19), 2) + pow((y - 1 - 19), 2));
			if (LO[x][y-1] == 1)
				F[x][y - 1] = G[x][y - 1] + H[x][y - 1];
		}
		if ((M[x - 1][y] != 5) && (x - 1 > -1))
		{
			if (LZ[x - 1][y] == 0)
			{
				LO[x - 1][y] = 1;
				if (G[x-1][y] == 0)
					G[x - 1][y]= G[x][y] + 1;
				if (R[x - 1][y] == 0)
					R[x - 1][y] = 2;
			}
				
			H[x - 1][y] = sqrt(pow((x - 1 - 19), 2) + pow((y - 19), 2));
			if (LO[x-1][y]==1)
				F[x - 1][y] = G[x - 1][y] + H[x - 1][y];
		}

		tempF = 2000;
		for (int i = 0; i < 20; i++) //szukanie najmniejszego F
		{
			for (int j = 0; j < 20; j++)
			{
				if ((LO[i][j] == 1) && (F[i][j] < tempF))
				{
					tempF = F[i][j];
					x = i;
					y = j;
				}
			}
		}
		if ((x != 19) || (y != 19)) //za kazdym razem gdy x lub y nie jest 19 to zwiêksza siê help, je¿eli bêdzie w kó³ko kr¹¿yæ algorytm to znaczy, ¿e nie znalaz³ trasy (nie osi¹gn¹³ celu) i help przekroczy kiedys wartoœæ 1000.
			help++;

		if (help > 1000)  //wyswietlanie gdy nie znajdzie trasy
		{
			for (int i = 0; i<20; i++) 
			{
				for (int j = 0; j < 20; j++)
				{
					if (M[i][j] == 5)
					{
						SetConsoleTextAttribute(hOut, FOREGROUND_RED);
						cout << M[i][j] << "  ";
					}
					if (M[i][j] == 0)
					{
						SetConsoleTextAttribute(hOut, 15);
						cout << M[i][j] << "  ";
					}
					SetConsoleTextAttribute(hOut, 15);
				}
				cout << "\n";
			}
			cout << "Liczba krokow: " << policz3 << endl;
			cout << "Nie znaleziono trasy!" << endl;
			break;
		}
			
		if (R[19][19] != 0)
		{
			break;
		}
	}

	for (int i = 19; i >= 0;) //tworzenie trasy
	{
		if (M[0][0] == 3)
			break;
		for (int j = 19; j >= 0;)
		{
			if (R[i][j] == 3)
			{
				M[i][j] = 3;
				M[i][j - 1] = 3;
				j--;
			}
			if (R[i][j] == 4)
			{
				M[i][j] = 3;
				M[i - 1][j] = 3;
				i--;
			}
			if (R[i][j] == 1)
			{
				M[i][j] = 3;
				M[i][j + 1] = 3;
				j++;
			}
			if (R[i][j] == 2)
			{
				M[i][j] = 3;
				M[i + 1][j] = 3;
				i++;
			}
			if (M[0][0] == 3)
				break;
		}
	}
		for (int i = 0; i<20; i++) //wyswietlanie mapy z tras¹
		{
			for (int j = 0; j < 20; j++)
			{
				if (M[i][j] == 3)
					policz3++;
				if (M[i][j] == 3)
				{
					SetConsoleTextAttribute( hOut, FOREGROUND_BLUE|BACKGROUND_GREEN);
					cout << M[i][j] << "  ";
				}
				if (M[i][j] == 5)
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << M[i][j] << "  ";
				}
				if (M[i][j] == 0)
				{
					SetConsoleTextAttribute(hOut, 15);
					cout << M[i][j] << "  ";
				}
				SetConsoleTextAttribute(hOut, 15);
			}
			cout << "\n";
		}
		cout << "Liczba krokow: " << policz3 << endl;
	system("pause");
	return 0;
}



