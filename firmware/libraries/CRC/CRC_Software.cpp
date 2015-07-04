#include "CRC.h"
#include<cstring>
#include<stdlib.h>
#define SYS_CURRENT_SUBSYS SYS_SUBSYS_CRC
#include"Sys.h"

/******************************************************************************/
/*                             Start of crcmodel.h                            */
/******************************************************************************/
/*                                                                            */
/* Author : Ross Williams (ross@guest.adelaide.edu.au.).                      */
/* Date   : 3 June 1993.                                                      */
/* Status : Public domain.                                                    */
/*                                                                            */
/* Description : This is the header (.h) file for the reference               */
/* implementation of the Rocksoft^tm Model CRC Algorithm. For more            */
/* information on the Rocksoft^tm Model CRC Algorithm, see the document       */
/* titled "A Painless Guide to CRC Error Detection Algorithms" by Ross        */
/* Williams (ross@guest.adelaide.edu.au.). This document is likely to be in   */
/* "ftp.adelaide.edu.au/pub/rocksoft".                                        */
/*                                                                            */
/* Note: Rocksoft is a trademark of Rocksoft Pty Ltd, Adelaide, Australia.    */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* How to Use This Package                                                    */
/* -----------------------                                                    */
/* Step 1: Declare a variable of type cm_t. Declare another variable          */
/*         (p_cm say) of type p_cm_t and initialize it to point to the first  */
/*         variable (e.g. p_cm_t p_cm = &cm_t).                               */
/*                                                                            */
/* Step 2: Assign values to the parameter fields of the structure.            */
/*         If you don't know what to assign, see the document cited earlier.  */
/*         For example:                                                       */
/*            p_cm->cm_width = 16;                                            */
/*            p_cm->cm_poly  = 0x8005L;                                       */
/*            p_cm->cm_init  = 0L;                                            */
/*            p_cm->cm_refin = TRUE;                                          */
/*            p_cm->cm_refot = TRUE;                                          */
/*            p_cm->cm_xorot = 0L;                                            */
/*         Note: Poly is specified without its top bit (18005 becomes 8005).  */
/*         Note: Width is one bit less than the raw poly width.               */
/*                                                                            */
/* Step 3: Initialize the instance with a call cm_ini(p_cm);                  */
/*                                                                            */
/* Step 4: Process zero or more message bytes by placing zero or more         */
/*         successive calls to cm_nxt. Example: cm_nxt(p_cm,ch);              */
/*                                                                            */
/* Step 5: Extract the CRC value at any time by calling crc = cm_crc(p_cm);   */
/*         If the CRC is a 16-bit value, it will be in the bottom 16 bits.    */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* Design Notes                                                               */
/* ------------                                                               */
/* PORTABILITY: This package has been coded very conservatively so that       */
/* it will run on as many machines as possible. For example, all external     */
/* identifiers have been restricted to 6 characters and all internal ones to  */
/* 8 characters. The prefix cm (for Crc Model) is used as an attempt to avoid */
/* namespace collisions. This package is endian independent.                  */
/*                                                                            */
/* EFFICIENCY: This package (and its interface) is not designed for           */
/* speed. The purpose of this package is to act as a well-defined reference   */
/* model for the specification of CRC algorithms. If you want speed, cook up  */
/* a specific table-driven implementation as described in the document cited  */
/* above. This package is designed for validation only; if you have found or  */
/* implemented a CRC algorithm and wish to describe it as a set of parameters */
/* to the Rocksoft^tm Model CRC Algorithm, your CRC algorithm implementation  */
/* should behave identically to this package under those parameters.          */
/*                                                                            */
/******************************************************************************/

/* The following #ifndef encloses this entire */
/* header file, rendering it indempotent.     */
#ifndef CM_DONE
#define CM_DONE

/******************************************************************************/

/* The following definitions are extracted from my style header file which    */
/* would be cumbersome to distribute with this package. The DONE_STYLE is the */
/* idempotence symbol used in my style header file.                           */

#ifndef DONE_STYLE

typedef unsigned long   ulong;
//typedef unsigned        bool;
typedef unsigned char * p_ubyte_;

#ifndef TRUE
#define FALSE 0
#define TRUE  1
#endif

/* Change to the second definition if you don't have prototypes. */
#define P_(A) A
/* #define P_(A) () */

/* Uncomment this definition if you don't have void. */
/* typedef int void; */

#endif

/******************************************************************************/

/* CRC Model Abstract Type */
/* ----------------------- */
/* The following type stores the context of an executing instance of the  */
/* model algorithm. Most of the fields are model parameters which must be */
/* set before the first initializing call to cm_ini.                      */
typedef struct
  {
   int   cm_width;   /* Parameter: Width in bits [8,32].       */
   ulong cm_poly;    /* Parameter: The algorithm's polynomial. */
   ulong cm_init;    /* Parameter: Initial register value.     */
   bool  cm_refin;   /* Parameter: Reflect input bytes?        */
   bool  cm_refot;   /* Parameter: Reflect output CRC?         */
   ulong cm_xorot;   /* Parameter: XOR this to output CRC.     */

   ulong cm_reg;     /* Context: Context during execution.     */
  } cm_t;
typedef cm_t *p_cm_t;

/******************************************************************************/

/* Functions That Implement The Model */
/* ---------------------------------- */
/* The following functions animate the cm_t abstraction. */

void cm_ini (p_cm_t p_cm);
/* Initializes the argument CRC model instance.          */
/* All parameter fields must be set before calling this. */

void cm_nxt (p_cm_t p_cm,int ch);
/* Processes a single message byte [0,255]. */

void cm_blk (p_cm_t p_cm,p_ubyte_ blk_adr,ulong blk_len);
/* Processes a block of message bytes. */

ulong cm_crc (p_cm_t p_cm);
/* Returns the CRC value for the message bytes processed so far. */

/******************************************************************************/

/* Functions For Table Calculation */
/* ------------------------------- */
/* The following function can be used to calculate a CRC lookup table.        */
/* It can also be used at run-time to create or check static tables.          */

ulong cm_tab (p_cm_t p_cm,int index);
/* Returns the i'th entry for the lookup table for the specified algorithm.   */
/* The function examines the fields cm_width, cm_poly, cm_refin, and the      */
/* argument table index in the range [0,255] and returns the table entry in   */
/* the bottom cm_width bytes of the return value.                             */

/******************************************************************************/

/* End of the header file idempotence #ifndef */
#endif

/******************************************************************************/
/*                             End of crcmodel.h                              */
/******************************************************************************/














/******************************************************************************/
/*                             Start of crcmodel.c                            */
/******************************************************************************/
/*                                                                            */
/* Author : Ross Williams (ross@guest.adelaide.edu.au.).                      */
/* Date   : 3 June 1993.                                                      */
/* Status : Public domain.                                                    */
/*                                                                            */
/* Description : This is the implementation (.c) file for the reference       */
/* implementation of the Rocksoft^tm Model CRC Algorithm. For more            */
/* information on the Rocksoft^tm Model CRC Algorithm, see the document       */
/* titled "A Painless Guide to CRC Error Detection Algorithms" by Ross        */
/* Williams (ross@guest.adelaide.edu.au.). This document is likely to be in   */
/* "ftp.adelaide.edu.au/pub/rocksoft".                                        */
/*                                                                            */
/* Note: Rocksoft is a trademark of Rocksoft Pty Ltd, Adelaide, Australia.    */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/* Implementation Notes                                                       */
/* --------------------                                                       */
/* To avoid inconsistencies, the specification of each function is not echoed */
/* here. See the header file for a description of these functions.            */
/* This package is light on checking because I want to keep it short and      */
/* simple and portable (i.e. it would be too messy to distribute my entire    */
/* C culture (e.g. assertions package) with this package.                     */
/*                                                                            */
/******************************************************************************/

//#include "crcmodel.h"

/******************************************************************************/

/* The following definitions make the code more readable. */

#define BITMASK(X) (1L << (X))
#define MASK32 0xFFFFFFFFL
#define LOCAL static

/******************************************************************************/

LOCAL ulong reflect (ulong v,int b)
/* Returns the value v with the bottom b [0,32] bits reflected. */
/* Example: reflect(0x3e23L,3) == 0x3e26                        */
{
 int   i;
 ulong t = v;
 for (i=0; i<b; i++)
   {
    if (t & 1L)
       v|=  BITMASK((b-1)-i);
    else
       v&= ~BITMASK((b-1)-i);
    t>>=1;
   }
 return v;
}

/******************************************************************************/

LOCAL ulong widmask (p_cm_t p_cm)
/* Returns a longword whose value is (2^p_cm->cm_width)-1.     */
/* The trick is to do this portably (e.g. without doing <<32). */
{
 return (((1L<<(p_cm->cm_width-1))-1L)<<1)|1L;
}

/******************************************************************************/

void cm_ini (p_cm_t p_cm)
{
 p_cm->cm_reg = p_cm->cm_init;
}

/******************************************************************************/

void cm_nxt (p_cm_t p_cm,int ch)
{
 int   i;
 ulong uch  = (ulong) ch;
 ulong topbit = BITMASK(p_cm->cm_width-1);

 if (p_cm->cm_refin) uch = reflect(uch,8);
 p_cm->cm_reg ^= (uch << (p_cm->cm_width-8));
 for (i=0; i<8; i++)
   {
    if (p_cm->cm_reg & topbit)
       p_cm->cm_reg = (p_cm->cm_reg << 1) ^ p_cm->cm_poly;
    else
       p_cm->cm_reg <<= 1;
    p_cm->cm_reg &= widmask(p_cm);
   }
}

/******************************************************************************/

void cm_blk (p_cm_t p_cm,p_ubyte_ blk_adr, ulong blk_len)
{
 while (blk_len--) cm_nxt(p_cm,*blk_adr++);
}

/******************************************************************************/

ulong cm_crc (p_cm_t p_cm)
{
 if (p_cm->cm_refot)
    return p_cm->cm_xorot ^ reflect(p_cm->cm_reg,p_cm->cm_width);
 else
    return p_cm->cm_xorot ^ p_cm->cm_reg;
}

/******************************************************************************/

ulong cm_tab (p_cm_t p_cm,int index)
{
 int   i;
 ulong r;
 ulong topbit = BITMASK(p_cm->cm_width-1);
 ulong inbyte = (ulong) index;

 if (p_cm->cm_refin) inbyte = reflect(inbyte,8);
 r = inbyte << (p_cm->cm_width-8);
 for (i=0; i<8; i++)
    if (r & topbit)
       r = (r << 1) ^ p_cm->cm_poly;
    else
       r<<=1;
 if (p_cm->cm_refin) r = reflect(r,p_cm->cm_width);
 return r & widmask(p_cm);
}

/******************************************************************************/
/*                             End of crcmodel.c                              */
/******************************************************************************/

typedef uint32_t crc32_t;

//////////////////////////////////////////////////////////////////////////
//
//  FUNCTION NAME :
//      CRC_CalcBlockCRC
//
//  AUTHOR:
//     Thanks for swhite of st.com forums
//
//  FUNCTIONAL DESCRIPTION :
//      Calculate a CRC the same way as the STM32F10x hardware generator.
//
//
//  FORMAL INPUT PARAMETERS :
//      buffer - pointer to series of 32-bit words (NOT bytes).
//      words  - count of 32-bit words to do.
//
//
//  FORMAL OUTPUT PARAMETERS :
//      None
//
//
//  RETURN VALUE :
//      32-bit CRC value as per the STM32F10x CRC generator.
//
//
//  IMPLICIT INPUTS AND OUTPUTS :
//      None
//
//
//  IMPORTED FUNCTIONS AND MACROS :
//      cm_ini(), cm_nxt(), cm_crc()
//
//
//////////////////////////////////////////////////////////////////////////

typedef uint32_t ulword;
typedef uint8_t ubyte;

static      crc32_t                     CRC_CalcBlockCRC(ulword *buffer, ulword words)
{
cm_t        crc_model;
ulword      word_to_do;
ubyte       byte_to_do;
int         i;

    // Values for the STM32F generator.

    crc_model.cm_width = 32;            // 32-bit CRC
    crc_model.cm_poly  = 0x04C11DB7;    // CRC-32 polynomial
    crc_model.cm_init  = 0xFFFFFFFF;    // CRC initialized to 1's
    crc_model.cm_refin = FALSE;         // CRC calculated MSB first
    crc_model.cm_refot = FALSE;         // Final result is not bit-reversed
    crc_model.cm_xorot = 0x00000000;    // Final result XOR'ed with this

    cm_ini(&crc_model);

    while (words--)
    {
        // The STM32F10x hardware does 32-bit words at a time!!!

        word_to_do = *buffer++;

        // Do all bytes in the 32-bit word.

        for (i = 0; i < sizeof(word_to_do); i++)
        {
            // We calculate a *byte* at a time. If the CRC is MSB first we
            // do the next MS byte and vica-versa.

            if (crc_model.cm_refin == FALSE)
            {
                // MSB first. Do the next MS byte.

                byte_to_do = (ubyte) ((word_to_do & 0xFF000000) >> 24);
                word_to_do <<= 8;
            }
            else
            {
                // LSB first. Do the next LS byte.

                byte_to_do = (ubyte) (word_to_do & 0x000000FF);
                word_to_do >>= 8;
            }

            cm_nxt(&crc_model, byte_to_do);
        }
    }

    // Return the final result.

    return (cm_crc(&crc_model));
}


uint32_t CRC32(const uint8_t * buf, uint32_t len)
{
  uint32_t crc;
  /**
   * Warning: We wastefully allocate a new buffer
   *  to allow for padding when len is not multiple of 4
   * A better solution would be to use an underlying
   *  CRC function that permits stepping, so we can
   *  manually add the last word zero-padded as needed.
   **/
  uint32_t newlen = ((len+3)/4)*4; // round up to nearest 4
  uint8_t * newbuf = (uint8_t*)malloc(newlen);
  uint32_t flen = (len/4)*4;
  memset(newbuf,0,newlen);
  memcpy(newbuf,buf,flen); // copy except any partial trailing word
  // copy partial trailing word
  //  we do this to get endianness right
  for (int i = flen; i<len; i++)
  {
    //newbuf[i - (len%4) + 4] = buf[i];
    newbuf[i] = buf[i];
  }
  SysDebugHexdump(buf,len,"buf (len=%d) ",len);
  SysDebugHexdump(newbuf,newlen,"newbuf (newlen=%d) ",newlen);
  crc = CRC_CalcBlockCRC((uint32_t*)newbuf, newlen/4);
  free (newbuf);
  return crc;
}

