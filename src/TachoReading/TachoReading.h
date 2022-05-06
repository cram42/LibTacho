#pragma once

#include <Arduino.h>

class TachoReading {
    public:
        void increment();
        uint16_t read();
    
    private:
        uint32_t _last_reading = 0;
        uint32_t _revs = 0;
};