#pragma once

#include <Arduino.h>
#include <Smoothed.h>

class Tacho {
    public:
        static const bool DEFAULT_ENABLE_LEVEL = HIGH;
        
        static Tacho* handler_instance;
        static void handle_interrupt();

        Tacho(uint8_t read_pin, uint8_t enable_pin = 255, bool enable_level = DEFAULT_ENABLE_LEVEL);

        void begin();
        void loop();
        void trigger();
        uint32_t get_rpm();

    private:
        Smoothed<uint32_t> _pulse_length;
        Smoothed<uint16_t> _rpm;

        uint8_t _read_pin;

        bool _use_enable = false;
        uint8_t _enable_pin;
        bool _enable_level;

        uint32_t _last_timestamp = 0;
        uint32_t _last_calculate = 0;
};