//
// Created by wolfgang on 26.11.2021.
//

#ifndef __MANCHESTER_H__
#define __MANCHESTER_H__

#include <stdint.h>

typedef enum MAN_POLARITY {
    LSB_RIGHT,
    LSB_LEFT
} MAN_POLARITY;

uint8_t man_dec_8(uint16_t data, MAN_POLARITY polarity);
uint16_t man_dec_16(uint32_t data, MAN_POLARITY polarity);
uint32_t man_dec_32(uint64_t data, MAN_POLARITY polarity);

uint16_t man_enc_8(uint8_t data, MAN_POLARITY polarity);
uint32_t man_enc_16(uint16_t data, MAN_POLARITY polarity);
uint64_t man_enc_32(uint32_t data, MAN_POLARITY polarity);

void bin_output8(uint8_t data);
void bin_output16(uint16_t data);
void bin_output32(uint32_t data);
void bin_output64(uint64_t data);

#endif  // __MANCHESTER_H__