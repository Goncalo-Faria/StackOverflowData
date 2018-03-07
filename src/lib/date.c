#include <stdlib.h>
#include "date.h"

struct date {
  int day;
  int month;
  int year;
};

Date createDate(int day, int month, int year) {
    Date d = malloc(sizeof(struct date));
    d->day = day;
    d->month = month;
    d->year = year;
    return d;
}

int get_day(Date d) {
    return d->day; 
}

int get_month(Date d) {
    return d->month; //change to enum? (Acho que sim. Desta forma já garantimos a limitação necessária)
}

int get_year(Date d) {
    return d->year;
}

void free_date(Date d) {
    free(d);
}

int date_compare ( void* a /*x*/, void* b/*y*/,void* user_data){

    // user data será sempre null;

    Date x = (Date)a , y = (Date)b;

    if (get_year(x) > get_year(y) )
        return -1;
    else if( get_year(x) < get_year(y) )
        return 1 ;
    //-----------------------------------------
    if( get_month(x) > get_month(y) )
        return -1;
    else if( get_month(x) < get_month(y) )
        return 1;
    //-----------------------------------------
    if( get_day(x) > get_day(y) )
        return -1;
    else if( get_day(x) < get_day(y) )
        return 1;

    return 0;
}

