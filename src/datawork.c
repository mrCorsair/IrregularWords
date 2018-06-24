#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "datawork.h"

int Randd(int zern,int max)
{
	srand(time(NULL)+zern);
	return (double)rand()/RAND_MAX*max;
}

int rawno(words *temp, words all_dict[], int rand_cycle[], unsigned i){
	if((strcmp(temp->eng[0],all_dict[rand_cycle[i]].eng[0])==0)&&
		(strcmp(temp->eng[1],all_dict[rand_cycle[i]].eng[1])==0)&&
		(strcmp(temp->eng[2],all_dict[rand_cycle[i]].eng[2])==0)){
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
/*
int data_init(words *all_dict, int max){
	FILE *dict=fopen("dictionary.txt", "r");
	if(!dict)return -1;
	words *temp=NULL;
	temp=(words*)malloc(sizeof(words));
	temp->eng[0]=(char*)malloc(50*sizeof(char));
	temp->eng[1]=(char*)malloc(50*sizeof(char));
	temp->eng[2]=(char*)malloc(50*sizeof(char));
	temp->rus=(char*)malloc(50*sizeof(char));
	if(!(temp->eng[0])||!(temp->eng[1])||!(temp->eng[2])||!(temp->rus))return -2;
	words all_dict[max];//инициализируем массив структур
	for(i=0;i<max;i++){
		fscanf(dict,"%d%d%s%s%s%s%d",&(temp->p),&(temp->n),temp->eng[0],temp->eng[1],temp->eng[2],temp->rus,&(temp->sp));
		all_dict[i].p=temp->p;
		all_dict[i].n=temp->n;
		all_dict[i].sp=temp->sp;
		all_dict[i].sn=temp->sn;
		all_dict[i].eng[0]=(char*)malloc(strlen(temp->eng[0])*sizeof(char));		
		strcpy(all_dict[i].eng[0],temp->eng[0]);
		all_dict[i].eng[1]=(char*)malloc(strlen(temp->eng[1])*sizeof(char));
		strcpy(all_dict[i].eng[1],temp->eng[1]);
		all_dict[i].eng[2]=(char*)malloc(strlen(temp->eng[2])*sizeof(char));
		strcpy(all_dict[i].eng[2],temp->eng[2]);
		all_dict[i].rus=(char*)malloc(strlen(temp->rus)*sizeof(char));
		strcpy(all_dict[i].rus,temp->rus);
		if(!(all_dict[i].eng[0])||!(all_dict[i].eng[1])||!(all_dict[i].eng[2])||!(all_dict[i].rus))return -3;
	}
	fclose(dict);
	return 0;
}*/

int random_cycle(unsigned max_word_in_cycle, int *rand_cycle, unsigned repetition,unsigned max, words* all_dict){		
	int i,k,j,flag;
	
	for(i=0;i<max_word_in_cycle;i++){
		if((rand_cycle[i]==-1)||((all_dict[rand_cycle[i]].sp)>=repetition)){
			k=Randd(i,max);//рандомный номер
			flag=0;
			for(j=0;j<max_word_in_cycle;j++){
				if((rand_cycle[i]==rand_cycle[j])&&(j!=i)&&(rand_cycle[j]!=-1)){//убираем повторы
					flag=1;
				}
			}
			while(((all_dict[k].p)>=repetition)||flag==1){
				k++;
				if(k>max-1)k=0;
				flag=0;
				for(j=0;j<max_word_in_cycle;j++){
					if((rand_cycle[i]==rand_cycle[j])&&(j!=i)&&(rand_cycle[j]!=-1)){//убираем повторы
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
		words *temp;
		int i;
		int max; 
		max=count_string(dict);
		temp=(words*)malloc(sizeof(words));
		temp->eng[0]=(char*)malloc(50*sizeof(char));
		temp->eng[1]=(char*)malloc(50*sizeof(char));
		temp->eng[2]=(char*)malloc(50*sizeof(char));
		temp->rus=(char*)malloc(50*sizeof(char));
		if(!(temp->eng[0])||!(temp->eng[1])||!(temp->eng[2])||!(temp->rus))return -2;
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
	//if(!dict_t)return -1;
	for(i=0;i<max;i++){
		fprintf(dict_t,"%d %d %s %s %s %s %d\n", all_dict[i].p, all_dict[i].n, all_dict[i].eng[0],
			all_dict[i].eng[1],all_dict[i].eng[2],all_dict[i].rus,all_dict[i].sp);
	}
	fclose(dict_t);
	remove("dictionary.txt");
	rename("dict_temp.txt","dictionary.txt");
	return 0;
}
