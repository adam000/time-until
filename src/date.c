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
      case 4:
      case 6:
      case 9:
      case 11:
         return 30;
   }

   // invalid
   return 0;
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
