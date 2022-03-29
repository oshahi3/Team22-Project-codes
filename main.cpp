#include <iostream>
#include <vector>
#include <string>
extern "C" {
#include "i2c.c"
}


/**
 * @brief 
 * This program is meant to act as a bridge between connecting the jetson nano
 * and the FPGA board. By utilizing i2c communication and sending single bytes
 * of information for the motor throttles and speed.
 * 
 * Author: Brevon Baker
 * UIC ECE Department 
 * ECE 397 Senior Design II (2022)
 **/


// Motor Addresses
const __u8 FWL = 0x32;
const __u8 FWR = 0x33;
const __u8 RWL = 0x34;
const __u8 RWR = 0x35;

// Slave Address
const __u8 FPGA_ADDRESS = 0x00;
// Speed configuration/calculation
// Anything greater than 127 or 7F will be in the reverse direction
const __u8 FULL_THROTTLE_FORWARD = 0x4b;
const __u8 HALF_THROTTLE_FORWARD = 0x23;
const __u8 FULL_THROTTLE_BACKWARD = 0xE2;
const __u8 HALF_THROTTLE_BACKWARD = 0xa3;


using namespace std;


void forward() {
    int bus = initBus();
    writeByte(bus, FPGA_ADDRESS, FWL, FULL_THROTTLE_FORWARD);
    writeByte(bus, FPGA_ADDRESS, FWR, FULL_THROTTLE_FORWARD);
    writeByte(bus, FPGA_ADDRESS, RWL, FULL_THROTTLE_FORWARD);
    writeByte(bus, FPGA_ADDRESS, RWR, FULL_THROTTLE_FORWARD);
}

void left_turn() {
    int bus = initBus();
    writeByte(bus, FPGA_ADDRESS, FWL, FULL_THROTTLE_FORWARD);
    writeByte(bus, FPGA_ADDRESS, FWR, HALF_THROTTLE_FORWARD);
    writeByte(bus, FPGA_ADDRESS, RWL, FULL_THROTTLE_FORWARD);
    writeByte(bus, FPGA_ADDRESS, RWR, HALF_THROTTLE_FORWARD);
}

void right_turn() {
    int bus = initBus();
    writeByte(bus, FPGA_ADDRESS, FWL, HALF_THROTTLE_FORWARD);
    writeByte(bus, FPGA_ADDRESS, FWR, FULL_THROTTLE_FORWARD);
    writeByte(bus, FPGA_ADDRESS, RWL, HALF_THROTTLE_FORWARD);
    writeByte(bus, FPGA_ADDRESS, RWR, FULL_THROTTLE_FORWARD);
}

void backward() {
    int bus = initBus();
    writeByte(bus, FPGA_ADDRESS, FWL, FULL_THROTTLE_BACKWARD);
    writeByte(bus, FPGA_ADDRESS, FWR, FULL_THROTTLE_BACKWARD);
    writeByte(bus, FPGA_ADDRESS, RWL, FULL_THROTTLE_BACKWARD);
    writeByte(bus, FPGA_ADDRESS, RWR, FULL_THROTTLE_BACKWARD);
}

void left_turn_backward() {
    int bus = initBus();
    writeByte(bus, FPGA_ADDRESS, FWL, HALF_THROTTLE_BACKWARD);
    writeByte(bus, FPGA_ADDRESS, FWR, FULL_THROTTLE_BACKWARD);
    writeByte(bus, FPGA_ADDRESS, RWL, HALF_THROTTLE_BACKWARD);
    writeByte(bus, FPGA_ADDRESS, RWR, FULL_THROTTLE_BACKWARD);
}

void right_turn_backward() {
    int bus = initBus();
    writeByte(bus, FPGA_ADDRESS, FWL, FULL_THROTTLE_BACKWARD);
    writeByte(bus, FPGA_ADDRESS, FWR, HALF_THROTTLE_BACKWARD);
    writeByte(bus, FPGA_ADDRESS, RWL, FULL_THROTTLE_BACKWARD);
    writeByte(bus, FPGA_ADDRESS, RWR, HALF_THROTTLE_BACKWARD);
}

int main()
{
    cout << "Hello World!" << endl;
    forward();


    return 0;
}