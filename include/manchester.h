//
// Created by wolfgang on 26.11.2021.
//

#ifndef __MANCHESTER_H__
#define __MANCHESTER_H__

#include <stdint.h>

/**
 * @brief This enum represents the polarity of the mancherster encoding. It can either be LSG-Left or LSB-Right.
 */
typedef enum MAN_POLARITY {
    LSB_RIGHT,
    LSB_LEFT
} MAN_POLARITY;

/**
 * @brief Decodes 2 Bytes in manchester encoding and returns the original data.
 *
 * @param data
 * @param polarity
 * @return uint8_t
 */
uint8_t man_dec_8(uint16_t data, MAN_POLARITY polarity);
/**
 * @brief Decodes 4 Bytes in manchester encoding and returns the original data.
 *
 * @param data
 * @param polarity
 * @return uint8_t
 */
uint16_t man_dec_16(uint32_t data, MAN_POLARITY polarity);
/**
 * @brief Decodes 8 Bytes in manchester encoding and returns the original data.
 *
 * @param data
 * @param polarity
 * @return uint8_t
 */
uint32_t man_dec_32(uint64_t data, MAN_POLARITY polarity);

/**
 * @brief Creates a manchester encoding for 1 Byte.
 *
 * @param data
 * @param polarity
 * @return uint16_t
 */
uint16_t man_enc_8(uint8_t data, MAN_POLARITY polarity);
/**
 * @brief Creates a manchester encoding for 2 Byte.
 *
 * @param data
 * @param polarity
 * @return uint32_t
 */
uint32_t man_enc_16(uint16_t data, MAN_POLARITY polarity);
/**
 * @brief Creates a manchester encoding for 4 Byte.
 *
 * @param data
 * @param polarity
 * @return uint64_t
 */
uint64_t man_enc_32(uint32_t data, MAN_POLARITY polarity);

/**
 * @brief Prints 8 bits to the terminal. This function was only implemented for debuging reasons.
 *
 * @param data
 */
void bin_output8(uint8_t data);
/**
 * @brief Prints 16 bits to the terminal. This function was only implemented for debuging reasons.
 *
 * @param data
 */
void bin_output16(uint16_t data);
/**
 * @brief Prints 32 bits to the terminal. This function was only implemented for debuging reasons.
 *
 * @param data
 */
void bin_output32(uint32_t data);
/**
 * @brief Prints 64 bits to the terminal. This function was only implemented for debuging reasons.
 *
 * @param data
 */
void bin_output64(uint64_t data);

#endif  // __MANCHESTER_H__