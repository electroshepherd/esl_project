#include "pca10059.h"
#include "nrf_delay.h"
#include <stdint.h>
#include <stdbool.h>

bool button_state_get(uint32_t button_id);  //stands for bsp_board_button_state_get from boards.c
void led_on(uint32_t led_id); //stands for bsp_board_led_on() from boards.c
void led_off(uint32_t led_id); //stands for bsp_board_led_on() from boards.c
void leds_off();
void leds_init(); //stands for bsp_board_leds_init in boards.c
void buttons_init(); //stands for bsp_board_buttons_init in boards.c
void blink_n_times(int n, int i);
void blink_once(uint32_t i);
