

#ifndef H_count_string
#define H_count_string
int count_string(FILE * f);

typedef struct words{
	int p;
	int n;
	char *eng[3];
	char *rus;
	int sp;
}words;

#endif

#ifndef H_seekstr
#define H_seekstr
int seek_str(FILE *f, long j);
#endif

#ifndef H_random_cycle
#define H_random_cycle
int random_cycle(unsigned max_word_in_cycle, int *rand_cycle, unsigned repetition, unsigned max, words *all_dict);
#endif

#ifndef H_stat_null
#define H_stat_null
int stat_null();
#endif

#ifndef H_rawno
#define H_rawno
int rawno(words *temp, words all_dict[], int rand_cycle[], unsigned i);
#endif

#ifndef H_sav_dict
#define H_sav_dict
int sav_dict(words all_dict[], unsigned max);
#endif
