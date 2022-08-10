#include <atmel_start.h>
#include <stdio.h>
#include "drv_ssd1306.h"
#include "gfx.h"


static struct timer_task TIMER_0_task1;
static uint8_t pwm_compare[3] = { 255, 0, 0 };
static uint8_t pwm_level[3] = { 0 };

/*
 Timer callback
 This gets called every millisecond
 The main app basically sets the point at which the pin flips, effectively changing the duty cycle of the pin.
*/
static void TIMER_0_task1_cb(const struct timer_task *const timer_task){
		
	if(pwm_level[0] >= pwm_compare[0]){
		gpio_set_pin_level(PWM0, false);
	}
	else{
		gpio_set_pin_level(PWM0, true);
	}
	
	if(pwm_level[1] >= pwm_compare[1]){
		gpio_set_pin_level(PWM1, false);
	}
	else{
		gpio_set_pin_level(PWM1, true);
	}
	
	if(pwm_level[2] >= pwm_compare[2]){
		gpio_set_pin_level(PWM2, false);
	}
	else{
		gpio_set_pin_level(PWM2, true);
	}
	
	pwm_level[0]++;
	pwm_level[1]++;
	pwm_level[2]++;
	
}

int main(void){
	
	// Initialize the system
	atmel_start_init();
	
	gpio_set_pin_pull_mode(PB08, GPIO_PULL_DOWN);
	
	// Init the display
	SSD1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS, false);
	SSD1306_setRotation(ROTATION_0);
	
    // Boot message
    util_gfx_init();
    util_gfx_set_font(FONT_COMPUTER_12PT);
    util_gfx_set_cursor(10, 1);
    util_gfx_print("DCZia", COLOR_WHITE);
    util_gfx_set_font(FONT_MONO55_8PT);
    util_gfx_set_cursor(10, 18);
    util_gfx_print("30 in ONE", COLOR_WHITE);
    util_gfx_draw_dczia(95, 2, COLOR_WHITE);

    // Display the thing
    SSD1306_display();
	
	// Wait for crowd reaction
	delay_ms(1000);
	
	// Setup the ADC inputs
	uint8_t adc1_buffer[2];
	uint8_t adc2_buffer[2];
	int adc1, adc2;
	adc_sync_enable_channel(&ADC_0, 0);
	
	char ADC1[15];
	char ADC2[15];
	
	// Setup the timer to generate the PWM signals
	TIMER_0_task1.interval = 1;
	TIMER_0_task1.cb       = TIMER_0_task1_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;

	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_start(&TIMER_0);

	// Now loop, forever, forever... FOREVER!
	uint8_t loop = 0;
	
	uint8_t incrementColor = 1, decrementColor = 0, countColor = 0;
	
	while (1) {
		
		// Set GPIO1 output to whatever GPIO0's level is.  GPIO0 has a pull-down enabled.
		gpio_set_pin_level(GPIO1, gpio_get_pin_level(GPIO0));
		
		// Set the PWM duty cycles to fade the RGB colors
		if(++countColor == 255){
			countColor = 0;
			
			pwm_compare[decrementColor] = 0;
			pwm_compare[incrementColor] = 255;
						
			decrementColor++;
			if(decrementColor > 2){
				decrementColor = 0;
			}
			
			incrementColor++;
			if(incrementColor > 2){
				incrementColor = 0;
			}
		}
		
		pwm_compare[decrementColor]--;
		pwm_compare[incrementColor]++;
				
	
		// Only every 10 times - this makes the button press detection more performant without having to redraw the screen each time
		if((loop % 10) == 0){
			
			// Refresh the ADC about every 100ms
			
			adc_sync_set_inputs(&ADC_0,ADC_INPUTCTRL_MUXPOS_PIN2_Val,0x18,0);
			adc_sync_read_channel(&ADC_0, 0, adc1_buffer, 2);
			adc_sync_set_inputs(&ADC_0,ADC_INPUTCTRL_MUXPOS_PIN3_Val,0x18,0);
			adc_sync_read_channel(&ADC_0, 0, adc2_buffer, 2);
			
			adc1 = (adc1_buffer[1] * 256) + adc1_buffer[0] - 30;
			adc2 = (adc2_buffer[1] * 256) + adc2_buffer[0] - 30;
			
			if(adc1 < 0){
				adc1 = 0;
			}
			if(adc2 < 0){
				adc2 = 0;
			}
		
			
			// Update the display about every 100ms
			SSD1306_clearDisplay();
			util_gfx_set_font(FONT_GAMEPLAY_5PT);
			util_gfx_set_cursor(4, 6);
			util_gfx_print("30", COLOR_WHITE);
			util_gfx_set_cursor(5, 12);
			util_gfx_set_font(FONT_VERAMONO_5PT);
			util_gfx_print("in", COLOR_WHITE);
			util_gfx_set_cursor(1, 23);
			util_gfx_set_font(FONT_GAMEPLAY_5PT);
			util_gfx_print("ONE", COLOR_WHITE);
		
			util_gfx_set_font(FONT_MONO55_8PT);
			util_gfx_set_cursor(35, 8);
			snprintf(ADC1, 15, "ADC1: %d.%02dv", ((adc1 * 360) >> 10) / 100, ((adc1 * 360) >> 10) % 100);
			util_gfx_print(ADC1, COLOR_WHITE);
			util_gfx_set_cursor(35, 20);
			snprintf(ADC2, 15, "ADC2: %d.%02dv", ((adc2 * 360) >> 10) / 100, ((adc2 * 360) >> 10) % 100);
			util_gfx_print(ADC2, COLOR_WHITE);
		
			SSD1306_display();
		
		}
		
		delay_ms(5);
		loop++;
		
	}
}

