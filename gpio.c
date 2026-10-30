#include "gpio.h"

const uint8_t leds_list[LEDS_NUMBER] = LEDS_LIST;
const uint8_t buttons_list[BUTTONS_NUMBER] = BUTTONS_LIST;

bool button_state_get(uint32_t button_id) { //stands for bsp_board_button_state_get from boards.c
	if(button_id < BUTTONS_NUMBER) {
		return nrf_gpio_pin_read(buttons_list[button_id])==BUTTONS_ACTIVE_STATE;
	}
	return 0;
}

void led_on(uint32_t led_id) { //stands for bsp_board_led_on() from boards.c
	if(led_id<LEDS_NUMBER) {
        	nrf_gpio_pin_write(leds_list[led_id], LEDS_ACTIVE_STATE);
	}
}

void led_off(uint32_t led_id) { //stands for bsp_board_led_on() from boards.c
	if(led_id<LEDS_NUMBER) {
        	nrf_gpio_pin_write(leds_list[led_id], ~LEDS_ACTIVE_STATE);
	}
}

void leds_off()
{
    uint32_t i;
    for (i = 0; i < LEDS_NUMBER; ++i)
    {
       led_off(i);
    }
}

void leds_init() { //stands for bsp_board_leds_init in boards.c
    uint32_t i;
    for (i = 0; i < LEDS_NUMBER; ++i)
    {
        nrf_gpio_cfg_output(leds_list[i]);
    }
    leds_off();
}

void buttons_init() { //stands for bsp_board_buttons_init in boards.c
    uint32_t i;
    for (i = 0; i < BUTTONS_NUMBER; ++i)
    {
        nrf_gpio_cfg_input(buttons_list[i], BUTTON_PULL);
    }
}

void blink_n_times(int n, int i) {
	for(int j = 0; j<n; j+=1) {
            led_on(i);
            nrf_delay_ms(200);
            led_off(i);
            nrf_delay_ms(200);
	}
}
void blink_once(uint32_t i) {
	led_on(i);
	nrf_delay_ms(200);
	led_off(i);
}
