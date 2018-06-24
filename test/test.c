#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../thirdparty/ctest.h"

#include "../src/datawork.h"

CTEST(srawn,test_1)
{
	words *t,a[2];
	t=(words*)malloc(sizeof(words));
	t->eng[0]=(char*)malloc(50*sizeof(char));
	t->eng[1]=(char*)malloc(50*sizeof(char));
	t->eng[2]=(char*)malloc(50*sizeof(char));

	a[0].eng[0]=(char*)malloc(50*sizeof(char));
	a[0].eng[1]=(char*)malloc(50*sizeof(char));
	a[0].eng[2]=(char*)malloc(50*sizeof(char));
	if(!((t->eng[0])&&(t->eng[1])&&(t->eng[2]))){
		printf("ошибка выделения памяти 1\n");
	}
	if(!((a[0].eng[0])&&(a[0].eng[1])&&(a[0].eng[2]))){
		printf("ошибка выделения памяти 2\n");
	}
	//память выделили, проверяем

	strcpy(a[0].eng[0],"test1_0");
	strcpy(a[0].eng[1],"test1_1");
	strcpy(a[0].eng[2],"test1_2");

	strcpy(t->eng[0],"test1_0");
	strcpy(t->eng[1],"test1_1");
	strcpy(t->eng[2],"test1_2");

	int rand_cycle[2]={0,1};
	unsigned i=0;

	int c1=rawno(t, a, rand_cycle, i);

	strcpy(t->eng[0],"Test1_0");
	strcpy(t->eng[1],"Test1_1");
	strcpy(t->eng[2],"Test1_2");

	int c2=rawno(t, a, rand_cycle, i);
	
	strcpy(t->eng[0],"lest1_0");
	strcpy(t->eng[1],"test1_1");
	strcpy(t->eng[2],"test1_2");

	int c3=rawno(t, a, rand_cycle, i);

	const int exp1 = 1;
	const int exp2 = 1;
	const int exp3 = 0;

	ASSERT_EQUAL(exp1, c1);
	ASSERT_EQUAL(exp2, c2);
	ASSERT_EQUAL(exp3, c3);
}
