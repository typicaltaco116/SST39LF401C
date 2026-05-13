#include <SST39LF401C.h>

#include "NOR_stats.h"

SST39LF401C memory;

uint32_t division1_starts[16] = {
  0x08000, 0x08800, 0x09000, 0x09800,
  0x0A000, 0x0A800, 0x0B000, 0x0B800,
  0x0C000, 0x0C800, 0x0D000, 0x0D800,
  0x0E000, 0x0E800, 0x0F000, 0x0F800
};

uint32_t division2_starts[16] = {
  0x20000, 0x20800, 0x21000, 0x21800,
  0x22000, 0x22800, 0x23000, 0x23800,
  0x24000, 0x24800, 0x25000, 0x25800,
  0x26000, 0x26800, 0x27000, 0x27800
};

uint32_t division3_starts[16] = {
  0x38000, 0x38800, 0x39000, 0x39800,
  0x3A000, 0x3A800, 0x3B000, 0x3B800,
  0x3C000, 0x3C800, 0x3D000, 0x3D800,
  0x3E000, 0x3E800, 0x3F000, 0x3F800
};

const unsigned long erase_time_bounds[] = {20, 100};

static void do_sector_partial_erase_stats(uint32_t sector)
{
  char text_buffer[64];

  for (int erase_time = erase_time_bounds[0]; erase_time < erase_time_bounds[1]; erase_time += 1) {
    memory.sector_erase(sector);
    memory.bulk_program(
      sector, // lower bound
      sector + memory.sector_size, // upper bound
      0x0000 // programming value for all words in the range
    );
    memory.sector_partial_erase(
      sector, 
      erase_time
    );

    int total_errors = get_sector_bit_error_count(memory, sector, EXPECTED_ERASE_VALUE);

    sprintf(text_buffer, "%05X, %d, %d", sector, erase_time, total_errors);
    SerialUSB.println(text_buffer);
  }
}

void setup() 
{

  SerialUSB.begin(115200);

  while (!SerialUSB);
  while (SerialUSB.read() != '\r');

  memory.begin();

  SerialUSB.println("Sector_Address, t_erase_us, error_count");

  for (auto &sector : division1_starts)
    do_sector_partial_erase_stats(sector);
}

void loop() {}
