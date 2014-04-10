// hid_con.cpp : Defines the entry point for the console application.
/*
//#include "stdafx.h"
#include "hid.h"
#include <iostream>
//bibliioteki do gry 
#include <Windows.h>
#include <conio.h>
#include <vector>
//biblioteka time - do losowania
#include <ctime>
//end
using namespace std;


//GRA
//stale typu int
int const MAP_X = 20;
int const MAP_Y = 30;
//struktura punktu 2D
struct Position2D
{
	int x;
	int y;
};
//Klasa Gry
class Game
{
	//zmienna move
	int short move;;
public:
		{
		//strtowa pozycja gracza
		player.x = 10;
		player.y = 20;
		//poczatkowy movement klienta :D
		move = 1;
	}


	//przesuwanie gracza
	

	//Zwrocenie pozycji gracza
	Position2D& return_ref_to_player() 
	{
		return player;
	}
};

class Map
{
	//mapa gry
	int map[MAP_X][MAP_Y];
public:
	//konstruktor
	Map()
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				map[i][j] = 0;
			}
		}
	}
	//Rysowanie mapy:

	

	//umieszczenie playera na mapie
	void put_player(Position2D& player)
	{
		map[player.x][player.y] = 2;
	}
	//umieszczenie potworkow na mapie
	
//END Implementacja GRA

int _tmain(int argc, _TCHAR* argv[])
{
	srand (time(NULL));
	//Utworzenie do gry obiektow MAP i GAME
	Map  m;
	Game g;
	//start gry
	//g.start();

	//zerowanie buforow wejscia i wyjscia STM
	
	//buffer_out[1]=1;// pomaranczowa dioda
	//buffer_out[1]=2;// zielona dioda
	//buffer_out[1]=4;// czerwona dioda
	//buffer_out[1]=8;// niebieska dioda

//	FindTheHID();
//	WriteOutputReport(buffer_out);
//	while (1){
//		ReadInputReport(buffer_in);
//		DisplayInputReport(buffer_in);
//		Sleep(1000);
//	}
//	system("pause");
	

	//petla gry...
	FindTheHID();
	while (g.fail_check())
	{
		m.reset();
		m.put_player(g.return_ref_to_player());
		m.put_monster(g.return_ref_to_monster());
		m.draw();
		g.monster_ai();
		
		g.move_player(buffer_in);
		Sleep(100);
		g.score_up();
		system("cls");
	}
	cout << endl;
	int zmienna = 0;
	for (int i = 0; i < 50; i++)
	{
		buffer_out[1] = rand()%15 + 1;
		WriteOutputReport(buffer_out);
		Sleep(500);
	}
	Sleep(1000);
	for(int i = 0; i < 5; i++)
	{
		buffer_out[1] = 0;
		WriteOutputReport(buffer_out);
	}
	cout << "Wyslalem!" << endl;
	system("pause");
	return 0;
}

*/