//
//  challenge1.c
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 24/04/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "CryptoChallenges.h"

/*                  ___1. CONVERT HEX TO BASE64___
 * The string:
 *
 * 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
 * Should produce:
 *
 * SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
 *
 * So go ahead and make that happen. You'll need to use this code
 * for the rest of the exercises.
 *
 * Cryptopals Rule
 * Always operate on raw bytes, never on encoded strings. 
 * Only use hex and base64 for pretty-printing.
 */

'h' 'e' 'i' '\0' 'i'

int main(int argc, char **argv) {
	
	const char *input = "49276d206b696c6c696e6720796f757220627261696e206c"
	"696b65206120706f69736f6e6f7573206d757368726f6f6d";
	
	bytestream hex_decoded = hex_decode(input);
	
	printf("Hex decoded: \n");
	print_bs(hex_decoded);
	
	printf("base64 encoded: \n");
	printf("%s\n", base64_encode(hex_decoded));
	
}

