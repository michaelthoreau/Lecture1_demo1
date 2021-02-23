/*
*   File:   main.cpp
*   Author: Michael Thoreau for ECE-GY 6483
*   Date:   2021/02/23
*/
#include <mbed.h>


/*
*   Combining a typedef with a struct definition
*   Struct contains a value and an DigitalOut object
*/
typedef struct {
  uint8_t val;
  DigitalOut* out;
} myStruct_t;


/*Set an LED
*  
*   Args:
*     out: A DigitalOut Object to toggle - our LED
*     val: the value
*
*   Returns:
*     None
*/
void setLED(DigitalOut* out, uint8_t val) {
  uint8_t writeVal = val;
  out->write(writeVal);
}


/*Set an LED using a pointer
*  
*   Args:
*     out: A pointer to a DigitalOut Object to toggle - our LED
*     val: pointer to the value
*
*   Returns:
*     None
*/
void setLEDviaPtr(DigitalOut* out, uint8_t* val) {
  uint8_t writeVal = *val;
  out->write(writeVal);
}


/*Toggle an LED
*  
*   Args:
*     out: A pointer to a DigitalOut Object to toggle - our LED
*
*   Returns:
*     None
*/
void toggleLED(DigitalOut* out) {
  
  //short but less clear?
  // *out = !*out;

  //equivalent - but more readable
  uint8_t tmp = out->read();
  out->write(!tmp);
}



/*Set an LED using a Struct
*  
*   Args:
*     structPtr: A pointer to the struct containing an LED pointer and a value
*
*   Returns:
*     None
*/
void setLEDviaStruct(myStruct_t* structPtr) {

  // These lines are equivalent
  uint8_t writeVal = structPtr->val;
          writeVal = (*structPtr).val;
  
  // dont get tricked - this will give you an error
          // writeVal = *structPtr.val
  // note:  *structPtr.val != (*structPtr).val

  structPtr->out->write(writeVal);
}


int main() {

  uint8_t tmp = 0;

  // define LEDs
  DigitalOut led1(LED3);
  DigitalOut led2(LED4);
  DigitalOut led3(LED5);
  DigitalOut led4(LED6);


  // initialise the struct
  myStruct_t myStruct_inst;
  myStruct_inst.val = 0;
  myStruct_inst.out = &led3;

  while(1) {

    // set an LED
    setLED(&led1, tmp);

    // set an LED using pass by reference
    setLEDviaPtr(&led2, &tmp); 

    // set an LED by passing a single pointer to a struct
    setLEDviaStruct(&myStruct_inst);

    // toggle an LED
    toggleLED(&led4);
    

    // toggle the variables
    tmp = !tmp;
    myStruct_inst.val = tmp;

    // delay
    wait_ms(500);

  }
}