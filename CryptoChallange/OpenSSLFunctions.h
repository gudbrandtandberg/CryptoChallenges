//
//  OpenSSLFunctions.h
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 14/05/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#ifndef __CryptoChallenge__OpenSSLFunctions__
#define __CryptoChallenge__OpenSSLFunctions__

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "CryptoChallenges.h"

//7 - AES in ECB mode
bytestream aes_128_ecb_encrypt(bytestream plaintext, unsigned char *password);
bytestream aes_128_ecb_encrypt_block(bytestream block,
									 unsigned char *password);
bytestream aes_128_ecb_decrypt(bytestream cipher, unsigned char *password);
bytestream aes_128_ecb_decrypt_block(bytestream cipher_block,
									 unsigned char *password);

//10 - AES in CBC mode
bytestream aes_128_cbc_encrypt(bytestream plaintext,
							   unsigned char *password,
							   unsigned char *iv);

bytestream aes_128_cbc_decrypt(bytestream ciphertext,
							   unsigned char *password,
							   unsigned char *iv);

unsigned char *random_aes_key();
bytestream encryption_oracle(bytestream input);
void detect_mode(bytestream (*oracle)(bytestream));

#endif /* defined(__CryptoChallenge__OpenSSLFunctions__) */

