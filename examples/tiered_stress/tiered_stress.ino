////////////////////////////////////////////////////////////////////////////////
// Filename: tiered_stress.ino
// Author: Jack Pyburn
// Description: This Arduino sketch is intended to stress an external 
// SST39LF401C NOR Flash IC with a three division tiered pattern. Check the IC
// datasheet for more information.
////////////////////////////////////////////////////////////////////////////////

#include <SST39LF401C.h> // use defualt pin assignment

#define KWORD 1024

#define ANSI_COLOR_DEFAULT "\x1B[0m"
#define ANSI_COLOR_GREEN "\x1B[32m"

SST39LF401C memory;

static const uint32_t division1_starts[16] = {
  0x08000, 0x08800, 0x09000, 0x09800,
  0x0A000, 0x0A800, 0x0B000, 0x0B800,
  0x0C000, 0x0C800, 0x0D000, 0x0D800,
  0x0E000, 0x0E800, 0x0F000, 0x0F800
};

static const uint32_t division2_starts[16] = {
  0x20000, 0x20800, 0x21000, 0x21800,
  0x22000, 0x22800, 0x23000, 0x23800,
  0x24000, 0x24800, 0x25000, 0x25800,
  0x26000, 0x26800, 0x27000, 0x27800
};

static const uint32_t division3_starts[16] = {
  0x38000, 0x38800, 0x39000, 0x39800,
  0x3A000, 0x3A800, 0x3B000, 0x3B800,
  0x3C000, 0x3C800, 0x3D000, 0x3D800,
  0x3E000, 0x3E800, 0x3F000, 0x3F800
};

#define STEP 10000

void setup() 
{
  char buffer[64];

  SerialUSB.begin(115200);
  while (!SerialUSB);
  while ((char)SerialUSB.read() != '\r'); // wait for user to press return

  SerialUSB.print("[    ] Initializing Memory Device ");
  memory.begin();
  SerialUSB.println("\r[" ANSI_COLOR_GREEN "DONE" ANSI_COLOR_DEFAULT);

  SerialUSB.println("PE Cycle Count: 0");

  for (uint32_t start_index = 0; start_index < 16; ++start_index) {
    SerialUSB.println();

    for (uint32_t i = start_index; i < 16; ++i) {
      snprintf(buffer, 64, "[....] Stressing Sector %3u 0x%05X", i + 16, division1_starts[i]);
      SerialUSB.print(buffer);
      memory.sector_stress(division1_starts[i], STEP);
      SerialUSB.println("\r[" ANSI_COLOR_GREEN "DONE" ANSI_COLOR_DEFAULT);

      snprintf(buffer, 64, "[....] Stressing Sector %3u 0x%05X", i + 64, division2_starts[i]);
      SerialUSB.print(buffer);
      memory.sector_stress(division2_starts[i], STEP);
      SerialUSB.println("\r[" ANSI_COLOR_GREEN "DONE" ANSI_COLOR_DEFAULT);

      snprintf(buffer, 64, "[....] Stressing Sector %3u 0x%05X", i + 112, division3_starts[i]);
      SerialUSB.print(buffer);
      memory.sector_stress(division3_starts[i], STEP);
      SerialUSB.println("\r[" ANSI_COLOR_GREEN "DONE" ANSI_COLOR_DEFAULT);
    }

    SerialUSB.print("PE Cycle Count: "); Serial.println(start_index * STEP);
  }

  SerialUSB.println("Stressing complete");
}

void loop() {}
