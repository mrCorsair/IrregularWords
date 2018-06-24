#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "const_for_settings_menu.h"
#include "datawork.h"

int options(){
	clear();
	bool enter=(false);
	int repetition=5;
	int max_word_in_cycle=15;
	unsigned i, lines, columns, choice = 0;
	//чтобы настройки сохранялись.
	FILE *sav=fopen("save.txt", "r");
	fscanf(sav,"%d%d",&repetition,&max_word_in_cycle);//
	getmaxyx(stdscr, lines, columns);
	while(enter==false){
		clear();
		for(i=0; i<4; i++){
			mvwprintw(stdscr, (lines/2)-2, (columns/2)-15, message_20);
			if(i == choice){
				mvwaddch(stdscr, (lines/2)+i, (columns)/2-15, '>');
			}
		}
		mvwprintw(stdscr, (lines/2), (columns)/2-14, settings_menu[0]);
		printw("%d",repetition);
		mvwprintw(stdscr, (lines/2)+1, (columns)/2-14, settings_menu[1]);
		printw("%d",max_word_in_cycle);
		mvwprintw(stdscr, (lines/2)+2, (columns)/2-14, settings_menu[2]);
		mvwprintw(stdscr, (lines/2)+3, (columns)/2-14, settings_menu[3]);
		// Получение пользовательского нажатия.
		switch (getch()){
			case KEY_UP:
				if(choice){ // Если возможно, переводим указатель вверх.
					choice--;
				}else choice=3;
				break;
			case KEY_DOWN:
				if(choice<3){ // Если возможно, переводим узакатель вниз.
					choice++;
				}else choice=0;
				break;
			case 10:
				enter = true;
		}
	}
	if(choice==3)return 0;
	if(choice==2){
		if(!stat_null())return 0;
	}
	clear();//ввод нового значения.
	mvwprintw(stdscr, (lines/2)-2, (columns/2)-15, message_20);
	mvwprintw(stdscr, (lines/2), (columns)/2-14, settings_menu[0]);
	if(choice==1) printw("%d",repetition);
	mvwprintw(stdscr, (lines/2)+1, (columns)/2-14, settings_menu[1]);
	mvwprintw(stdscr, (lines/2)+2, (columns)/2-14, settings_menu[2]);
	mvwprintw(stdscr, (lines/2)+3, (columns)/2-14, settings_menu[3]);
	if(choice==0){
		move((lines/2)+1, (columns/2)-11+strlen(settings_menu[1])/2);
		printw("%d",max_word_in_cycle);
		move((lines/2), (columns/2)-11+strlen(settings_menu[0])/2);
		scanw("%d",&repetition);
	}
	if(choice==1){
		move((lines/2)+1, (columns/2)-11+strlen(settings_menu[1])/2);
		scanw("%d",&max_word_in_cycle);
	} 
	FILE *sav_temp=fopen("save_temp.txt", "w");
	//сохранение нового значения
	fprintf(sav_temp,"%d %d",repetition, max_word_in_cycle);
	//освободить потоки, переименовать temp  в норм. файл
	fclose(sav);
  	fclose(sav_temp);
  	remove("save.txt");
  	rename("save_temp.txt","save.txt");
  	return 0;
}
