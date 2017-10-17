//
//  main.c
//  challenge11
//
//  Created by Gudbrand Tandberg on 19/05/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

/*				___11. AN ECB/CBC DETECTION ORACLE___
 *
 * Now that you have ECB and CBC working:
 *
 * Write a function to generate a random AES key; that's just 16 random bytes.
 *
 * Write a function that encrypts data under an unknown key --- that is, a 
 * function that generates a random key and encrypts under it.
 *
 * The function should look like:
 *
 * encryption_oracle(your-input)
 * => [MEANINGLESS JIBBER JABBER]
 * Under the hood, have the function append 5-10 bytes (count chosen randomly)
 * before the plaintext and 5-10 bytes after the plaintext.
 *
 * Now, have the function choose to encrypt under ECB 1/2 the time, and under
 * CBC the other half (just use random IVs each time for CBC). Use rand(2) to
 * decide which to use.
 *
 * Detect the block cipher mode the function is using each time. You should end
 * up with a piece of code that, pointed at a block box that might be encrypting
 * ECB or CBC, tells you which one is happening.
 */
 
#include "OpenSSLFunctions.h"

//unsigned char *random_aes_key();
//bytestream encryption_oracle(bytestream input);
//void detect_mode(bytestream (*encryption_oracle(bytestream)));

bytestream func(bytestream input) {
	return input;
}

int main(int argc, const char * argv[]) {
	
	bytestream (*funcPtr)(bytestream) = &encryption_oracle;
	
	detect_mode(funcPtr);
	
    return 0;
}
