/* MYUTILS_H */

#ifndef MYUTILS_H
#define MYUTILS_H

#include <Arduino.h>
#include <sensors.h>

#define DEBUG
#define UPDATE_RTC

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Payload data struct to send in communication. Data size at most 12 bytes.
 * Attention to the struct padding that increase the size of struct.
 * char - 1 byte;
 * uint8_t - 1 byte;
 * uint16_t - 2 bytes;
 * int - 4 bytes;
 * float - 4 bytes;
 * double - 8 bytes;
 */
typedef struct payload{
    int i = 128;
    float v = 3.333;
    float pi = 3.14159;
} payload;


/**
 * Class of items in linked list. This objects with read data will be save and removed
 * from the list to be logged in file.
 */
class DataItemList{
    public:
        parameter param;
        double value;
        String timestamp;
};


#ifdef __cplusplus
}
#endif

#endif