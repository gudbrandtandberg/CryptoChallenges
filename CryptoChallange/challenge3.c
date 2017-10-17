//
//  challenge3.c
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 24/04/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "CryptoChallenges.h"

/*					___3. SINGLE-BYTE XOR CIPHER___
 *
 * The hex encoded string:
 *
 * 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
 * ... has been XOR'd against a single character. 
 * Find the key, decrypt the message.
 *
 * You can do this by hand. But don't: write code to do it for you.
 *
 * How? Devise some method for "scoring" a piece of English plaintext. 
 * Character frequency is a good metric. Evaluate each output and choose
 * the one with the best score.
 */

int main(int argc, char **argv) {
	
	bytestream cipher = hex_decode("1b37373331363f78151b7f2b783431333d"
								   "78397828372d363c78373e783a393b3736");
	int key;
	bytestream plain = single_byte_xor_crack(cipher, &key);
	
	printf("Key: '%c' \nPlaintext: ", key);
	print_bs(plain);
}