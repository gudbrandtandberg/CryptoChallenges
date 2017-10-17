//
//  Set1.h
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 11/04/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#ifndef CryptoChallenge_CryptoChallenges_h
#define CryptoChallenge_CryptoChallenges_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "CryptoUtils.h"

//main todo list:
//TODO: comment and clean all code nicely and consistently
//TODO: update README
//TODO: complete and test ecb/cbc en/de-cryption functions (use padding)
//

//1 - encode data with base64 scheme
char *base64_encode(const bytestream data);
bytestream base64_decode(const char *base64);

//2 - XOR two equal length strings
bytestream fixed_xor(bytestream bs1, bytestream bs2);

//3 - single byte XOR-cipher
bytestream single_byte_xor_crack(bytestream cipher, int *key);
bytestream single_byte_xor(bytestream input, byte c);
bytestream find_most_english(bytestream *candidates,
							 int numCandidates, int *index);

//4 - detect single byte XOR-cipher
bytestream find_single_byte_xor(bytestream *candidates, int num_candidates,
								int *key);

//5 - implement repeating-key XOR
bytestream repeating_key_xor_encrypt(bytestream secret, bytestream password);

//6 - break repeating-key XOR
bytestream break_repeating_key_xor(bytestream cipher, bytestream *password);

//8 - Detect AES in ECB mode
int has_repeating_blocks(bytestream data);

//9 - Implement PKCS#7 padding scheme
int pkcs_7_pad(bytestream *bs_to_pad, size_t blocksize);



#endif
