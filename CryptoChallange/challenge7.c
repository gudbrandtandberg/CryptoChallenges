//
//  challenge7.c
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 12/05/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "CryptoChallenges.h"
#include "OpenSSLFunctions.h"

/*							___7. AES IN ECB MODE___
 *
 * The Base64-encoded content in this file has been encrypted via AES-128 in ECB
 * mode under the key
 *
 * "YELLOW SUBMARINE".
 *
 * (case-sensitive, without the quotes; exactly 16 characters; I like 
 * "YELLOW SUBMARINE" because it's exactly 16 bytes long, and now you do too).
 *
 *  Decrypt it. You know the key, after all.
 *
 *  Easiest way: use OpenSSL::Cipher and give it AES-128-ECB as the cipher.
 */

int main(int argc, char **argv) {
	
	char *base64 = readfile_skip_newline("7.txt", 64, 60);
	bytestream cipher = base64_decode(base64);  // cipher has length 2880 =
												// 180blocks * 16bytes per block
	
	// 128 bit password:
	unsigned char *password = (unsigned char *)"YELLOW SUBMARINE";
	bytestream plaintext = aes_128_ecb_decrypt(cipher, password);  //TODO: fix!
	
	print_bs(plaintext);
	
}

