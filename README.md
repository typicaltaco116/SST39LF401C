# SST39LF401C NOR Flash IC Arduino Interface Library
This library utilizes C++ macros for handling pin assignment for performance. The default pin assignments can be viewed in the src/SST39LF401C_pin_assignments.h header file.

### Custom pin assignment
In order to change the pin assignments used by the class instantiates in a particular implementation file, the ADR_PIN_x, DQ_pin_x, WE_PIN, OE_PIN, CE_PIN, RYBY_PIN, RST_PIN, or WP_PIN macros should be defined before the header file inclusion.

```C
#define WE_PIN 16
#include <SST39LF401C.h>
```

### Arduino supported targets
- Arduino DUE (AT91SAM3X8E)

More Arduino devices could easily be implemented with updated digitalWriteFast() function implementation for other devices.
