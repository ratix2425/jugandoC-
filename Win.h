#ifndef windows
#define windows

#if defined(WIN32)//Metodos para Windows

#include <Windows.h>

#define LimpiarPantalla(); system("cls");//Solo funciona en Windows

#define Debug(str, ...);textColor(6);printf(str,__VA_ARGS__);textColor(7);
#define Error(str, ...);textColor(4);printf(str,__VA_ARGS__);textColor(7);
#define Notice(str, ...);textColor(2);printf(str,__VA_ARGS__);textColor(7);


//Solo WINDOWS: da posicion al curso para escribir
void gotoxy(int x, int y)
{
	HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(h,c);

}

//Solo WINDOWS: da color al texto para escribir
void textColor(int color)
{
	HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h,color);
}
#elif //Mismos Metodos para Linux

#define LimpiarPantalla();system("clear");//Para Linux
#define Debug(str, ...);
#define Error(str, ...);
#define Notice(str, ...);
void gotoxy(int x, int y)
{
	return;
}
void textColor(int color)
{
	return;
}
#endif

#endif