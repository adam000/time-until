#include "datePicker.h"
#include "colors.h"

void config_provider(Window* window);

void updateWhichSelected(DatePickerWindow w) {
   text_layer_set_background_color(w.day.layer, C_BACKGROUND);
   text_layer_set_text_color(w.day.layer, C_FOREGROUND);
   text_layer_set_background_color(w.month.layer, C_BACKGROUND);
   text_layer_set_text_color(w.month.layer, C_FOREGROUND);
   text_layer_set_background_color(w.year.layer, C_BACKGROUND);
   text_layer_set_text_color(w.year.layer, C_FOREGROUND);
   switch (w.selected % 3) {
   case 0:
      text_layer_set_background_color(w.day.layer, C_BACKGROUND_SELECTED);
      text_layer_set_text_color(w.day.layer, C_FOREGROUND_SELECTED);
      break;
   case 1:
      text_layer_set_background_color(w.month.layer, C_BACKGROUND_SELECTED);
      text_layer_set_text_color(w.month.layer, C_FOREGROUND_SELECTED);
      break;
   case 2:
      text_layer_set_background_color(w.year.layer, C_BACKGROUND_SELECTED);
      text_layer_set_text_color(w.year.layer, C_FOREGROUND_SELECTED);
      break;
   }

   /* size_t len = sizeof(char) * 32; */
   /* char* str = malloc(len); */
   /* snprintf(str, len, "Set selected level: %d", w.selected % 3); */
   /* APP_LOG(APP_LOG_LEVEL_DEBUG, str); */
   /* free(str); */
}

DatePickerWindow initDatePicker() {
   DatePickerWindow w;

   w.selected = 0;
   w.date = Today();

   w.window = window_create();
   w.day.layer = text_layer_create(GRect(9, 66, 28, 35));
   w.month.layer = text_layer_create(GRect(43, 66, 28, 35));
   w.year.layer = text_layer_create(GRect(76, 66, 58, 35));

   char* day = Day(&w.date);
   text_layer_set_text(w.day.layer, day);
   text_layer_set_font(w.day.layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
   text_layer_set_text_alignment(w.day.layer, GTextAlignmentCenter);
   text_layer_set_background_color(w.day.layer, C_BACKGROUND);
   text_layer_set_text_color(w.day.layer, C_FOREGROUND);
   layer_add_child(window_get_root_layer(w.window), text_layer_get_layer(w.day.layer));

   char* month = Month(&w.date);
   text_layer_set_text(w.month.layer, month);
   text_layer_set_font(w.month.layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
   text_layer_set_text_alignment(w.month.layer, GTextAlignmentCenter);
   text_layer_set_background_color(w.month.layer, C_BACKGROUND);
   text_layer_set_text_color(w.month.layer, C_FOREGROUND);
   layer_add_child(window_get_root_layer(w.window), text_layer_get_layer(w.month.layer));

   char* year = Year(&w.date);
   text_layer_set_text(w.year.layer, year);
   text_layer_set_font(w.year.layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
   text_layer_set_text_alignment(w.year.layer, GTextAlignmentCenter);
   text_layer_set_background_color(w.year.layer, C_BACKGROUND);
   text_layer_set_text_color(w.year.layer, C_FOREGROUND);
   layer_add_child(window_get_root_layer(w.window), text_layer_get_layer(w.year.layer));

   updateWhichSelected(w);

   window_set_click_config_provider_with_context(w.window, (ClickConfigProvider)config_provider, (void*)&w);

   return w;
}

void DestroyDatePicker(DatePickerWindow w) {
   // Destroy the text layers
   text_layer_destroy(w.day.layer);
   text_layer_destroy(w.month.layer);
   text_layer_destroy(w.year.layer);

   // Destroy the window
   window_destroy(w.window);
}

void mid_single_click_handler(ClickRecognizerRef recognizer, void* context) {
   DatePickerWindow* w = (DatePickerWindow*)context;
   w->selected++;
   updateWhichSelected(*w);
}

void modifyDisplayDate(int direction, DatePickerWindow w) {
   switch (w.selected % 3) {
   case 0:
      w.date.day += direction;
      NormalizeDay(&w.date);
      break;
   case 1:
      w.date.month += direction;
      NormalizeMonth(&w.date);
      break;
   case 2:
      w.date.year += direction;
      NormalizeMonth(&w.date);
      break;
   }

   text_layer_set_text(w.day.layer, Day(&w.date));
   text_layer_set_text(w.month.layer, Month(&w.date));
   text_layer_set_text(w.year.layer, Year(&w.date));

   updateWhichSelected(w);
}

void up_single_click_handler(ClickRecognizerRef recognizer, void* context) {
   DatePickerWindow* w = (DatePickerWindow*)context;
   modifyDisplayDate(1, *w);
}

void down_single_click_handler(ClickRecognizerRef recognizer, void* context) {
   DatePickerWindow* w = (DatePickerWindow*)context;
   modifyDisplayDate(-1, *w);
}

void config_provider(Window* window) {
   window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
   window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
   window_single_click_subscribe(BUTTON_ID_SELECT, mid_single_click_handler);
}

/* vim: set sw=3: */
