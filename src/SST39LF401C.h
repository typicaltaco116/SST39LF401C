#pragma once
#include <Arduino.h>

#include "SST39LF401C_pin_assignments.h"

class SST39LF401C 
{
  protected:
    int DQ_pins[DQ_BUS_WIDTH];

    uint32_t port_A_IO_mask;
    uint32_t port_B_IO_mask;
    uint32_t port_C_IO_mask;
    uint32_t port_D_IO_mask;

    void build_IO_mask(void);
    void prepareIO_Read(void);
    void prepareIO_Write(void);
    void pushAddress(uint32_t address);
    void pushData(uint16_t data);
    void fast_word_program(uint32_t address, uint16_t data);

    void command_write_cycle(uint32_t address, uint16_t data);

    uint32_t block_start_table[11] = {
        0x00000,
        0x02000,
        0x03000,
        0x04000,
        0x08000,
        0x10000,
        0x18000,
        0x20000,
        0x28000,
        0x30000,
        0x38000
    };

    uint32_t block_end_table[11] = {
        0x01FFF,
        0x02FFF,
        0x03FFF,
        0x07FFF,
        0x0FFFF,
        0x17FFF,
        0x1FFFF,
        0x27FFF,
        0x2FFFF,
        0x37FFF,
        0x3FFFF
    };

  public:
    SST39LF401C();
  
    void begin(void);
    uint16_t word_read(uint32_t address);
    void word_program(uint32_t address, uint16_t data);
    void bulk_program(uint32_t start_address, uint32_t end_address, uint16_t data);
    // end_address is non inclusive
    void sector_erase(uint32_t address);
    void sector_partial_erase(uint32_t address, unsigned int time_us);
    void sector_stress(uint32_t sector_address, uint32_t count);

    uint32_t get_block_start(uint8_t block);
    uint32_t get_block_end(uint8_t block);

    const int sector_size = 2048; // units of words
};
