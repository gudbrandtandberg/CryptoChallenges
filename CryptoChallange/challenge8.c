//
//  challenge8.c
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 13/05/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "CryptoChallenges.h"

/*					  ___8. Detect AES in ECB mode___
 *
 * In this file (ex8strings.hex) are a bunch of hex-encoded ciphertexts.
 *
 * One of them has been encrypted with ECB.
 *
 * Detect it.
 *
 * Remember that the problem with ECB is that it is stateless and deterministic;
 * the same 16 byte plaintext block will always produce the same 16 byte
 * ciphertext.
 */

int main(int argc, char **argv) {
	int lines_in_file = 204;
	bytestream *lines = hex_decode_lines("8.txt", lines_in_file);

	for (int i = 0; i < lines_in_file; i++) {
		if (has_repeating_blocks(lines[i])) {
			printf("Line %d has repeating blocks!\n", i+1);
			printf("Perhaps it is encrypted with in ECB mode!?\n");
		}
	}
}