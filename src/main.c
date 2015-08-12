#include <pebble.h>
#include "date.h"
#include "colors.h"

Window *window;
TextLayer *layer_day;
TextLayer *layer_month;
TextLayer *layer_year;
int selected = 0;
Date date;
char* day;
char* month;
char* year;

void config_provider(Window* window);

void updateWhichSelected() {
   text_layer_set_background_color(layer_day, C_BACKGROUND);
   text_layer_set_text_color(layer_day, C_FOREGROUND);
   text_layer_set_background_color(layer_month, C_BACKGROUND);
   text_layer_set_text_color(layer_month, C_FOREGROUND);
   text_layer_set_background_color(layer_year, C_BACKGROUND);
   text_layer_set_text_color(layer_year, C_FOREGROUND);
   switch (selected % 3) {
   case 0:
      text_layer_set_background_color(layer_day, C_BACKGROUND_SELECTED);
      text_layer_set_text_color(layer_day, C_FOREGROUND_SELECTED);
      break;
   case 1:
      text_layer_set_background_color(layer_month, C_BACKGROUND_SELECTED);
      text_layer_set_text_color(layer_month, C_FOREGROUND_SELECTED);
      break;
   case 2:
      text_layer_set_background_color(layer_year, C_BACKGROUND_SELECTED);
      text_layer_set_text_color(layer_year, C_FOREGROUND_SELECTED);
      break;
   }

   size_t len = sizeof(char) * 32;
   char* str = malloc(len);
   snprintf(str, len, "Set selected level: %d", selected % 3);
   APP_LOG(APP_LOG_LEVEL_DEBUG, str);
   free(str);
}

void handle_init(void) {
   date = Today();

   // Create a window and text layer
   window = window_create();
   layer_day = text_layer_create(GRect(9, 66, 28, 35));
   layer_month = text_layer_create(GRect(43, 66, 28, 35));
   layer_year = text_layer_create(GRect(76, 66, 58, 35));

   day = Day(&date);
   text_layer_set_text(layer_day, day);
   text_layer_set_font(layer_day, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
   text_layer_set_text_alignment(layer_day, GTextAlignmentCenter);
   text_layer_set_background_color(layer_day, C_BACKGROUND);
   text_layer_set_text_color(layer_day, C_FOREGROUND);
   layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_day));

   month = Month(&date);
   text_layer_set_text(layer_month, month);
   text_layer_set_font(layer_month, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
   text_layer_set_text_alignment(layer_month, GTextAlignmentCenter);
   text_layer_set_background_color(layer_month, C_BACKGROUND);
   text_layer_set_text_color(layer_month, C_FOREGROUND);
   layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_month));

   year = Year(&date);
   text_layer_set_text(layer_year, year);
   text_layer_set_font(layer_year, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
   text_layer_set_text_alignment(layer_year, GTextAlignmentCenter);
   text_layer_set_background_color(layer_year, C_BACKGROUND);
   text_layer_set_text_color(layer_year, C_FOREGROUND);
   layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer_year));

   updateWhichSelected();

   window_set_click_config_provider(window, (ClickConfigProvider)config_provider);

   // Push the window
   window_stack_push(window, true);
}

void handle_deinit(void) {
   // Destroy the text layers
   text_layer_destroy(layer_day);
   text_layer_destroy(layer_month);
   text_layer_destroy(layer_year);

   // Destroy the window
   window_destroy(window);
}

int main(void) {
   handle_init();
   app_event_loop();
   handle_deinit();
}

void mid_single_click_handler(ClickRecognizerRef recognizer, void* context) {
   selected++;
   updateWhichSelected();
}

void modifyDisplayDate(int direction) {
   switch (selected % 3) {
   case 0:
      date.day += direction;
      NormalizeDay(&date);
      break;
   case 1:
      date.month += direction;
      NormalizeMonth(&date);
      break;
   case 2:
      date.year += direction;
      NormalizeMonth(&date);
      break;
   }

   text_layer_set_text(layer_day, Day(&date));
   text_layer_set_text(layer_month, Month(&date));
   text_layer_set_text(layer_year, Year(&date));

   updateWhichSelected();
}

void up_single_click_handler(ClickRecognizerRef recognizer, void* context) {
   modifyDisplayDate(1);
}

void down_single_click_handler(ClickRecognizerRef recognizer, void* context) {
   modifyDisplayDate(-1);
}

void config_provider(Window* window) {
   window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
   window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
   window_single_click_subscribe(BUTTON_ID_SELECT, mid_single_click_handler);
}

/* vim: set sw=3: */
