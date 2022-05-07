#include "PulseCounter.h"

PulseCounter::PulseCounter(Smoothed<uint16_t>* report_to, uint16_t report_after) {
    this->_report_to = report_to;
    this->_report_after = report_after;
}

void PulseCounter::trigger() {
    this->_pulse_count++;
    if (this->_pulse_count >= this->_report_after) {
        float average_period = (micros() - this->_last_report) / this->_pulse_count;
        uint16_t rpm = 60000000.0 / average_period;
        this->_report_to->add(rpm);
        this->_pulse_count = 0;
        this->_last_report = micros();
    }
}