#ifndef __COMMON_DEF__
#define __COMMON_DEF__

typedef struct record
{
    void *fst;
    void *snd;
} * Record;

int yes(void *a, void *b);
Record createRecord(void *fs, void *sn);

int is_A(void *value, void *user_data);
int is_Q(void *value, void *user_data);

int date_compare(const void *a /*x*/, const void *b /*y*/, void *user_data);

int int_cmp(void *a, void *b, void *user_data);
int np_cmp(void *a, void *b, void *user_data);

int post_compare(void *a, void *b, void *user_data); // não vai ser preciso.
int inv_post_compare(void *a, void *b, void *user_data);
int score_cmp(void *a, void *b, void *user_data);
int nAns_cmp(void *a, void *b, void *user_data);
int post_ord(const void *a, const void *b);

#endif