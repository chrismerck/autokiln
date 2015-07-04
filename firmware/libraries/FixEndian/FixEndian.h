#ifndef __FIX_ENDIAN_H__
#define __FIX_ENDIAN_H__

#include<stdint.h>

uint64_t hton64(uint64_t x);
void hton64(uint64_t * x);
uint64_t ntoh64(uint64_t x);
void ntoh64(uint64_t * x);
uint32_t hton32(uint32_t x);
void hton32(uint32_t * x);
uint32_t ntoh32(uint32_t x);
void ntoh32(uint32_t * x);
uint16_t hton16(uint16_t x);
void hton16(uint16_t * x);
uint16_t ntoh16(uint16_t x);
void ntoh16(uint16_t * x);

#endif // __FIX_ENDIAN_H__
