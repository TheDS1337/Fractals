#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

class Cplex
{
public:
	float x, y;

	Cplex()
	{
		x = 0.0;
		y = 0.0;
	}

	Cplex(float rel, float img)
	{
		x = rel;
		y = img;
	}

	Cplex conjugate()
	{
		return Cplex(x, -y);
	}

	float norm()
	{
		return pow(x, 2) + pow(y, 2);
	}

	Cplex operator+ (const Cplex& other)
	{
		return Cplex(x + other.x, y + other.y);
	}

	Cplex operator* (const Cplex& other)
	{
		return Cplex(x * other.x - y * other.y, x * other.y + y * other.x);
	}

	Cplex operator* (float scaler)
	{
		return Cplex(scaler * x, scaler * y);
	}
};

class MandelbrotElement: public Cplex
{
public:
	bool outside;
	
	MandelbrotElement()
	{
		x = 0.0;
		y = 0.0;
		outside = false;
	}

	MandelbrotElement(float rel, float img)
	{
		x = rel;
		y = img;
		outside = false;
		
		DoesPointConverge();
	}

private:

	void DoesPointConverge()
	{
		Cplex z(x, y);		

		for( auto i = 0; i < 100; i++ )
		{
			if( z.norm() >= 4.0f )
			{
				outside = true;
				break;
			}

			z = z * z + Cplex(x, y);
		}
/*
		if( outside )
		{
			cout << x << ' ' << y << " is outside." << endl;
		}
		else
		{
			cout << x << ' ' << y << " is inside." << endl;
		}*/
	}
};


BOOL SetConsoleXY(short x, short y)
{
	COORD coord = {x, y};
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GetConsoleSize(int& width, int& height)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
