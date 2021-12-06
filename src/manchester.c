//
// Created by wolfgang on 26.11.2021.
//
#include <manchester.h>

ui8 man_dec_8(ui16 data, MAN_POLARITY polarity)
{
    ui8 decData = 0;
    switch(polarity)
    {
        case LSB_LEFT:
            for(ui32 i = 0; i < 16; i += 2)
            {
                if((data & (0x8000 >> i)))
                {
                    decData |= (0x01 << (i >> 1));
                }
            }
            break;

        case LSB_RIGHT:
            for(ui32 i = 0; i < 16; i += 2)
            {
                if((data & (0x02 << i)))
                {
                    decData |= (0x01 << (i >> 1));
                }
            }
            break;

        default:
            break;
    }
    return decData;
}
ui16 man_dec_16(ui32 data, MAN_POLARITY polarity)
{
    ui16 decData = 0;
    switch(polarity)
    {
        case LSB_LEFT:
        {
            ui8 lower = man_dec_8((ui16)(data & 0xffff), LSB_LEFT);
            ui8 upper = man_dec_8((ui16)((data & 0xffff0000) >> 16), LSB_LEFT);
            decData |= ((ui16) lower << 8) | upper;
        }
        break;

        case LSB_RIGHT:
        {
            ui8 lower = man_dec_8((ui16)(data & 0xffff), LSB_RIGHT);
            ui8 upper = man_dec_8((ui16)((data & 0xffff0000) >> 16), LSB_RIGHT);
            decData |= ((ui16) upper << 8) | lower;
        }
        break;

        default:
            break;
    }
    return decData;
}
ui32 man_dec_32(ui64 data, MAN_POLARITY polarity)
{
    ui32 decData = 0;
    switch(polarity)
    {
        case LSB_LEFT:
        {
            ui16 lower = man_dec_16((ui32)(data & 0xffffffff), LSB_LEFT);
            ui16 upper = man_dec_16((ui32)((data & 0xffffffff00000000) >> 32), LSB_LEFT);
            decData |= ((ui32) lower << 16) | upper;
        }
        break;

        case LSB_RIGHT:
        {
            ui16 lower = man_dec_16((ui32)(data & 0xffffffff), LSB_RIGHT);
            ui16 upper = man_dec_16((ui32)((data & 0xffffffff00000000) >> 32), LSB_RIGHT);
            decData |= ((ui32) upper << 16) | lower;
        }
        break;

        default:
            break;
    }
    return decData;
}

ui16 man_enc_8(ui8 data, MAN_POLARITY polarity)
{
    ui16 encData = 0;
    switch(polarity)
    {
        case LSB_LEFT:
            for(ui32 i = 0; i < 8; i++)
            {
                if(data & (0x01 << i))
                {
                    encData |= (0x8000 >> (i << 1));
                }
                else
                {
                    encData |= (0x4000 >> (i << 1));
                }
            }
            break;

        case LSB_RIGHT:
            for(ui32 i = 0; i < 8; i++)
            {
                if(data & (0x01 << i))
                {
                    encData |= (0x02 << (i << 1));
                }
                else
                {
                    encData |= (0x01 << (i << 1));
                }
            }
            break;

        default:
            break;
    }
    return encData;
}
ui32 man_enc_16(ui16 data, MAN_POLARITY polarity)
{
    ui32 encData = 0;
    switch(polarity)
    {
        case LSB_LEFT:
        {
            ui16 lower = man_enc_8((ui8)(data & 0xff), LSB_LEFT);
            ui16 upper = man_enc_8((ui8)((data & 0xff00) >> 8), LSB_LEFT);
            encData |= (lower << 16) | upper;
        }
        break;

        case LSB_RIGHT:
        {
            ui16 lower = man_enc_8((ui8)(data & 0xff), LSB_RIGHT);
            ui16 upper = man_enc_8((ui8)((data & 0xff00) >> 8), LSB_RIGHT);
            encData |= (upper << 16) | lower;
        }
        break;

        default:
            break;
    }
    return encData;
}
ui64 man_enc_32(ui32 data, MAN_POLARITY polarity)
{
    ui64 encData = 0u;
    switch(polarity)
    {
        case LSB_LEFT:
        {
            ui32 lower = man_enc_16((ui16)(data & 0xffff), LSB_LEFT);
            ui32 upper = man_enc_16((ui16)((data & 0xffff0000) >> 16), LSB_LEFT);
            encData |= ((ui64) lower << 32) | upper;
        }
        break;

        case LSB_RIGHT:
        {
            ui32 lower = man_enc_16((ui16)(data & 0xffff), LSB_RIGHT);
            ui32 upper = man_enc_16((ui16)((data & 0xffff0000) >> 16), LSB_RIGHT);
            encData |= ((ui64) upper << 32) | lower;
        }
        break;

        default:
            break;
    }
    return encData;
}