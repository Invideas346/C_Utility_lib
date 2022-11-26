//
// Created by wolfgang on 26.11.2021.
//
#include <manchester.h>
#include <stdio.h>
#include <typedef.h>

//! not tested yet
uint8_t man_dec_8(uint16_t data, MAN_POLARITY polarity)
{
    uint8_t dec_data = 0;
    switch(polarity) {
        case LSB_LEFT:
            for(uint32_t i = 0; i < 16; i += 2) {
                if((data & (0x8000 >> i))) {
                    dec_data |= (0x01 << (i >> 1));
                }
            }
            break;

        case LSB_RIGHT:
            for(uint32_t i = 0; i < 16; i += 2) {
                if((data & (0x02 << i))) {
                    dec_data |= (0x01 << (i >> 1));
                }
            }
            break;

        default:
            break;
    }
    return dec_data;
}

//! not tested yet
uint16_t man_dec_16(uint32_t data, MAN_POLARITY polarity)
{
    uint16_t dec_data = 0;
    switch(polarity) {
        case LSB_LEFT: {
            uint8_t lower = man_dec_8((uint16_t) (data & 0xffff), LSB_LEFT);
            uint8_t upper = man_dec_8((uint16_t) ((data & 0xffff0000) >> 16), LSB_LEFT);
            dec_data |= ((uint16_t) lower << 8) | upper;
        } break;

        case LSB_RIGHT: {
            uint8_t lower = man_dec_8((uint16_t) (data & 0xffff), LSB_RIGHT);
            uint8_t upper = man_dec_8((uint16_t) ((data & 0xffff0000) >> 16), LSB_RIGHT);
            dec_data |= ((uint16_t) upper << 8) | lower;
        } break;

        default:
            break;
    }
    return dec_data;
}

//! not tested yet
uint32_t man_dec_32(uint64_t data, MAN_POLARITY polarity)
{
    uint32_t dec_data = 0;
    switch(polarity) {
        case LSB_LEFT: {
            uint16_t lower = man_dec_16((uint32_t) (data & 0xffffffff), LSB_LEFT);
            uint16_t upper = man_dec_16((uint32_t) ((data & 0xffffffff00000000) >> 32), LSB_LEFT);
            dec_data |= ((uint32_t) lower << 16) | upper;
        } break;

        case LSB_RIGHT: {
            uint16_t lower = man_dec_16((uint32_t) (data & 0xffffffff), LSB_RIGHT);
            uint16_t upper = man_dec_16((uint32_t) ((data & 0xffffffff00000000) >> 32), LSB_RIGHT);
            dec_data |= ((uint32_t) upper << 16) | lower;
        } break;

        default:
            break;
    }
    return dec_data;
}

//! not tested yet
uint16_t man_enc_8(uint8_t data, MAN_POLARITY polarity)
{
    uint16_t enc_data = 0;
    switch(polarity) {
        case LSB_LEFT:
            for(uint32_t i = 0; i < 8; i++) {
                if(data & (0x01 << i)) {
                    enc_data |= (0x8000 >> (i << 1));
                }
                else {
                    enc_data |= (0x4000 >> (i << 1));
                }
            }
            break;

        case LSB_RIGHT:
            for(uint32_t i = 0; i < 8; i++) {
                if(data & (0x01 << i)) {
                    enc_data |= (0x02 << (i << 1));
                }
                else {
                    enc_data |= (0x01 << (i << 1));
                }
            }
            break;

        default:
            break;
    }
    return enc_data;
}

//! not tested yet
uint32_t man_enc_16(uint16_t data, MAN_POLARITY polarity)
{
    uint32_t enc_data = 0;
    switch(polarity) {
        case LSB_LEFT: {
            uint16_t lower = man_enc_8((uint8_t) (data & 0xff), LSB_LEFT);
            uint16_t upper = man_enc_8((uint8_t) ((data & 0xff00) >> 8), LSB_LEFT);
            enc_data |= (lower << 16) | upper;
        } break;

        case LSB_RIGHT: {
            uint16_t lower = man_enc_8((uint8_t) (data & 0xff), LSB_RIGHT);
            uint16_t upper = man_enc_8((uint8_t) ((data & 0xff00) >> 8), LSB_RIGHT);
            enc_data |= (upper << 16) | lower;
        } break;

        default:
            break;
    }
    return enc_data;
}

//! not tested yet
uint64_t man_enc_32(uint32_t data, MAN_POLARITY polarity)
{
    uint64_t enc_data = 0u;
    switch(polarity) {
        case LSB_LEFT: {
            uint32_t lower = man_enc_16((uint16_t) (data & 0xffff), LSB_LEFT);
            uint32_t upper = man_enc_16((uint16_t) ((data & 0xffff0000) >> 16), LSB_LEFT);
            enc_data |= ((uint64_t) lower << 32) | upper;
        } break;

        case LSB_RIGHT: {
            uint32_t lower = man_enc_16((uint16_t) (data & 0xffff), LSB_RIGHT);
            uint32_t upper = man_enc_16((uint16_t) ((data & 0xffff0000) >> 16), LSB_RIGHT);
            enc_data |= ((uint64_t) upper << 32) | lower;
        } break;

        default:
            break;
    }
    return enc_data;
}

void bin_output8(uint8_t data)
{
    char output[9] = {'0', '0', '0', '0', '0', '0', '0', '0', 0};
    for(uint32_t i = 0; i < 8; i++) {
        output[7 - i] += ((data & (0x1 << i)) >> i);
    }
    printf("%s", output);
}

void bin_output16(uint16_t data)
{
    bin_output8((data & (0xff << 8)) >> 8);
    printf(" ");
    bin_output8(data & 0xff);
}

void bin_output32(uint32_t data)
{
    bin_output16((uint16_t) ((data & (0xffff << 16)) >> 16));
    printf(" ");
    bin_output16(data & 0xffff);
}

void bin_output64(uint64_t data)
{
    bin_output32((data & ((uint64_t) 0xffffffff << 32)) >> 32);
    printf(" ");
    bin_output32((uint32_t) (data & 0xffffffff));
}