#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x9D, 0x67, 0x17, 0x45, 0xF8, 0x26, 0x49, 0x6E, 0xB1, 0xD3, 0x28, 0x54, 0x23, 0xC1, 0x22, 0x71 }
PBL_APP_INFO(MY_UUID,
             "Door Awesomest", "Nearbuy",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
static Layer mainLayer;
static TextLayer mainTextLayer;

void top_button_handler(ClickRecognizerRef recognizer, Window *window) {
  (void) recognizer;
  (void) window;

  // send the "open front" message to the iphone app
}

void bottom_button_handler(ClickRecognizerRef recognizer, Window *window) {
  (void) recognizer;
  (void) window;

  // send the "open side" message to the iphone app
}

void config_provider(ClickConfig **config, Window *window) {
  (void) window;

  config[BUTTON_ID_UP]->click.handler = (ClickHandler) top_button_handler;
  config[BUTTON_ID_UP]->click.repeat_interval_ms = 3000;

  config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) bottom_button_handler;
  config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 3000;
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Door Awesomest Pebble");
  window_stack_push(&window, true /* Animated */);
  window_set_fullscreen(&window, true);
  window_set_background_color(&window, GColorClear);

  window.layer.bounds.size.w -= 10;
  window.layer.bounds.size.h -= 10;

  layer_init(&mainTextLayer, window.layer.frame);
  mainTextLayer.update_proc = &main_text_layer_update_callback;
  layer.add_child(&window.layer, &mainTextLayer);

  text_layer_init(&

  // handle the desired button events
  window_set_click_config_provider(&window, (ClickConfigProvider) config_provider);
}

void handle_second_tick(AppContextRef context, PebbleTickEvent *t) {
  (void)t;
  (void)context;


}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
      .tick_handler = &handle_second_tick,
      .tick_units = SECOND_UNIT
    },
    .messaging_info = {
      .buffer_sizes = {
        .inbound = 256,
        .outbound = 256
      }
    }
  };
  app_event_loop(params, &handlers);
}
