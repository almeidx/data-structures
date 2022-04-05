#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

typedef struct Date {
  int day, month, year;
} DATE;

DATE *get_current_date();

#endif  // DATE_H_INCLUDED
