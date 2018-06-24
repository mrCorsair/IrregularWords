#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../thirdparty/ctest.h"

#include "../src/datawork.h"

CTEST(srawn,test_1)
{
	words *temp,all_dict[2];
	temp=(words*)malloc(sizeof(words));
	temp->eng[0]=(char*)malloc(50*sizeof(char));
	temp->eng[1]=(char*)malloc(50*sizeof(char));
	temp->eng[2]=(char*)malloc(50*sizeof(char));

	all_dict[0].eng[0]=(char*)malloc(50*sizeof(char));
	all_dict[0].eng[1]=(char*)malloc(50*sizeof(char));
	all_dict[0].eng[2]=(char*)malloc(50*sizeof(char));

	all_dict[1].eng[0]=(char*)malloc(50*sizeof(char));
	all_dict[1].eng[1]=(char*)malloc(50*sizeof(char));
	all_dict[1].eng[2]=(char*)malloc(50*sizeof(char));

	if(!((temp->eng[0])&&(temp->eng[1])&&(temp->eng[2])&&(temp->rus))){
		printf("ошибка выделения памяти 1");
		getchar();
	}
	if(!((all_dict[0].eng[0])&&(all_dict[0].eng[1])&&(all_dict[0].eng[2])&&(all_dict[0].rus))){
		printf("ошибка выделения памяти 2");
		getchar();
	}
	if(!((all_dict[1].eng[0])&&(all_dict[1].eng[1])&&(all_dict[1].eng[2])&&(all_dict[1].rus))){
		printf("ошибка выделения памяти 3");
		getchar();
	}
	//память выделили, проверяем

	strcpy(all_dict[0].eng[0],"test1_0");
	strcpy(all_dict[0].eng[1],"test1_1");
	strcpy(all_dict[0].eng[2],"test1_2");

	strcpy(all_dict[1].eng[0],"test2_0");
	strcpy(all_dict[2].eng[1],"test2_1");
	strcpy(all_dict[3].eng[2],"test2_2");

	strcpy(temp->eng[0],"test1_0");
	strcpy(temp->eng[1],"test1_1");
	strcpy(temp->eng[2],"test1_2");

	int rand_cycle[2]={0,1};
	unsigned i=0;

	int c1=rawno(temp, all_dict, rand_cycle, i);

	strcpy(temp->eng[0],"Test1_0");
	strcpy(temp->eng[1],"Test1_1");
	strcpy(temp->eng[2],"Test1_2");

	int c2=rawno(temp, all_dict, rand_cycle, i);
	
	strcpy(temp->eng[0],"lest1_0");
	strcpy(temp->eng[1],"teut1_1");
	strcpy(temp->eng[2],"test1_2");

	int c3=rawno(temp, all_dict, rand_cycle, i);

	const int exp1 = 1;
	const int exp2 = 1;
	const int exp3 = 0;

	ASSERT_EQUAL(exp1, c1);
	ASSERT_EQUAL(exp2, c2);
	ASSERT_EQUAL(exp3, c3);
}
