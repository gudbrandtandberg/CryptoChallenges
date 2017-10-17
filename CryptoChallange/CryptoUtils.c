//
//  Crypto_Utils.c
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 25/04/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "CryptoUtils.h"

bytestream bs_alloc(size_t length) {
	bytestream bs;
	bs.bytes = (byte *)malloc(length);
	bs.length = length;
	return bs;
}

bytestream bs_make(byte *bytes, size_t length) {
	bytestream bs = bs_alloc(length);
	bs.bytes = bytes;
	return bs;
}

bytestream bs_from_chars(char *str) {
	size_t len = strlen(str);
	return bs_make((byte *)str, len);
}

bytestream sub_stream(bytestream bs, int start, int finish) {
	int len = finish - start + 1;
	byte *bytes = malloc(len);
	
	if (finish > bs.length) return bs_alloc(0);
	memcpy(bytes, bs.bytes + start, len);
	
	return bs_make(bytes, len);
}

void print_bs(bytestream bs) {
	//printf("Printing bytestream of length %lu:\n", bs.length);
	for (int i = 0; i < bs.length; i++) {
		char b = (char) bs.bytes[i];
		if (isprint(b) || isspace(b)) {
			printf("%c", b);
		} else {
			printf(".");
		}
	}
	printf("\n");
}

int strmnstrm(bytestream haystack, bytestream needle, size_t length) {
	size_t needle_length = needle.length;
	int i, j;
	
	for (i = 0; i <= length; i++) {
		if (i > (haystack.length - needle_length)) return NO_SUBSTREAM;
		j = 0;
		while ((haystack.bytes[i+j] == needle.bytes[j]) && j < needle_length) {
			j++;
		}
		if (j == needle_length) {
			return i;
		}
	}
	
	return NO_SUBSTREAM;
}

static byte alphamap[] = {10, 11, 12, 13, 14, 15};
static char *hex_symbols = "0123456789abcdef";

byte char_to_hex(char c) {
	//char is 0 to 9 or a to f or A to F
	int ret;
	
	if (c >= '0' && c <= '9') {
		ret = c - '0';
	} else if (c >= 'a' && c <= 'f'){
		ret = alphamap[c - 'a'];
	} else if (c >= 'A' && c <= 'F') {
		ret = alphamap[c - 'A'];
	} else {
		printf("Attempting to convert non-hex convertible character\n");
		ret = NO_HEX_VALUE;
	}
	
	return ret;
}

char hex_to_char(int hex) {
	return hex_symbols[hex];
}

char *hex_encode(const bytestream data) {

	size_t output_length = 2 * data.length;
	
	int fourBits = 15;
	int i = 0, j = 0;

	char *hex_string = malloc(output_length + 1);
	
	while (i < output_length) {
		
		byte next_byte = data.bytes[j++];
		
		hex_string[i++] = hex_to_char((next_byte >> 4) & fourBits);
		hex_string[i++] = hex_to_char(next_byte & fourBits);
		
	} hex_string[i] = '\0';
	
	return hex_string;
}

bytestream hex_decode(const char *hex_string) {
	size_t input_length = strlen(hex_string);
	size_t output_length = input_length / 2;
	byte *output_bytes = malloc(output_length);

	int i = 0, j = 0;
	byte dig1, dig2;
	
	while (i < input_length) {
		if ((dig1 = char_to_hex(hex_string[i++])) == NO_HEX_VALUE){}
		if ((dig2 = char_to_hex(hex_string[i++])) == NO_HEX_VALUE){}
		
		output_bytes[j++] = 16 * dig1 + dig2;
	}
	
	return bs_make(output_bytes, output_length);
}

char *readfile_skip_newline(char *infile, size_t lines, size_t linelength) {
	FILE *fp = fopen(infile, "rb");
	size_t file_length = (linelength+1) * lines;
	char c, *file_contents = malloc(file_length + 1);
	int i = 0;
	
	while ((c = fgetc(fp)) != EOF) {
		if (c != '\n') {
			file_contents[i++] = c;
		}
	}
	return file_contents;
}

bytestream *hex_decode_lines(const char *filename, int lines) {
	FILE *infile = fopen(filename, "rb");
	int i = 0;
	char line[MAXLINE];
	
	bytestream *decoded_lines = (bytestream *)malloc(lines * sizeof(bytestream));
	
	while (i < lines) {
		
		fgets(line, MAXLINE, infile);
		line[strlen(line) - 1] = '\0';  //strip final newline
		
		decoded_lines[i++] = hex_decode(line);
	}
	
	return decoded_lines;
}
