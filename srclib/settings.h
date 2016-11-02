#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <stdbool.h>    // For bool, true, false
#include <stddef.h>     // For size_t, NULL
#include <stdint.h>     // For uint32_t, int16_t and etc.

#define _PACKET_LENGTH      256               // Must be as large as any single protocol response (Command, Data, CRC)
#define _COMMAND_LENGTH     sizeof(uint32_t)  // Command name size in bytes (must be 4)
#define _CRC_LENGTH         sizeof(uint16_t)  // CRC size in bytes (must be 2)

#endif  // _SETTINGS_H
