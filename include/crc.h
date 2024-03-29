#ifndef __CRC_H__
#define __CRC_H__

#include <stdint.h>

/**
 * @brief This enum is a collection of popular used crc polynoms to perform a crc calculation.
 */
typedef enum CRC_POLYNOM {
    CRC1 = 0x1,

    CRC3_GSM_MSB = 0x3,
    CRC3_GSM_LSB = 0x6,

    CRC4_ITU_MSB = 0x3,
    CRC4_ITU_LSB = 0xC,

    CRC5_EPC_MSB = 0x09,
    CRC5_EPC_LSB = 0x12,

    CRC5_ITU_MSB = 0x15,
    CRC5_ITU_LSB = 0x15,

    CRC5_USB_MSB = 0x05,
    CRC5_USB_LSB = 0x14,

    CRC6_CDMA2000A_MSB = 0x27,
    CRC6_CDMA2000A_LSB = 0x39,

    CRC6_CDMA2000B_MSB = 0x07,
    CRC6_CDMA2000B_LSB = 0x38,

    CRC6_DARC_MSB = 0x19,
    CRC6_DARC_LSB = 0x26,

    CRC6_GSM_MSB = 0x2F,
    CRC6_GSM_LSB = 0x3D,

    CRC6_ITU_MSB = 0x03,
    CRC6_ITU_LSB = 0x30,

    CRC7_MSB = 0x09,
    CRC7_LSB = 0x48,

    CRC7_MVB_MSB = 0x65,
    CRC7_MVB_LSB = 0x53,

    CRC8_MSB = 0xD5,
    CRC8_LSB = 0xAB,

    CRC8_AUTOSAR_MSB = 0x2F,
    CRC8_AUTOSAR_LSB = 0xF4,

    CRC8_BLUETOOTH_MSB = 0xA7,
    CRC8_BLUETOOTH_LSB = 0xE5,

    CRC8_CCITT_MSB = 0x07,
    CRC8_CCITT_LSB = 0xE0,

    CRC8_DALLAS_MSB = 0x31,
    CRC8_DALLAS_LSB = 0x8C,

    CRC8_MAXIM_MSB = 0x31,
    CRC8_MAXIM_LSB = 0x8C,

    CRC8_DARC_MSB = 0x39,
    CRC8_DARC_LSB = 0x9C,

    CRC8_GSM_B_MSB = 0x49,
    CRC8_GSM_B_LSB = 0x92,

    CRC8_SAE_MSB = 0x1D,
    CRC8_SAE_LSB = 0xB8,

    CRC8_WCDMA_MSB = 0x9B,
    CRC8_WCDMA_LSB = 0xD9,

    CRC10_MSB = 0x233,
    CRC10_LSB = 0x331,

    CRC10_CDMA2000_MSB = 0x3D9,
    CRC10_CDMA2000_LSB = 0x26F,

    CRC10_GSM_MSB = 0x175,
    CRC10_GSM_LSB = 0x2BA,

    CRC11_MSB = 0x385,
    CRC11_LSB = 0x50E,

    CRC12_MSB = 0x80F,
    CRC12_LSB = 0xF01,

    CRC12_CDMA2000_MSB = 0xF13,
    CRC12_CDMA2000_LSB = 0xC8F,

    CRC12_GSM_MSB = 0xD31,
    CRC12_GSM_LSB = 0x8CB,

    CRC13_BBC_MSB = 0x1CF5,
    CRC13_BBC_LSB = 0x15E7,

    CRC14_DARC_MSB = 0x0805,
    CRC14_DARC_LSB = 0x2804,

    CRC14_GSM_MSB = 0x202D,
    CRC14_GSM_LSB = 0x2D01,

    CRC15_CAN_MSB = 0xC599,
    CRC15_CAN_LSB = 0xC599,

    CRC15_MPT1327_MSB = 0x6815,
    CRC15_MPT1327_LSB = 0x540B,

    CRC16_CHAKRAVARTY_MSB = 0x2F15,
    CRC16_CHAKRAVARTY_LSB = 0xA8F4,

    CRC16_ARINC_MSB = 0xA02B,
    CRC16_ARINC_LSB = 0xD405,

    CRC16_CCITT_MSB = 0x1021,
    CRC16_CCITT_LSB = 0x8408,

    CRC16_CDMA2000_MSB = 0xC867,
    CRC16_CDMA2000_LSB = 0xE613,

    CRC16_DECT_MSB = 0x0589,
    CRC16_DECT_LSB = 0x91A0,

    CRC16_T10DIF_MSB = 0x8BB7,
    CRC16_T10DIF_LSB = 0xEDD1,

    CRC16_DNP_MSB = 0x3D65,
    CRC16_DNP_LSB = 0xA6BC,

    CRC16_IBM_MSB = 0x8005,
    CRC16_IBM_LSB = 0xA001,

    CRC16_OPENSAFETY_A_MSB = 0x5935,
    CRC16_OPENSAFETY_A_LSB = 0xAC9A,

    CRC16_OPENSAFETY_B_MSB = 0x755B,
    CRC16_OPENSAFETY_B_LSB = 0xDAAE,

    CRC17_CAN_MSB = 0x1685B,
    CRC17_CAN_LSB = 0x1B42D,

    CRC21_CAN_MSB = 0x102899,
    CRC21_CAN_LSB = 0x132281,

    CRC24_MSB = 0x5D6DCB,
    CRC24_LSB = 0xD3B6BA,

    CRC24_RADIX64_MSB = 0x864CFB,
    CRC24_RADIX64_LSB = 0xDF3261,

    CRC24_WCDMA_MSB = 0x800063,
    CRC24_WCDMA_LSB = 0xC60001,

    CRC30_MSB = 0x2030B9CF,
    CRC30_LSB = 0x38E74301,

    CRC32_MSB = 0x04C11DB7,
    CRC32_LSB = 0xEDB88320,

    CRC32_32C_MSB = 0x1EDC6F41,
    CRC32_32C_LSB = 0x82F63B78,

    CRC32_32K_MSB = 0x741B8CD7,
    CRC32_32K_LSB = 0xEB31D82E,

    CRC32_32Q_MSB = 0x814141AB,
    CRC32_32Q_LSB = 0xD5828281,

    CRC40_GSM_MSB = 0x0004820009,
    CRC40_GSM_LSB = 0x9000412000,

    CRC64_ECMA_MSB = 0x42F0E1EBA9EA3693,
    CRC64_ECMA_LSB = 0xC96C5795D7870F42,

    CRC64_ISO_MSB = 0x000000000000001B,
    CRC64_ISO_LSB = 0xD800000000000000,
} CRC_POLYNOM;

/**
 * @brief Performs a basic crc calculation on the given data and returns the checksum.
 *
 * @param data
 * @param polynome
 * @param objectSize
 * @param count
 */
void create_crc(void* data, CRC_POLYNOM polynome, uint32_t objectSize, uint32_t count);
/**
 * @brief Performs a crc calculation on the given data with a costum polynom and returns the checksum.
 *
 * @param data
 * @param polynome
 * @param objectSize
 * @param count
 */
void create_crc_custom(void* data, uint64_t polynome, uint32_t objectSize, uint32_t count);

#endif  // __CRC_H__