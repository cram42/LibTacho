#include "TachoReading.h"

void TachoReading::increment() {
    this->_revs++;
}

uint16_t TachoReading::read() {
    
    noInterrupts();
    uint32_t period = millis() - this->_last_reading;
    uint16_t rpm = (this->_revs * 60) / (1000.0 / (float)period);
    this->_last_reading = millis();
    this->_revs = 0;
    interrupts();

    return rpm;

}