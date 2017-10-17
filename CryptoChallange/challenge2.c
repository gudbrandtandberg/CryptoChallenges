//
//  challenge2.c
//  CryptoChallange
//
//  Created by Gudbrand Tandberg on 24/04/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "CryptoChallenges.h"

/*							___2. FIXED XOR___
 *
 * Write a function that takes two equal-length buffers
 * and produces their XOR combination.
 *
 * If your function works properly, then when you feed it the string:
 *
 * 1c0111001f010100061a024b53535009181c
 * ... after hex decoding, and when XOR'd against:
 *
 * 686974207468652062756c6c277320657965
 * ... should produce:
 *
 * 746865206b696420646f6e277420706c6179
 */

int main(int argc, char **argv) {
	
	bytestream str1 = hex_decode("1c0111001f010100061a024b53535009181c");
	bytestream str2 = hex_decode("686974207468652062756c6c277320657965");
	
	printf("Xor'ed strings:\n");
	printf("%s\n", hex_encode(fixed_xor(str1, str2)));
}
