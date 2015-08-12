#pragma once

typedef struct {
   int day;
   int month;
   int year;
} Date;

Date CurrentDate();
Date DiffDates(Date start, Date end);
Date Today();

char* Day(const Date* date);
char* Month(const Date* date);
char* Year(const Date* date);

void NormalizeDay(Date* date);
void NormalizeMonth(Date* date);

static const Date InvalidDate = { .day = -1, .month = -1, .year = -1 };
