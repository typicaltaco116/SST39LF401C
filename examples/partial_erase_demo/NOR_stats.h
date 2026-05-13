//#include "lib_SST39LF401C/SST39LF401C.h"
#include <SST39LF401C.h>

#define EXPECTED_ERASE_VALUE    0xFFFF
#define EXPECTED_PROGRAM_VALUE  0x0000

int get_sector_bit_error_count(SST39LF401C &mem, uint32_t sector_start, uint16_t expected);

float get_sector_BER(SST39LF401C &mem, uint32_t sector_start, uint16_t expected);
