#include <iostream>
#include<cmath>
#include<iomanip>
#include<conio.h>
#include<windows.h>
using namespace std;

const int redova = 25, kolona = 80;

char mapa[redova][kolona];

char _lik[3][5]={" FF ",
			    "FFFF",
			    "FFFF"};

class Lik
{
public:
	int lokacijaX = redova - 4;
	int lokacijaY = 2;
};

void ClearScreen()
{
	COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void inicMape()
{
	
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 80; j++)
		{
			if (i == 0 || i == 24 || j == 79 || j==0)
				mapa[i][j] = '#';
			else
				mapa[i][j] = ' ';
			if ((i==10 || i == 20) && (j > 50 && j!=79))
				mapa[i][j] = '_';
			if ((i == 17 || i==13) && (j < 50 && j != 79 && j!=0))
				mapa[i][j] = '_';
		}
	}
}

void Crtanje()
{
	for (int i = 0; i < 25; i++)
	{
		for (size_t j = 0; j < 80; j++)
		{
			cout << mapa[i][j];
		}
		cout << endl;
	}
}

void SpawnLik(Lik lik)
{
	int k = 0, l = 0;
	for (int i = lik.lokacijaX; i < lik.lokacijaX+3; i++)
	{
		for (int j = lik.lokacijaY; j < lik.lokacijaY+4; j++)
		{
			mapa[i][j] = _lik[k][l];
			l++;
		}
		k++;
		l = 0;
	}
}



void pomjeranjeLika(Lik & lik)
{
	if (lik.lokacijaX-1 < redova - 5)
	{
		if (mapa[lik.lokacijaX + 2][lik.lokacijaY+4] == '_' ||  mapa[lik.lokacijaX + 2][lik.lokacijaY ] == '_' )
			1;
		else
			lik.lokacijaX++;
	}

	if (GetAsyncKeyState(VK_UP) != 0 && (mapa[lik.lokacijaX + 3][lik.lokacijaY] == '#' || mapa[lik.lokacijaX + 2][lik.lokacijaY] == '_' || mapa[lik.lokacijaX + 2][lik.lokacijaY + 1] != '_' || mapa[lik.lokacijaX + 2][lik.lokacijaY + 2] != '_' || mapa[lik.lokacijaX + 2][lik.lokacijaY + 3] != '_'))
	{
		if (lik.lokacijaX < redova - 5 && mapa[lik.lokacijaX + 2][lik.lokacijaY] != '_' && mapa[lik.lokacijaX + 2][lik.lokacijaY+1 ] != '_' && mapa[lik.lokacijaX + 2][lik.lokacijaY+2 ] != '_' && mapa[lik.lokacijaX + 2][lik.lokacijaY+3] != '_' && mapa[lik.lokacijaX + 2][lik.lokacijaY+4] != '_')
			return;
		lik.lokacijaX-=5;
	}
	if (GetAsyncKeyState(VK_LEFT) != 0)
	{
		if (lik.lokacijaY < 3 || mapa[lik.lokacijaX][lik.lokacijaY -1] == '_' || mapa[lik.lokacijaX + 1][lik.lokacijaY - 1] == '_')
			return;
		lik.lokacijaY-=2;
	}
	if (GetAsyncKeyState(VK_RIGHT) != 0)
	{
		if (lik.lokacijaY > kolona - 7 || mapa[lik.lokacijaX][lik.lokacijaY+5]=='_' || mapa[lik.lokacijaX+1][lik.lokacijaY + 5] == '_')
			return;
		lik.lokacijaY+=2;
	}
}




int main()
{
	Lik lik;
	srand(time(NULL));

	do
	{
		ClearScreen();

		inicMape();
		pomjeranjeLika(lik);
		SpawnLik(lik);
		Crtanje();

	} while (1);




	system("PAUSE");
	return 0;
}

