// Bump.c
// Runs on MSP432
// Provide low-level functions that interface bump switches the robot.
// Robert Hayek | Fall 2021

// Negative logic bump sensors
// P4.7 Bump5, left side of robot
// P4.6 Bump4
// P4.5 Bump3
// P4.3 Bump2
// P4.2 Bump1
// P4.0 Bump0, right side of robot

#include <stdint.h>
#include "msp.h"
// Initialize Bump sensors
// Make six Port 4 pins inputs
// Activate interface pull-up
// pins 7,6,5,3,2,0
void Bump_Init(void) {
    P4->SEL0 &= ~0xED;  // Set pins 4.(7,6,5,3,2,0) as GPIO
    P4->SEL1 &= ~0xED;  // Set pins 4.(7,6,5,3,2,0) as GPIO
    P4->DIR &= ~0xED;   // Setting pins as inputs
    P4->REN |= 0xED;    // Activating interface pull-ups on pins
    P4->OUT |= 0xED;    // Setting 1 to the OUT register on the pin bit number
}

// Read current state of 6 switches
// Returns a 6-bit positive logic result (0 to 63)
// bit 5 Bump5
// bit 4 Bump4
// bit 3 Bump3
// bit 2 Bump2
// bit 1 Bump1
// bit 0 Bump0
uint8_t Bump_Read(void) {
    uint8_t result;   // 8-bit resulting SW data
    // Storing individual bump switch data
    uint8_t bump0 = P4->IN&0x01;    // Value on P4.0 --> Bump SW 0 Data
    uint8_t bump1 = P4->IN&0x04;    // Value on P4.2 --> Bump SW 1 Data
    uint8_t bump2 = P4->IN&0x08;    // Value on P4.3 --> Bump SW 2 Data
    uint8_t bump3 = P4->IN&0x20;    // Value on P4.5 --> Bump SW 3 Data
    uint8_t bump4 = P4->IN&0x40;    // Value on P4.6 --> Bump SW 4 Data
    uint8_t bump5 = P4->IN&0x80;    // Value on P4.7 --> Bump SW 5 Data

    // Building the 6-bit positive logic result
    result = 0 << 7;
    result |= 0 << 6;
    result |= ~bump5 << 5;
    result |= ~bump4 << 4;
    result |= ~bump3 << 3;
    result |= ~bump2 << 2;
    result |= ~bump1 << 1;
    result |= ~bump0;

    return result;
}

