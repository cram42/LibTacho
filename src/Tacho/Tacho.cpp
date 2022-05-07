#include "Tacho.h"

Tacho* Tacho::handler_instance;
void Tacho::handle_interrupt() { Tacho::handler_instance->trigger(); }


Tacho::Tacho(uint8_t read_pin, uint8_t enable_pin, bool enable_level) {

    Tacho::handler_instance = this;
    
    this->_read_pin = read_pin;
    pinMode(this->_read_pin, INPUT);

    this->_use_enable = true;
    this->_enable_pin = enable_pin;
    this->_enable_level = enable_level;
    pinMode(this->_enable_pin, OUTPUT);
    digitalWrite(this->_enable_pin, !this->_enable_level);
}

void Tacho::begin() {
    if (this->_use_enable) digitalWrite(this->_enable_pin, this->_enable_level);
    attachInterrupt(digitalPinToInterrupt(this->_read_pin), Tacho::handle_interrupt, FALLING);
    this->_pulse_length.begin(SMOOTHED_AVERAGE);
    this->_rpm.begin(SMOOTHED_AVERAGE);
}

void Tacho::loop() {
    if (millis() >= this->_last_calculate + 100) {
        this->_rpm.add(60000000.0 / this->_pulse_length.get());
        this->_last_calculate = millis();
    }
}

void Tacho::trigger() {
    uint32_t period = micros() - this->_last_timestamp;
    this->_pulse_length.add(period);
    this->_last_timestamp = micros();
}

uint32_t Tacho::get_rpm() { return this->_rpm.get(); }