#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "datawork.h"

int Randd(int zern,int max)
{
	srand(time(NULL)*rand()/RAND_MAX+zern*zern);
	return (double)rand()/RAND_MAX*max;
}

int rawno(words *temp, words all_dict[], int rand_cycle[], unsigned i){
	int rasn='A'-'a';
	if((strcmp(temp->eng[0]+1,all_dict[rand_cycle[i]].eng[0]+1)==0)&&
		(strcmp(temp->eng[1]+1,all_dict[rand_cycle[i]].eng[1]+1)==0)&&
		(strcmp(temp->eng[2]+1,all_dict[rand_cycle[i]].eng[2]+1)==0)&&
		((temp->eng[0][0]==all_dict[rand_cycle[i]].eng[0][0])||(((temp->eng[0][0])-(all_dict[rand_cycle[i]].eng[0][0]))==rasn))&&
		((temp->eng[1][0]==all_dict[rand_cycle[i]].eng[1][0])||(((temp->eng[1][0])-(all_dict[rand_cycle[i]].eng[1][0]))==rasn))&&
		((temp->eng[2][0]==all_dict[rand_cycle[i]].eng[2][0])||(((temp->eng[2][0])-(all_dict[rand_cycle[i]].eng[2][0]))==rasn))){
		return 1;
	}else{
		return 0;
	}
}

int count_string(FILE *f){
	int lines_count = 0;
	while(!feof(f)){
		if(fgetc(f)=='\n'){
			lines_count++;
		}
	}
	rewind(f);
	return lines_count;
}

int seek_str(FILE *f, long j){
	rewind(f);
	int lines_count=1;
	while(!feof(f)&&lines_count<j){
		if(fgetc(f)=='\n') {
			lines_count++;
		}
	}
	return 0;
}

int random_cycle(unsigned max_word_in_cycle, int *rand_cycle, unsigned repetition,unsigned max, words* all_dict){		
	int i,k,j,flag;
	
	for(i=0;i<max_word_in_cycle;i++){
		if((rand_cycle[i]==-1)||((all_dict[rand_cycle[i]].sp)>=repetition)){
			k=Randd(i,max);//рандомный номер
			flag=0;
			for(j=0;j<max_word_in_cycle;j++){
				if(k==rand_cycle[j]){//убираем повторы
					flag=1;
				}
			}
			while(((all_dict[k].sp)>=repetition)||flag==1){
				k++;
				if(k==max)k=0;
				flag=0;
				for(j=0;j<max_word_in_cycle;j++){
					if(k==rand_cycle[j]){//убираем повторы
						flag=1;
					}
				}
			}
			rand_cycle[i]=k;
		}
	}
	return 0;
}

int stat_null(){
		FILE *dict=fopen("dictionary.txt", "r");
		FILE *dict_temp=fopen("dict_temp.txt", "w");
		if(!dict)return -5;
		//if(!dict_temp)return -5;
		words *temp;
		int i;
		int max; 
		max=count_string(dict);
		temp=(words*)malloc(sizeof(words));
		temp->eng[0]=(char*)malloc(50*sizeof(char));
		temp->eng[1]=(char*)malloc(50*sizeof(char));
		temp->eng[2]=(char*)malloc(50*sizeof(char));
		temp->rus=(char*)malloc(50*sizeof(char));
		if(!(temp->eng[0])||!(temp->eng[1])||!(temp->eng[2])||!(temp->rus)){
			printf("ошибка выделения памяти TEMP2\n");
			return -2;
		}
		for(i=0;i<max;i++){
			fscanf(dict,"%d%d%s%s%s%s%d",&(temp->p),&(temp->n),temp->eng[0],temp->eng[1],temp->eng[2],temp->rus,&(temp->sp));
			fprintf(dict_temp,"0 0 %s %s %s %s 0\n",temp->eng[0],temp->eng[1],temp->eng[2],temp->rus);
		}
		fclose(dict);
		fclose(dict_temp);
		remove("dictionary.txt");
		rename("dict_temp.txt","dictionary.txt");
		return 0;
}

int sav_dict( words all_dict[], unsigned max){	
	int i;	
	FILE *dict_t=fopen("dict_temp.txt", "w");
	//if(!dict_t)return -5;
	for(i=0;i<max;i++){
		fprintf(dict_t,"%d %d %s %s %s %s %d\n", all_dict[i].p, all_dict[i].n, all_dict[i].eng[0],
			all_dict[i].eng[1],all_dict[i].eng[2],all_dict[i].rus,all_dict[i].sp);
	}
	fclose(dict_t);
	remove("dictionary.txt");
	rename("dict_temp.txt","dictionary.txt");
	return 0;
}
