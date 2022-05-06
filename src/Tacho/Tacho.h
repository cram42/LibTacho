#pragma once

#include <Arduino.h>
#include <Smoothed.h>
#include "../TachoReading/TachoReading.h"

#define OUTPUT_INTERVAL 100
#define READ_INTERVAL 1000
#define NUM_READINGS (READ_INTERVAL / OUTPUT_INTERVAL)

class Tacho {
    public:
        Tacho(uint8_t read_pin);
        void set_enable(uint8_t enable_pin, bool enable_level = HIGH);
        void begin();
        void loop();
        void increment();

        static Tacho* instance;
        static void on_interrupt();

    private:
        uint8_t _read_pin;
        
        uint8_t _enable_pin;
        bool _enable_level;
        bool _enable_set = false;

        TachoReading _readings[NUM_READINGS];
        uint8_t _next_reading_index = 0;
        uint32_t _next_reading_time = 0;

        Smoothed<uint16_t> _rpm;
};