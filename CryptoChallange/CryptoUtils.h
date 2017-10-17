//
//  Crypto_Utils.h
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 25/04/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#ifndef __CryptoChallenge__CryptoUtils__
#define __CryptoChallenge__CryptoUtils__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NO_SUBSTREAM -1
#define NO_HEX_VALUE 17
#define MAXLINE 400

/*  BYTESTREAM STUFF */

// just a nicer-looking alias..
typedef uint8_t byte;

unsigned char* b;
int l;

// the fundamental data structure used for internally storing and manipulating
// streams of bytes. Could be printable text, could be unprintable garbage
typedef struct bytestream {
	byte *bytes;
	size_t length;
} bytestream;

// allocates an empty byte_stream with a fixed length
bytestream bs_alloc(size_t length);

// creates a bytestream from a byte array
bytestream bs_make(byte *bytes, size_t length);

// creates a bytestream from a char array
bytestream bs_from_chars(char *string);

// get a substream from a bytestream
bytestream sub_stream(bytestream bs, int start, int finish);

// print the bytes in a bytestream
void print_bs(bytestream bs);

// return the index of the furst occurence of the substring needle
int strmnstrm(bytestream haystack, bytestream needle, size_t length);

/*  HEX STUFF  */

// OK, so there is a asymmetry in the en/decode declarations here, but this is
// well founded. Hex data can always be stored in a char*, but decoded data is
// arbitrary, so a bytestream is more robust. For full symmetry, simply convert
// before calling!

// encode arbitrary data as hex string
char *hex_encode(const bytestream data);

// decode hex data to a byte stream
bytestream hex_decode(const char *hex_string);

// 10 -> 'f'  etc.
char hex_to_char(int hex);

// 'f' -> 10  etc.
byte char_to_hex(char c);

/*   FILEREADING STUFF   */
char *readfile_skip_newline(char *infile, size_t lines, size_t linelength);
bytestream *hex_decode_lines(const char *filename, int lines);

#endif /* defined(__CryptoChallange__CryptoUtils__) */