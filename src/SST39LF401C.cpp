#include "SST39LF401C.h"
#include "digitalWriteFast.h"
#include <Arduino.h>

void SST39LF401C::pushAddress(uint32_t address)
{
    digitalWriteFast(ADR_PIN_0, address & (0x1 << 0));
    digitalWriteFast(ADR_PIN_1, address & (0x1 << 1));
    digitalWriteFast(ADR_PIN_2, address & (0x1 << 2));
    digitalWriteFast(ADR_PIN_3, address & (0x1 << 3));
    digitalWriteFast(ADR_PIN_4, address & (0x1 << 4));
    digitalWriteFast(ADR_PIN_5, address & (0x1 << 5));
    digitalWriteFast(ADR_PIN_6, address & (0x1 << 6));
    digitalWriteFast(ADR_PIN_7, address & (0x1 << 7));
    digitalWriteFast(ADR_PIN_8, address & (0x1 << 8));
    digitalWriteFast(ADR_PIN_9, address & (0x1 << 9));
    digitalWriteFast(ADR_PIN_10, address & (0x1 << 10));
    digitalWriteFast(ADR_PIN_11, address & (0x1 << 11));
    digitalWriteFast(ADR_PIN_12, address & (0x1 << 12));
    digitalWriteFast(ADR_PIN_13, address & (0x1 << 13));
    digitalWriteFast(ADR_PIN_14, address & (0x1 << 14));
    digitalWriteFast(ADR_PIN_15, address & (0x1 << 15));
    digitalWriteFast(ADR_PIN_16, address & (0x1 << 16));
    digitalWriteFast(ADR_PIN_17, address & (0x1 << 17));
}

void SST39LF401C::pushData(uint16_t data)
{
    digitalWriteFast(DQ_PIN_0, data & (0x1 << 0));
    digitalWriteFast(DQ_PIN_1, data & (0x1 << 1));
    digitalWriteFast(DQ_PIN_2, data & (0x1 << 2));
    digitalWriteFast(DQ_PIN_3, data & (0x1 << 3));
    digitalWriteFast(DQ_PIN_4, data & (0x1 << 4));
    digitalWriteFast(DQ_PIN_5, data & (0x1 << 5));
    digitalWriteFast(DQ_PIN_6, data & (0x1 << 6));
    digitalWriteFast(DQ_PIN_7, data & (0x1 << 7));
    digitalWriteFast(DQ_PIN_8, data & (0x1 << 8));
    digitalWriteFast(DQ_PIN_9, data & (0x1 << 9));
    digitalWriteFast(DQ_PIN_10, data & (0x1 << 10));
    digitalWriteFast(DQ_PIN_11, data & (0x1 << 11));
    digitalWriteFast(DQ_PIN_12, data & (0x1 << 12));
    digitalWriteFast(DQ_PIN_13, data & (0x1 << 13));
    digitalWriteFast(DQ_PIN_14, data & (0x1 << 14));
    digitalWriteFast(DQ_PIN_15, data & (0x1 << 15));
}

#define ADD_DIGITAL_PIN_TO_MASK(pin) \
    if (digitalPinToPort(pin) == PIOA) \
        port_A_IO_mask |= digitalPinToBitMask(pin);\
    if (digitalPinToPort(pin) == PIOB) \
        port_B_IO_mask |= digitalPinToBitMask(pin);\
    if (digitalPinToPort(pin) == PIOC) \
        port_C_IO_mask |= digitalPinToBitMask(pin);\
    if (digitalPinToPort(pin) == PIOD) \
        port_D_IO_mask |= digitalPinToBitMask(pin);

void SST39LF401C::build_IO_mask()
{
    port_A_IO_mask = 0;
    port_B_IO_mask = 0;
    port_C_IO_mask = 0;
    port_D_IO_mask = 0;

    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_0)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_1)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_2)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_3)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_4)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_5)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_6)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_7)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_8)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_9)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_10)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_11)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_12)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_13)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_14)
    ADD_DIGITAL_PIN_TO_MASK(DQ_PIN_15)
}

void SST39LF401C::prepareIO_Read()
{
    PIOA->PIO_ODR = port_A_IO_mask;
    PIOB->PIO_ODR = port_B_IO_mask;
    PIOC->PIO_ODR = port_C_IO_mask;
    PIOD->PIO_ODR = port_D_IO_mask;
}

void SST39LF401C::prepareIO_Write()
{
    PIOA->PIO_OER = port_A_IO_mask;
    PIOB->PIO_OER = port_B_IO_mask;
    PIOC->PIO_OER = port_C_IO_mask;
    PIOD->PIO_OER = port_D_IO_mask;
}


SST39LF401C::SST39LF401C(void)
{
    // Array only used for reads
    DQ_pins[0] = DQ_PIN_0;
    DQ_pins[1] = DQ_PIN_1;
    DQ_pins[2] = DQ_PIN_2;
    DQ_pins[3] = DQ_PIN_3;
    DQ_pins[4] = DQ_PIN_4;
    DQ_pins[5] = DQ_PIN_5;
    DQ_pins[6] = DQ_PIN_6;
    DQ_pins[7] = DQ_PIN_7;
    DQ_pins[8] = DQ_PIN_8;
    DQ_pins[9] = DQ_PIN_9;
    DQ_pins[10] = DQ_PIN_10;
    DQ_pins[11] = DQ_PIN_11;
    DQ_pins[12] = DQ_PIN_12;
    DQ_pins[13] = DQ_PIN_13;
    DQ_pins[14] = DQ_PIN_14;
    DQ_pins[15] = DQ_PIN_15;
}

///////////////////////////////////////////////////////
// Setup pin modes
///////////////////////////////////////////////////////
void SST39LF401C::begin(void)
{
    pinMode(ADR_PIN_0, OUTPUT);
    pinMode(ADR_PIN_1, OUTPUT);
    pinMode(ADR_PIN_2, OUTPUT);
    pinMode(ADR_PIN_3, OUTPUT);
    pinMode(ADR_PIN_4, OUTPUT);
    pinMode(ADR_PIN_5, OUTPUT);
    pinMode(ADR_PIN_6, OUTPUT);
    pinMode(ADR_PIN_7, OUTPUT);
    pinMode(ADR_PIN_8, OUTPUT);
    pinMode(ADR_PIN_9, OUTPUT);
    pinMode(ADR_PIN_10, OUTPUT);
    pinMode(ADR_PIN_11, OUTPUT);
    pinMode(ADR_PIN_12, OUTPUT);
    pinMode(ADR_PIN_13, OUTPUT);
    pinMode(ADR_PIN_14, OUTPUT);
    pinMode(ADR_PIN_15, OUTPUT);
    pinMode(ADR_PIN_16, OUTPUT);
    pinMode(ADR_PIN_17, OUTPUT);

    build_IO_mask();

    pinMode(DQ_PIN_0, INPUT);
    pinMode(DQ_PIN_1, INPUT);
    pinMode(DQ_PIN_2, INPUT);
    pinMode(DQ_PIN_3, INPUT);
    pinMode(DQ_PIN_4, INPUT);
    pinMode(DQ_PIN_5, INPUT);
    pinMode(DQ_PIN_6, INPUT);
    pinMode(DQ_PIN_7, INPUT);
    pinMode(DQ_PIN_8, INPUT);
    pinMode(DQ_PIN_9, INPUT);
    pinMode(DQ_PIN_10, INPUT);
    pinMode(DQ_PIN_11, INPUT);
    pinMode(DQ_PIN_12, INPUT);
    pinMode(DQ_PIN_13, INPUT);
    pinMode(DQ_PIN_14, INPUT);
    pinMode(DQ_PIN_15, INPUT);

    pinMode(WE_PIN, OUTPUT);
    pinMode(OE_PIN, OUTPUT);
    pinMode(CE_PIN, OUTPUT);
    pinMode(WP_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);

    pinMode(RYBY_PIN, INPUT_PULLUP);

    digitalWriteFast(CE_PIN, HIGH); // place device into standby mode
    digitalWriteFast(OE_PIN, HIGH);
    digitalWriteFast(WE_PIN, HIGH);
    digitalWriteFast(WP_PIN, HIGH);
    digitalWriteFast(RST_PIN, HIGH);
}

uint16_t SST39LF401C::word_read(uint32_t address)
{
    uint16_t bitmask;
    uint16_t dataBuffer = 0;

    prepareIO_Read(); // set the pinModes to input

    digitalWriteFast(CE_PIN, LOW); // when CE or OE is low the IO lines are no longer high-z
    digitalWriteFast(WE_PIN, HIGH); // disable writing to the EEPROM

    pushAddress(address);

    digitalWriteFast(OE_PIN, LOW);

    bitmask = 0x0001;
    for (int i = 0; i < DQ_BUS_WIDTH; i++) {
        if (digitalRead(DQ_pins[i]))
            dataBuffer |= bitmask;

        bitmask = bitmask << 1;
    }

    digitalWriteFast(CE_PIN, HIGH); // standby mode
    digitalWriteFast(OE_PIN, HIGH);

    return dataBuffer;
}

// void function with device state consequences
void SST39LF401C::command_write_cycle(uint32_t address, uint16_t data)
{
    pushAddress(address);
    digitalWriteFast(WE_PIN, LOW);
    pushData(data);
    digitalWriteFast(WE_PIN, HIGH);
}

void SST39LF401C::fast_word_program(uint32_t address, uint16_t data)
{
    command_write_cycle(0x0555, 0x00AA);
    command_write_cycle(0x02AA, 0x0055);
    command_write_cycle(0x0555, 0x00A0);
    command_write_cycle(address, data);

    while (!digitalRead(RYBY_PIN));
}

void SST39LF401C::word_program(uint32_t address, uint16_t data)
{
    digitalWriteFast(OE_PIN, HIGH);
    digitalWriteFast(CE_PIN, LOW);
    prepareIO_Write();

    fast_word_program(address, data);

    prepareIO_Read();
    digitalWriteFast(CE_PIN, HIGH);
    digitalWriteFast(OE_PIN, LOW);
}

void SST39LF401C::bulk_program(uint32_t start_address, uint32_t end_address, uint16_t data)
{
    digitalWriteFast(OE_PIN, HIGH);
    digitalWriteFast(CE_PIN, LOW);
    prepareIO_Write();

    while (start_address < end_address) {
        fast_word_program(start_address++, data);
    }

    prepareIO_Read();
    digitalWriteFast(CE_PIN, HIGH);
    digitalWriteFast(OE_PIN, LOW);
}

void SST39LF401C::sector_erase(uint32_t address)
{
    digitalWriteFast(CE_PIN, LOW);
    digitalWriteFast(OE_PIN, HIGH);
    prepareIO_Write();

    command_write_cycle(0x0555, 0x00AA);
    command_write_cycle(0x02AA, 0x0055);
    command_write_cycle(0x0555, 0x0080);
    command_write_cycle(0x0555, 0x00AA);
    command_write_cycle(0x02AA, 0x0055);
    command_write_cycle(address, 0x0050);

    while (!digitalRead(RYBY_PIN));

    prepareIO_Read();
    digitalWriteFast(OE_PIN, LOW);
    digitalWriteFast(CE_PIN, HIGH);
}

void SST39LF401C::sector_partial_erase(uint32_t address, unsigned int time_us)
{
    digitalWriteFast(CE_PIN, LOW);
    digitalWriteFast(OE_PIN, HIGH);
    prepareIO_Write();

    // Sector ERASE Sequence
    command_write_cycle(0x0555, 0x00AA);
    command_write_cycle(0x02AA, 0x0055);
    command_write_cycle(0x0555, 0x0080);
    command_write_cycle(0x0555, 0x00AA);
    command_write_cycle(0x02AA, 0x0055);
    command_write_cycle(address, 0x0050);

    delayMicroseconds(time_us);

    digitalWriteFast(RST_PIN, LOW);
    delayMicroseconds(1);
    digitalWriteFast(RST_PIN, HIGH);
    
    prepareIO_Read();
    digitalWriteFast(OE_PIN, LOW);
    digitalWriteFast(CE_PIN, HIGH);
}

#define SECTOR_WORDS 2048
void SST39LF401C::sector_stress(uint32_t sector_address, uint32_t count)
// Leaves sector in a written state
{
    while (count) {
        sector_erase(sector_address);
        bulk_program(sector_address, sector_address + SECTOR_WORDS, 0x0000);
        count--;
    }
}

uint32_t SST39LF401C::get_block_start(uint8_t block)
{
    return block_start_table[block];
}

uint32_t SST39LF401C::get_block_end(uint8_t block)
{
    return block_end_table[block];
}
