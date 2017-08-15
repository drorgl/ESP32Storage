# ESP32 Filesystem Tests

- FAT
- SPIFFS

Tests show that fat is way faster than SPIFFS, formatting and writing takes significantly more time with SPIFFS.

However, from running all these tests, it seems that fat is more prone to corruption.

Resources:
- https://github.com/loboris/ESP32_spiffs_example
- https://github.com/pellepl/spiffs
- https://github.com/SuperHouse/esp-open-rtos/tree/master/extras/spiffs


