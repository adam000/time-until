#include <pebble.h>
#include <time.h>
#include "date.h"

Date getTimeAsDate(time_t unixTime) {
   struct tm* time = localtime(&unixTime);
   Date date = {
      .day = time->tm_mday,
      .month = time->tm_mon,
      .year = time->tm_year
   };
   return date;
}

Date CurrentDate() {
   return getTimeAsDate(time(NULL));
}

int daysInYear(int year) {
   if (year%4 == 0) {
      return 366;
   }
   return 365;
}

int daysInMonth(int month, int year) {
   if (month == 2 && year%4 == 0) {
      return 29;
   }

   switch (month) {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
         return 31;
      case 2:
         return 28;
      case 4:
      case 6:
      case 9:
      case 11:
         return 30;
   }

   // invalid
   return 0;
}

int dayOfYear(Date date) {
   int numDays = 0;
   for (int i = 1; i < date.month; i++) {
      numDays += daysInMonth(i, date.year);
   }
   numDays += date.day;
   return numDays;
}

Date DiffDates(Date start, Date end) {
   if (start.year > end.year) {
      return InvalidDate;
   } else if (start.year == end.year) {
      if (start.month > end.month) {
         return InvalidDate;
      } else if (start.month == end.month && start.day > end.day) {
         return InvalidDate;
      }
   }

   Date diff = {
      .day = end.day - start.day,
      .month = end.month - start.month,
      .year = end.year - start.year
   };

   if (diff.day <= 0) {
      diff.month--;
      int priorMonth = end.month - 1;
      int priorYear = end.year;
      if (priorMonth <= 0) {
         priorMonth += 12;
         priorYear--;
      }
      diff.day += daysInMonth(priorMonth, priorYear);
   }

   if (diff.month < 0) {
      diff.year--;
      diff.month += 12;
   }

   return diff;
}

int DiffDatesDays(Date start, Date end) {
   int numDays = 0;

   numDays -= dayOfYear(start);

   for (int year = start.year; year < end.year; year++) {
      numDays += daysInYear(year);
   }

   numDays += dayOfYear(end) + 1;

   return numDays;
}

Date Today() {
    return getTimeAsDate(time(NULL));
}

char* Day(Date* date) {
    size_t len = sizeof(char) * 2;
    char* day = malloc(len);
    snprintf(day, len, "%02d", date->day);
    return day;
}

char* Month(Date* date) {
    size_t len = sizeof(char) * 2;
    char* month = malloc(len);
    snprintf(month, len, "%02d", date->month);
    return month;
}

char* Year(Date* date) {
    size_t len = sizeof(char) * 2;
    char* year = malloc(len);
    snprintf(year, len, "%02d", date->year);
    return year;
}
