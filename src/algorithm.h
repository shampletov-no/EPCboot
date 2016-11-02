#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * If you want crc8 you must make it with table algorithm like crc16
 */
//uint8_t crc8(const void *block, size_t len);

/*
 * CRC-16-IBM also known as CRC-16 and CRC-16-ANSI
 */
uint16_t crc16(const void *block, size_t len);

#if defined(__cplusplus)
};
#endif

#endif  // _ALGORITHM_H
