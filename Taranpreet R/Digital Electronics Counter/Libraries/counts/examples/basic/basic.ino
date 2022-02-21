#include "counts.h"

uint32_t buttons[] = {ACT1, ACT2, ACT3, ACT4, ACT5, ACT6, ACT7, ACT8, ACT9, ACT10};
uint32_t leds[] = {P1, P2, P3, P4, P5, P6, P7, P8, P9, P10};

void setup() {
  // put your setup code here, to run once:
  init_counts();
}

void loop() {
  // put your main code here, to run repeatedly:
  check_new_round();
  check_play();
  check_stop();
  check_BLE_mode();
  check_sleep();
  check_start_button();
  check_stop_button();
  check_reset_button();

  for (int i = 0; i < 10; i++)
  {
    if (check_button(buttons[i]))
    {
      toggle_led(leds[i]);
    }
  }
}
