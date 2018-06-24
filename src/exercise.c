#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h> 
#include "datawork.h"

int play(){
	//int ch;
	clear();
	words *temp;
	FILE *dict=fopen("dictionary.txt", "r");
	FILE *sav=fopen("save.txt", "r");
	if(!dict)return -5;
	if(!sav)return -5;
	unsigned i,l, lines, columns, repetition, max_word_in_cycle, max=count_string(dict);
	temp=(words*)malloc(sizeof(words));
	temp->eng[0]=(char*)malloc(50*sizeof(char));
	temp->eng[1]=(char*)malloc(50*sizeof(char));
	temp->eng[2]=(char*)malloc(50*sizeof(char));
	temp->rus=(char*)malloc(50*sizeof(char));
	if(!(temp->eng[0])||!(temp->eng[1])||!(temp->eng[2])||!(temp->rus)){
		printf("ошибка выделения памяти TEMP\n");
		return -3;
	}
	
	getmaxyx(stdscr, lines, columns);
	words all_dict[max];
	for(i=0;i<max;i++){
		fscanf(dict,"%d%d%s%s%s%s%d",&(temp->p),&(temp->n),temp->eng[0],temp->eng[1],temp->eng[2],temp->rus,&(temp->sp));
		all_dict[i].p=temp->p;
		all_dict[i].n=temp->n;
		all_dict[i].sp=temp->sp;
		all_dict[i].eng[0]=(char*)malloc(strlen(temp->eng[0])*sizeof(char));		
		strcpy(all_dict[i].eng[0],temp->eng[0]);
		all_dict[i].eng[1]=(char*)malloc(strlen(temp->eng[1])*sizeof(char));
		strcpy(all_dict[i].eng[1],temp->eng[1]);
		all_dict[i].eng[2]=(char*)malloc(strlen(temp->eng[2])*sizeof(char));
		strcpy(all_dict[i].eng[2],temp->eng[2]);
		all_dict[i].rus=(char*)malloc((strlen(temp->rus)+1)*sizeof(char));
		strcpy(all_dict[i].rus,temp->rus);
		if(!(all_dict[i].eng[0])||!(all_dict[i].eng[1])||!(all_dict[i].eng[2])||!(all_dict[i].rus)){
			printf("ошибка выделения памяти ALL_DICT\n");
			return -3;
		}
	}
	fscanf(sav,"%d%d", &repetition, &max_word_in_cycle);
	clear();
	int rand_cycle[max_word_in_cycle];
	for(i=0;i<max_word_in_cycle;i++)rand_cycle[i]=-1;
	while(1){
		//проверка на наличие невыученных слов
		l=0;
		for(i=0;i<max;i++){
			if((all_dict[i].sp)>=repetition)l++;
		}
		if(max==l){
			clear();
			mvwprintw(stdscr, (lines/2), 4, 
			"Вы выучили все слова! Если хотите повторить,\n можете увеличить нужное количество верных ответов\n или сбросить статистику.");
			getch();
			sav_dict(all_dict, max);
			return 1;
		}
		if((max-l)<max_word_in_cycle)max_word_in_cycle=max-l;//берем сколько есть
		//берем случайные слова на пустые места и отвеченные слова
		mvwprintw(stdscr, (lines/2), 4, "!!");
		random_cycle(max_word_in_cycle, rand_cycle, repetition, max, all_dict);
		for(i=0;i<max_word_in_cycle;i++){
			clear();
			strcpy(temp->eng[0],"не введено");
			strcpy(temp->eng[1],"не введено");
			strcpy(temp->eng[2],"не введено");
			mvwprintw(stdscr, lines/2-3, columns/2, "%s",all_dict[rand_cycle[i]].rus);
			mvwprintw(stdscr, lines/2-2, columns/2-14, "первая форма: ");
			mvwprintw(stdscr, lines/2-1, columns/2-14, "вторая форма: ");
			mvwprintw(stdscr, lines/2, columns/2-14, "третья форма: ");
			mvwscanw(stdscr, lines/2-2, columns/2, "%s",temp->eng[0]);
			mvwscanw(stdscr, lines/2-1, columns/2, "%s",temp->eng[1]);
			mvwscanw(stdscr, lines/2, columns/2, "%s",temp->eng[2]);
			clear();
			if(rawno(temp, all_dict, rand_cycle, i)){
					mvwprintw(stdscr, lines/2-2, columns/2-14, "Верно! Нажмите enter для продолжения.");
					all_dict[rand_cycle[i]].p++;
					all_dict[rand_cycle[i]].sp++;
					if(getch()!='\n'){
						sav_dict(all_dict, max);
						return 0;
					}
			}else{
				mvwprintw(stdscr, lines/2-2, columns/2-24, "первая форма, введено:%s, правильный ответ:%s"
					,temp->eng[0],all_dict[rand_cycle[i]].eng[0]);
				mvwprintw(stdscr, lines/2-1, columns/2-24, "вторая форма, введено:%s, правильный ответ:%s"
					,temp->eng[1],all_dict[rand_cycle[i]].eng[1]);
				mvwprintw(stdscr, lines/2, columns/2-24, "третья форма, введено:%s, правильный ответ:%s"
					,temp->eng[2],all_dict[rand_cycle[i]].eng[2]);
				all_dict[rand_cycle[i]].n++;
				all_dict[rand_cycle[i]].sp=0;
				if(getch()!='\n'){
					sav_dict(all_dict, max);
					return 0;
				}
			}
		}
	}
	fclose(dict);
	fclose(sav);
	sav_dict(all_dict, max);
	return 0;
}
