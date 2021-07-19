#include<iostream>
#include<cmath>
#include<iomanip>
#include<conio.h>
#include<windows.h>

using namespace std;

struct Enemy {
	int lokacijaX;
	int lokacijaY;
	int velicina;
};

struct Car
{
	int lokacijaX;
	int lokacijaY;
};

struct Projektil {
	int lokacijaX;
	int lokacijaY;
	int pocetnaY;
	int pocetnaX;
};

const int redovi = 25, kolone = 50;
char polje[redovi][kolone],a;
enum shoot{SPACE=0};
shoot Shoot;

char shuttle[3][6] = { ("  *  "),
					   (" *** "),
					   ("*****")

};

void AlokacijaEnemy(Enemy enemy)
{
	for (int i = enemy.lokacijaX; i < enemy.lokacijaX+enemy.velicina ; i++)
	{
		for (int j = enemy.lokacijaY; j < enemy.lokacijaY + enemy.velicina; j++)
		{
			polje[i][j] = 'O';
		}
	}
}

void AlokacijaAuta(Car car)
{
	int k = 0, l = 0;
	for (int i = car.lokacijaX; i < car.lokacijaX + 3; i++)
	{
		l = 0;
		for (int j = car.lokacijaY; j < car.lokacijaY + 5; j++)
		{
			polje[i][j] = shuttle[k][l];
			l++;
		}
		k++;
	}
}

void Alokacija()
{
	for (int i = 0; i < redovi; i++)
	{
		for (int j = 0; j < kolone; j++)
		{
			polje[i][j] = ' ';
		}
	}
}

void Draw()
{

	for (int i = 0; i < kolone+2; i++)
		cout<< "#";

	cout << endl;

	for (int i = 0; i < redovi; i++)
	{
		cout << "#";
		for (int j = 0; j < kolone; j++)
		{
				cout<< polje[i][j];
		}
		cout << "#" << endl;
	}

	for (int i = 0; i < kolone+2; i++)
		cout << "#";
}

void Kontrola(Car & car, Projektil & projektil)
{

	if (GetAsyncKeyState(VK_LEFT) != 0)
	{
		if (car.lokacijaY < 1)
			return;
		car.lokacijaY -= 2;
		projektil.lokacijaY-=2;
	}
	if (GetAsyncKeyState(VK_RIGHT) != 0)
	{
		if (car.lokacijaY+5 > kolone-1)
			return;
		car.lokacijaY+=2;
		projektil.lokacijaY+=2;
	}

}

void PomjeranjeEnemy(Enemy& enemy)
{
	enemy.lokacijaX++;
	if (enemy.lokacijaX == redovi)
	{
		enemy.lokacijaX = 0;
		enemy.lokacijaY = rand() % 40 + 5;
	}
}



void PomjeranjeProjektila(Projektil& projektil,Car car)
{
	projektil.lokacijaX -= 1;
	if (projektil.lokacijaX < 1)
	{
		projektil.lokacijaX= car.lokacijaX;
	}
}

void AlokacijaProjektila(Projektil& projektil)
{
  	polje[projektil.lokacijaX][projektil.lokacijaY] = 'M';  
}

void kolizija(Enemy &enemy)
{
	if (polje[enemy.lokacijaX + 2][enemy.lokacijaY] == 'M' || polje[enemy.lokacijaX + 2][enemy.lokacijaY + 1] == 'M' || polje[enemy.lokacijaX + 2][enemy.lokacijaY + 2] == 'M')
	{
		enemy.lokacijaX = 0;
		enemy.lokacijaY = rand() % 40 + 5;
	}

	if (polje[enemy.lokacijaX + 1][enemy.lokacijaY] == 'M' || polje[enemy.lokacijaX + 1][enemy.lokacijaY + 1] == 'M' || polje[enemy.lokacijaX + 1][enemy.lokacijaY + 2] == 'M')
	{
		enemy.lokacijaX = 0;
		enemy.lokacijaY = rand() % 40 + 5;
	}

	if (polje[enemy.lokacijaX ][enemy.lokacijaY] == 'M' || polje[enemy.lokacijaX][enemy.lokacijaY + 1] == 'M' || polje[enemy.lokacijaX][enemy.lokacijaY + 2] == 'M')
	{
		enemy.lokacijaX = 0;
		enemy.lokacijaY = rand() % 40 + 5;
	}
}



void ClearScreen()
{
	COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

int main()
{
	Car car;
	car.lokacijaX = redovi - 3;
	car.lokacijaY = kolone / 2;
	Enemy enemy;
	srand(time(0));
	enemy.lokacijaX = 0;
	enemy.lokacijaY = rand() % 40 + 5;
	enemy.velicina = 3;
	Projektil projektil;
	projektil.lokacijaX = car.lokacijaX-1;
	projektil.lokacijaY = car.lokacijaY+2;
	/*projektil.pocetnaX = car.lokacijaX - 1;
	projektil.pocetnaY = car.lokacijaY + 2;*/
	int brojac = 0;
	
	
	do
	{

		Alokacija();
		AlokacijaAuta(car);
		AlokacijaEnemy(enemy);
		if (brojac == 2)
		{
			PomjeranjeEnemy(enemy);
			brojac = 0;
		}
		AlokacijaProjektila(projektil);
		PomjeranjeProjektila(projektil, car);
		kolizija(enemy);
		Draw();
		Kontrola(car,projektil);
		ClearScreen();
		brojac++;
 
	} while (1);
	


	




	




	system("pause>0");
	return 0;
}