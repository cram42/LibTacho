#include "Tacho.h"

Tacho::Tacho(uint8_t read_pin) {

    Tacho::instance = this;

    this->_read_pin = read_pin;
    pinMode(this->_read_pin, INPUT);
}

void Tacho::set_enable(uint8_t enable_pin, bool enable_level) {
    this->_enable_pin = enable_pin;
    this->_enable_level = enable_level;
    this->_enable_set = true;

    pinMode(this->_enable_pin, OUTPUT);
    digitalWrite(this->_enable_pin, !this->_enable_level);
}

void Tacho::begin() {
    this->_rpm.begin(SMOOTHED_EXPONENTIAL, 40);
    if (this->_enable_set) digitalWrite(this->_enable_pin, this->_enable_level);
    attachInterrupt(digitalPinToInterrupt(this->_read_pin), Tacho::on_interrupt, FALLING);
}

void Tacho::loop() {
    if (millis() >= this->_next_reading_time) {
        uint16_t rpm = this->_readings[this->_next_reading_index].read();
        this->_next_reading_index++;
        if (this->_next_reading_index >= NUM_READINGS) this->_next_reading_index = 0;
        this->_next_reading_time = millis() + OUTPUT_INTERVAL;
        this->_rpm.add(rpm);
        Serial.println(this->_rpm.get());
    }
}

void Tacho::increment() {
    for (uint8_t i = 0; i < NUM_READINGS; i++) {
        this->_readings[i].increment();
    }
}


Tacho* Tacho::instance;
void Tacho::on_interrupt() { Tacho::instance->increment(); }