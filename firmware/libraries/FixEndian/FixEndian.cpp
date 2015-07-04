/**
 * FixEndian.cpp
 * Endianness Conversion Utilities
 * Copyright (c) 2014,2015 Chris Merck
 **/

#include"FixEndian.h"

void hton64(uint64_t * x)
{
  *x = hton64(*x);
}
uint64_t hton64(const uint64_t x)
{
  uint64_t t = x;
  uint8_t * a = (uint8_t*)&t;
  a[0] = x>>(8*7);
  a[1] = x>>(8*6);
  a[2] = x>>(8*5);
  a[3] = x>>(8*4);
  a[4] = x>>(8*3);
  a[5] = x>>(8*2);
  a[6] = x>>(8*1);
  a[7] = x>>(8*0);
  return t;
}

void ntoh64(uint64_t * x)
{
  *x = ntoh64(*x);
}
uint64_t ntoh64(const uint64_t x)
{
  const uint8_t * a = (const uint8_t *)&x;
  return (((uint64_t)a[0])<<(8*7)) 
    + (((uint64_t)a[1])<<(8*6))
    + (((uint64_t)a[2])<<(8*5))
    + (((uint64_t)a[3])<<(8*4)) 
    + (((uint64_t)a[4])<<(8*3)) 
    + (((uint64_t)a[5])<<(8*2)) 
    + (((uint64_t)a[6])<<(8*1)) 
    + (((uint16_t)a[7])<<(8*0));
}

void hton32(uint32_t * x)
{
  *x = hton32(*x);
}
uint32_t hton32(const uint32_t x)
{
  uint32_t t = x;
  uint8_t * a = (uint8_t*)&t;
  a[0] = x>>(8*3);
  a[1] = x>>(8*2);
  a[2] = x>>(8*1);
  a[3] = x>>(8*0);
  return t;
}

void ntoh32(uint32_t * x)
{
  *x = ntoh32(*x);
}
uint32_t ntoh32(const uint32_t x)
{
  const uint8_t * a = (const uint8_t *)&x;
  return (a[0]<<(8*3)) + (a[1]<<(8*2)) + (a[2]<<(8*1)) + (a[3]<<(8*0));
}

void hton16(uint16_t * x)
{
  *x = hton16(*x);
}
uint16_t hton16(const uint16_t x)
{
  uint16_t t = x;
  uint8_t * a = (uint8_t*)&t;
  a[0] = x>>(8*1);
  a[1] = x>>(8*0);
  return t;
}

void ntoh16(uint16_t * x)
{
  *x = ntoh16(*x);
}
uint16_t ntoh16(const uint16_t x)
{
  uint8_t * a = (uint8_t*)&x;
  return (a[0]<<(8*1)) + (a[1]<<(8*0));
}

