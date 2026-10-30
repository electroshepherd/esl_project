/**
 * Copyright (c) 2014 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"

#include "pca10059.h"

/**
 * @brief Function for application main entry.
 */
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

int main(void)
{
    /* Configure board. */
	leds_init();
	buttons_init();

    unsigned int times_to_blink[] = {6, 5, 9, 9};
    /* Toggle LEDs. */
    uint32_t i = 0; //led_id
    uint32_t b = times_to_blink[i]; //blink counter
    while (true)
    {
	    while(button_state_get(0)) {
		    if(b==0) {
			    if(i<=2) i++;
			    else if(i==3) i = 0;
			    else i=0;
			    b = times_to_blink[i];
		    }
		    blink_once(i);
		    nrf_delay_ms(200);
		    b-=1;
	    }
    }
}


/**
 *@}
 **/
