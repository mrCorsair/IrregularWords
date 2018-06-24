#include <ncurses.h>
#include <string.h>
#include <locale.h>

#include "const_for_main_menu.h"
#include "exercise.h"
#include "print_functions.h"
#include "settings.h"

int hello();

int main()
{
	setlocale( 0, "" );
	initscr();
	unsigned lines, columns;

	getmaxyx(stdscr, lines, columns); // Записываем максимальное кол-во строк и столбцов в переменные.
	mvwprintw(stdscr, (lines/2)-4, (columns-strlen(message_00)/2)/2, message_00); // Вывод message_00-02.
	mvwprintw(stdscr, (lines/2)-2, (columns-strlen(message_01)/2)/2, message_01);
	mvwprintw(stdscr, (lines/2)-0, (columns-strlen(message_02)/2)/2, message_02);
	getch();
	while(true){
		switch(hello()){
			case 0:play();break;
			case 1:chow_dictonary();break;
			case 2:options();break;
			case 3:endwin();return 0;
		}
	}
	endwin();
}

int hello(){
	bool enter=false;
	unsigned i, lines, columns, choice = 0;
	getmaxyx(stdscr, lines, columns); // Записываем максимальное кол-во строк и столбцов в переменные.
	curs_set(0); // Выключение курсора.
	keypad(stdscr, true); // Подключение функциональных клавишь.
	while(enter==false){
		clear();
		for(i=0; i<4; i++){
			mvwprintw(stdscr, (lines/2)-2, (columns/2)-15, message_10);
			if(i == choice){
				mvwaddch(stdscr, (lines/2)+i, (columns)/2-15, '>');
			}
			mvwprintw(stdscr, (lines/2)+i, (columns)/2-14, menu[i]);
		}
		// Получение пользовательского нажатия.
		switch (getch()){
			case KEY_UP:
				if (choice) { // Если возиожно, переводим указатель вверх.
					choice--;
				}
				else choice=3;
				break;
			case KEY_DOWN:
				if (choice<3) { // Если возможно, переводим узакатель вниз.
					choice++;
				}
				else choice=0;
				break;
			case '\n':
				enter = true;
		}
	}
	return choice;
}
