#include <pebble.h>
#include "date.h"
#include "colors.h"
#include "datePicker.h"

DatePickerWindow w;

void handle_init(void) {
   w = initDatePicker();

   // Push the window
   window_stack_push(w.window, true);
}

void handle_deinit(void) {
   DestroyDatePicker(w);
}

int main(void) {
   handle_init();
   app_event_loop();
   handle_deinit();
}
