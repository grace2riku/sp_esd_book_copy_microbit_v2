#include "MicroBit.h"

#ifndef MB_NEXT_TESTS_H
#define MB_NEXT_TESTS_H

#define MICROBIT_UBIT_AS_STATIC_OBJECT

#ifdef MICROBIT_UBIT_AS_STATIC_OBJECT
extern MicroBit uBit;
#else
extern MicroBit& uBit;
#endif

void start_flashLed();

#endif
