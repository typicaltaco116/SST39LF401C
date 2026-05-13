#include "NOR_stats.h"
#include <SST39LF401C.h>

#define STAT_READ_COUNT 11

int get_sector_bit_error_count(SST39LF401C &mem, uint32_t sector_start, uint16_t expected)
{
    int total_errors = 0;

    uint32_t sector_end = sector_start + mem.sector_size;

    uint32_t address = sector_start;

    for (uint32_t address = sector_start; address < sector_end; ++address) {
        uint16_t difference_votes[16] = {0};

        for (int read_count = 0; read_count < STAT_READ_COUNT; ++read_count) {
            uint16_t differences = mem.word_read(address) ^ expected;

            for (int i = 0; i < 16; ++i)
                if (differences & (1 << i))
                    difference_votes[i]++;
        }

        for (int i = 0; i < 16; ++i)
            if (difference_votes[i] >= (STAT_READ_COUNT / 2 + 1))
                total_errors++;
    }

    return total_errors;
}

float get_sector_BER(SST39LF401C &mem, uint32_t sector_start, uint16_t expected)
{
    float total_errors = static_cast<float>(
        get_sector_bit_error_count(mem, sector_start, expected) );
    
    return total_errors / static_cast<float>( mem.sector_size * 16);
}
