#include "NOR_stats.h"
#include "lib_SST39LF401C/SST39LF401C.h"

int get_sector_bit_error_count(SST39LF401C &mem, uint8_t sector, uint16_t expected)
{
    int total_errors = 0;

    uint32_t start = mem.get_sector_start(sector);
    uint32_t end = mem.get_sector_end(sector);
    uint32_t address = start;

    while (address <= end) {
        uint16_t read_val = mem.word_read(address);
        uint16_t compare = read_val ^ expected;

        uint16_t bitmask = 0x1;
        for (int i = 0; i < 16; ++i) {
            if (compare & bitmask)
                total_errors++;
            bitmask = bitmask << 1;
        }

        address++;
}

return total_errors;
}

float get_sector_BER(SST39LF401C &mem, uint8_t sector, uint16_t expected)
{
    float total_errors = static_cast<float>(
        get_sector_bit_error_count(mem, sector, expected) );
    
    return total_errors /
        (static_cast<float>(mem.get_sector_end(sector) - mem.get_sector_start(sector) + 1) * 16);
}
