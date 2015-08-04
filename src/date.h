#pragma once

typedef struct {
   int day;
   int month;
   int year;
} Date;

Date CurrentDate();
Date DiffDates(Date start, Date end);
Date Today();

static const Date InvalidDate = { .day = -1, .month = -1, .year = -1 };
