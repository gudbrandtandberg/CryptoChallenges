//
//  challenge5.c
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 24/04/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "CryptoChallenges.h"

/*					___5. IMPLEMENT REPEATING-KEY XOR___
 *
 * Here is the opening stanza of an important work of the English language:
 *
 * Burning 'em, if you ain't quick and nimble
 * I go crazy when I hear a cymbal
 *
 * Encrypt it, under the key "ICE", using repeating-key XOR.
 *
 * In repeating-key XOR, you'll sequentially apply each byte of the key;
 * the first byte of plaintext will be XOR'd against I, the next C, 
 * the next E, then I again for the 4th byte, and so on.
 *
 * It should come out to:
 *
 * 0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a2622632427276527
 * 2a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f
 *
 * Encrypt a bunch of stuff using your repeating-key XOR function.
 * Encrypt your mail. Encrypt your password file. Your .sig file. 
 * Get a feel for it. I promise, we aren't wasting your time with this.
 */

int main(int argc, char *argv[]) {
	
	bytestream secret = bs_from_chars("Burning 'em, if you ain't quick and nim"
									  "ble\nI go crazy when I hear a cymbal");

	bytestream password = bs_from_chars("ICE");
	
	bytestream encrypted = repeating_key_xor_encrypt(secret, password);
	
	printf("Encrypted message: %s\n", hex_encode(encrypted));
}


