#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h> 

#include "datawork.h"

void chow_dictonary(){
	clear();
	words *temp;
	unsigned i,j, lines, columns;
	bool enter=(false);
	temp=(words*)malloc(sizeof(words));
	temp->eng[0]=(char*)malloc(50*sizeof(char));
	temp->eng[1]=(char*)malloc(50*sizeof(char));
	temp->eng[2]=(char*)malloc(50*sizeof(char));
	temp->rus=(char*)malloc(50*sizeof(char));

	getmaxyx(stdscr, lines, columns);
	FILE *dict=fopen("dictionary.txt", "r");
	FILE *sav=fopen("save.txt", "r");
	int must;
	fscanf(sav,"%d",&must);
	fclose(sav);
	long max=count_string(dict);
	j=1;
	while(enter==false){
		clear();
		getmaxyx(stdscr, lines, columns);
		lines--;
		mvwprintw(stdscr, 0, 1, "+/-/V");
		mvwprintw(stdscr, 0, 13, "Первая форма");//12+1
		mvwprintw(stdscr, 0, (columns-21)/3+7, "Вторая форма");
		mvwprintw(stdscr, 0, 2*(columns-21)/3+7, "Третья форма");
		mvwprintw(stdscr, 0, columns-18, "Перевод");//7+1
		seek_str(dict,j);
		for(i=1;i<lines;i++){
			fscanf(dict,"%d%d%s%s%s%s%d",&(temp->p),&(temp->n),temp->eng[0],temp->eng[1],temp->eng[2],temp->rus,&(temp->sp));
			if((temp->p)==(temp->n)&&(temp->n)==0){
				mvwprintw(stdscr, i, 1, "-");
			}else{
					//float prozent=(float)(temp->p)/(temp->n)*100;
					mvwprintw(stdscr, i, 1, "%d/%d", temp->p, temp->n);
					if(temp->sp>=must)printw("/V");
				}
			mvwprintw(stdscr, i, 13, temp->eng[0]);
			mvwprintw(stdscr, i, ((columns-21)/3+7), temp->eng[1]);
			mvwprintw(stdscr, i, (2*(columns-21)/3+7), temp->eng[2]);
			mvwprintw(stdscr, i, columns-18, temp->rus);
			if((j+i)==max+1)break;
		}
		mvwprintw(stdscr, lines, 3, "'стрелка вверх/вниз' - навигация, enter(ввод) - выход в меню");//12+1
		switch (getch()){
			case KEY_UP:
				if(j>1){ // Если возиожно, переводим указатель вверх.
					j=j-lines+1;
					if(j<1)j=1;
				}
				break;
			case KEY_DOWN:
				if(j<max){ // Если возможно, переводим узакатель вниз.
					if((j+lines-1)>=max)break;
					j=j+lines-1;
				}
				else j=1;
				break;
			case '\n':
				enter = true;
		}
	}
}
