#ifndef __DELAY_H__
#define __DELAY_H__

#include <REGX52.H>

#include <stdint.h>

#define CRYSTAL_FREQUENCY   11.0592
#define FS                  (1 / (CRYSTAL_FREQUENCY / 12))

void delay_ms(uint16_t t);

#endif
