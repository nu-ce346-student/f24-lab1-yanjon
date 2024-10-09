#include "gpio.h"
#include "stdio.h"

typedef struct{
  // Step 3:
  // Add register definitions here
  uint32_t _unused_A[(0x504)/4];
  uint32_t OUT;
  uint32_t OUTSET;
  uint32_t OUTCLR;
  uint32_t IN;
  uint32_t DIR; 
  uint32_t DIRSET;
  uint32_t DIRCLR;
  uint32_t LATCH;
  uint32_t DETECTMODE;
  uint32_t _unused_B[(0x700-0x524)/4 -1];
  uint32_t PIN_CNF[(0x77C-0x700)/4 -1];

} gpio_reg_t;

volatile gpio_reg_t* GPIO_REGS0 = (gpio_reg_t*)(0x50000000);
volatile gpio_reg_t* GPIO_REGS1 = (gpio_reg_t*)(0x50000300);

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
//  dir - gpio direction (INPUT, OUTPUT)
void gpio_config(uint8_t gpio_num, gpio_direction_t dir) {
  // Implement me
  // This function should configure the pin as an input/output
  // Hint: Use proper PIN_CNF instead of DIR
  if (gpio_num>31){
    GPIO_REGS1->PIN_CNF[gpio_num-32] = 3*dir;
    printf("pin %d address: %d\n", gpio_num, &GPIO_REGS1->PIN_CNF[gpio_num-32]);
  }
  else{
    GPIO_REGS0->PIN_CNF[gpio_num] = 3*dir;
    printf("pin %d address: %d\n", gpio_num, &GPIO_REGS0->PIN_CNF[gpio_num]);
  }
  // printf("set pin %d to %d \n", gpio_num, dir);

  

}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_set(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin high
  // It can assume that the pin has already been configured


  if (gpio_num>31){
    GPIO_REGS1->OUTSET = (1 << (gpio_num-32));
  }
  else{
    GPIO_REGS0->OUTSET = (1 << (gpio_num));
  }

}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
void gpio_clear(uint8_t gpio_num) {
  // Implement me
  // This function should make the pin low
  // It can assume that the pin has already been configured
  if (gpio_num>31){
    GPIO_REGS1->OUTCLR= (1 << (gpio_num-32));
  }
  else{
    GPIO_REGS0->OUTCLR= (1 << (gpio_num));
  }
}

// Inputs: 
//  gpio_num - gpio number 0-31 OR (32 + gpio number)
// Output:
//  bool - pin state (true == high)
bool gpio_read(uint8_t gpio_num) {
  // Implement me
  // This function should read the value from the pin
  // It can assume that the pin has already been configured
  if (gpio_num>31){
    volatile int32_t value = GPIO_REGS1->IN;
    return (value & (1 << (gpio_num-32)));
  }
  else{
    volatile int32_t value = GPIO_REGS0->IN;
    return (value & (1 << (gpio_num)));
  }
  return true;
}

// prints out some information about the GPIO driver. Can be called from main()
void gpio_print(void) {
  // Use this function for debugging purposes
  // For example, you could print out struct field addresses
  // You don't otherwise have to write anything here

  printf("DIRSET Pointer: %p\n", &(GPIO_REGS0->DIRSET));
  printf("OUT Pointer: %p\n", &(GPIO_REGS0->OUT));
  printf("PIN_CNF[15] Pointer: %p\n", &(GPIO_REGS0->PIN_CNF[15]));

  


}

