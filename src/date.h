#pragma once

typedef struct {
   int day;
   int month;
   int year;
} Date;

Date CurrentDate();
Date DiffDates(Date start, Date end);
Date Today();

char* Day(Date* date);
char* Month(Date* date);
char* Year(Date* date);

static const Date InvalidDate = { .day = -1, .month = -1, .year = -1 };
