// GPIO app
//
// Uses MMIO to control GPIO pins

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"

#include "microbit_v2.h"
#include "gpio.h"

int main(void) {
  printf("Board started!\n");


  // Turn on all LEDs on the back of the Microbit
  // Add code here
  gpio_config(21,GPIO_OUTPUT);
  gpio_config(22,GPIO_OUTPUT);
  gpio_config(15,GPIO_OUTPUT);
  gpio_config(24,GPIO_OUTPUT);
  gpio_config(19,GPIO_OUTPUT);
  gpio_config(28,GPIO_OUTPUT); // sets all rows and columns to outputs
  gpio_config(11,GPIO_OUTPUT);
  gpio_config(31,GPIO_OUTPUT);
  gpio_config(37,GPIO_OUTPUT);
  gpio_config(30,GPIO_OUTPUT);

  gpio_set(21);
  gpio_set(22);
  gpio_set(15); // sets all rows to high
  gpio_set(24);
  gpio_set(19);

  gpio_clear(28); // sets all columns to low
  gpio_clear(11);
  gpio_clear(31);
  gpio_clear(37);
  gpio_clear(30);



  // setting buttons to inputs
  gpio_config(14,GPIO_INPUT);
  gpio_config(23,GPIO_INPUT);
  //set microphone to output
  gpio_config(20,GPIO_OUTPUT);



  // Control LED with raw MMIO
  // Microphone LED is P0.20 and active high
  // Add code here
  // *(uint32_t*)(0x50000514) = 0 | (1<<20);
  // *(uint32_t*)(0x50000504) = 0 | (1<<20);
  

  // loop forever
  printf("Looping\n");
  while (1) {

    // Control LED with buttons
    // Button A is P0.14 and active low
    // Button B is P0.23 and active low
    // Add code here
    // gpio_print();
    nrf_delay_ms(100);
    gpio_print();

    if (!gpio_read(14)){
      gpio_set(20);
    }

    if (!gpio_read(23)){
      gpio_clear(20);
    }
    printf("button A is : %d \n", gpio_read(14));
    printf("button B is : %d \n", gpio_read(23));



  }
}

