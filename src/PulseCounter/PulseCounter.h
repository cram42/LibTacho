#pragma once

#include <Arduino.h>
#include <Smoothed.h>

class PulseCounter {
    public:
        PulseCounter(Smoothed<uint16_t>* report_to, uint16_t report_after = 10);
        void trigger();
    
    private:
        Smoothed<uint16_t>* _report_to;
        uint16_t _report_after;
        uint16_t _pulse_count = 0;
        uint32_t _last_report = 0;
};