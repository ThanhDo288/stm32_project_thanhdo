#include <stdint.h>
#include "stm32f10x.h"

void Dec2String(uint32_t num, char* buffer) {
    uint32_t i = 0;
    uint32_t delta = 1000000000;

    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    if (num > 999999999) {
        buffer[i++] = '*';
        buffer[i++] = '.';
        buffer[i++] = '*';
        buffer[i++] = '*';
        buffer[i++] = '*';
        buffer[i] = '\0';
        return;
    }

    while (num == 0) {
        delta /= 10;
        i++;
    }

    while (delta > 0) {
        uint32_t digit = num / delta;
        num -= digit * delta;
        buffer[i++] = digit + '0';
        if (i == 1) {
            buffer[i++] = '.';
        }
        delta /= 10;
    }

    buffer[i] = '\0';
}

void Fix2String(uint32_t num, char* buffer) {
    uint32_t i = 0;
    uint32_t delta = 1000;

    if (num > 9999) {
        buffer[i++] = '*';
        buffer[i++] = '.';
        buffer[i++] = '*';
        buffer[i++] = '*';
        buffer[i++] = '*';
        buffer[i] = '\0';
        return;
    }

    while (delta > 0) {
        uint32_t digit = num / delta;
        num -= digit * delta;
        buffer[i++] = digit + '0';
        if (i == 1) {
            buffer[i++] = '.';
        }
        delta /= 10;
    }

    buffer[i] = '\0';
}
