#include "NOR_stats.h"
#include <SST39LF401C.h>

SST39LF401C memory; // declare global class instantiation

void setup() 
{
  SerialUSB.begin(115200);
  while (!SerialUSB);
  while (SerialUSB.read() != '\r');

  memory.begin();

  SerialUSB.println(get_sector_BER(memory, 0, 0x0000));
}

void loop() {}
