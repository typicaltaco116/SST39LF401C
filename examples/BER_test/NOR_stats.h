#include "lib_SST39LF401C/SST39LF401C.h"

int get_sector_bit_error_count(SST39LF401C &mem, uint8_t sector, uint16_t expected);

float get_sector_BER(SST39LF401C &mem, uint8_t sector, uint16_t expected);
