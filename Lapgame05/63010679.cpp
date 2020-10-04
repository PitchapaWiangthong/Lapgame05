#include<stdio.h>
#include<conio.h>
#include<windows.h>

#define bullet_count 5

void draw_ship(int, int);
void erase_ship(int, int);
void gotoxy(int, int);
void setcursor(bool);
void setcolor(int, int);
void draw_bullet(int, int);
void erase_bullet(int, int);


int main()
{
	char ch = '.';
	char direction = 's';
	int x = 38, y = 20,bx[bullet_count],by[bullet_count];
	bool state[bullet_count] = {0};
	setcursor(0);
	gotoxy(x,y);
	draw_ship(x,y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a')	{direction = 'l';}
			if (ch == 'd')	{direction = 'r';}
			if (ch == 's')	{direction = 's';}
			if (ch == ' ') {
				for (int i = 0; i < bullet_count; i++)
				{
					if (state[i] == 0)
					{
						state[i] = 1;
						bx[i] = x + 2;
						by[i] = y - 1;
						break;
					}
				}
			}
			fflush(stdin);
		}
		if (direction == 'l' && x != 0) { erase_ship(x, y); draw_ship(--x, y); }
		if (direction == 'r' && x <= 80) { erase_ship(x, y); draw_ship(++x, y); }
		if (direction == 's') { erase_ship(x, y); draw_ship(x, y); }
		for (int i = 0; i < bullet_count; i++)
		{
			if (state[i] == 1)
			{
				erase_bullet(bx[i], by[i]);
				if (by[i] > 0)
				{
					draw_bullet(bx[i], --by[i]);
				}
				else
				{
					state[i] = 0;
				}
			}
		}
		Sleep(100);
	} while (ch != 'p');
	return 0;
}





void draw_ship(int x,int y)
{	
	gotoxy(x,y);
	setcolor(2, 4);
	printf("<-0->");
}

void erase_ship(int x,int y)
{
	gotoxy(x,y);
	setcolor(2, 0);
	printf("       ");
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_bullet(int x, int y)
{	
	gotoxy(x, y);
	setcolor(4, 4);
	printf(" ");
}
void erase_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}