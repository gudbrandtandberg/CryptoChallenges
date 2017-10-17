//
//  challenge10.c
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 14/05/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "CryptoChallenges.h"
#include "OpenSSLFunctions.h"

/*						___10. IMPLEMENT CBC MODE___
 *
 * CBC mode is a block cipher mode that allows us to encrypt irregularly-sized
 * messages, despite the fact that a block cipher natively only transforms
 * individual blocks.
 *
 * In CBC mode, each ciphertext block is added to the next plaintext block
 * before the next call to the cipher core.
 *
 * The first plaintext block, which has no associated previous ciphertext block,
 * is added to a "fake 0th ciphertext block" called the initialization vector.
 *
 * Implement CBC mode by hand by taking the ECB function you wrote earlier,
 * making it encrypt instead of decrypt (verify this by decrypting whatever you
 * encrypt to test), and using your XOR function from the previous exercise to
 * combine them.
 *
 * The file here (ex10text.txt) is intelligible (somewhat) when CBC decrypted
 * against "YELLOW SUBMARINE" with an IV of all ASCII 0 (\x00\x00\x00 &c)
 */

int main(int argc, char **argv) {
	
	bytestream data = base64_decode(readfile_skip_newline("10.txt", 64, 60));
	
	unsigned char *password = (unsigned char *)"YELLOW SUBMARINE";
	unsigned char *iv = (unsigned char *)"\x00\x00\x00\x00\x00\x00\x00\x00"
										 "\x00\x00\x00\x00\x00\x00\x00\x00";
	
	bytestream decrypted = aes_128_cbc_decrypt(data, password, iv);
	print_bs(decrypted);

//  TESTS
//	bytestream plaintext = bs_from_chars("Hi this is a string of arbitrary len"
//										 "gth. It definitely has a length grea"
//										 "ter than sixteen, and not a multiple"
//										 " of sixteen");
//	
//	printf("Input length: %lu\n", plaintext.length);
//	
//	bytestream encrypted = aes_128_cbc_encrypt(plaintext, password, iv);
//	print_bs(encrypted);
//	
//	bytestream decrypted = aes_128_cbc_decrypt(encrypted, password, iv);
//	print_bs(decrypted);
	
}



