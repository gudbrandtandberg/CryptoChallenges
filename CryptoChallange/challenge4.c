//
//  challenge3.c
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 24/04/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "CryptoChallenges.h"

/*					___4. DETECT SINGLE-CHARACTER XOR___
 *
 * One of the 60-character strings in this file has been encrypted by
 * single-character XOR.
 *
 * Find it.
 *
 * (Your code from #3 should help.)
 */

int main(int argc, char **argv) {
	int key;
	const int lines_in_file = 327;
	bytestream *lines = hex_decode_lines("4.txt", lines_in_file);
	bytestream winner = find_single_byte_xor(lines, lines_in_file, &key);
	
	printf("Key: '%c'\n", key);
	printf("Winner: ");
	print_bs(winner);
}
