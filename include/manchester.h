//
// Created by wolfgang on 26.11.2021.
//

#ifndef __MANCHESTER_H__
#define __MANCHESTER_H__

#include <typedef.h>

typedef enum MAN_POLARITY
{
    LSB_RIGHT,
    LSB_LEFT
} MAN_POLARITY;

ui8 man_dec_8(ui16 data, MAN_POLARITY polarity);
ui16 man_dec_16(ui32 data, MAN_POLARITY polarity);
ui32 man_dec_32(ui64 data, MAN_POLARITY polarity);

ui16 man_enc_8(ui8 data, MAN_POLARITY polarity);
ui32 man_enc_16(ui16 data, MAN_POLARITY polarity);
ui64 man_enc_32(ui32 data, MAN_POLARITY polarity);

#endif  // __MANCHESTER_H__
