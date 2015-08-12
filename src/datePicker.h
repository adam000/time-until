#pragma once

#include <pebble.h>
#include "date.h"

typedef struct {
   TextLayer* layer;
   int value;
} IntTextLayer;

typedef struct {
   Window* window;
   IntTextLayer day;
   IntTextLayer month;
   IntTextLayer year;
   int selected;
   Date date;
} DatePickerWindow;

DatePickerWindow initDatePicker();
void DestroyDatePicker(DatePickerWindow w);



/* vim: set sw=3: */
