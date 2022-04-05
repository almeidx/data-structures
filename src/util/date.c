#ifndef DATE_C_INCLUDED
#define DATE_C_INCLUDED

#ifndef time
#include <time.h>
#endif  // time

typedef struct Date {
  int day, month, year;
} DATE;

DATE *get_current_date() {
  DATE *date = (DATE *)malloc(sizeof(DATE));
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  date->day = t->tm_mday;
  date->month = t->tm_mon + 1;
  date->year = t->tm_year + 1900;
  return date;
}

#endif  // DATE_C_INCLUDED
