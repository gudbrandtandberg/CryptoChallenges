//
//  Set1.c
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 12/05/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "CryptoChallenges.h"

/************************************1*****************************************/

#define PADDING_CHAR 99

static char encoding_table[];
static int lookup(char c);

char *base64_encode(const bytestream data) {
	size_t num_input_bytes = data.length;
	size_t num_triplets = num_input_bytes / 3;
	size_t remainder = num_input_bytes % 3; //is 0, 1 or 2
	
	size_t output_length = num_triplets * 4 + ((remainder != 0) ? 1 : 0) * 4;
	
	char *base64_encoded_bytes = (char *)malloc(output_length+1);
	if (!base64_encoded_bytes) return NULL;
	
	uint32_t sixSetBitsMask = 0x3f; //111111
	uint32_t octet_a, octet_b, octet_c, bitpattern;
	
	int i = 0, j = 0;
	while (i < (num_input_bytes - remainder)) {
		
		octet_a = data.bytes[i++];
		octet_b = data.bytes[i++];
		octet_c = data.bytes[i++];
		
		bitpattern = (octet_a << 16) + (octet_b << 8) + (octet_c << 0);
		
		base64_encoded_bytes[j++] = encoding_table[(int) (bitpattern >> 18 &
														  (sixSetBitsMask))];
		base64_encoded_bytes[j++] = encoding_table[(int) (bitpattern >> 12 &
														  (sixSetBitsMask))];
		base64_encoded_bytes[j++] = encoding_table[(int) (bitpattern >> 6 &
														  (sixSetBitsMask))];
		base64_encoded_bytes[j++] = encoding_table[(int) (bitpattern >> 0 &
														  (sixSetBitsMask))];
	}
	
	//now for the remainder:
	if (remainder == 1) {
		
		octet_a = data.bytes[i++];
		octet_b = 0;
		octet_c = 0;
		
		bitpattern = (octet_a << 16) + (octet_b << 8) + (octet_c << 0);
		
		base64_encoded_bytes[j++] = encoding_table[(bitpattern >> 18 &
													(sixSetBitsMask))];
		base64_encoded_bytes[j++] = encoding_table[(bitpattern >> 12 &
													(sixSetBitsMask))];
		base64_encoded_bytes[j++] = '=';
		base64_encoded_bytes[j++] = '=';
	}
	else if (remainder == 2) {
		octet_a = data.bytes[i++];
		octet_b = data.bytes[i++];
		octet_c = 0;
		
		bitpattern = (octet_a << 16) + (octet_b << 8) + (octet_c << 0);
		
		base64_encoded_bytes[j++] = encoding_table[(int) (bitpattern >> 18 &
														  (sixSetBitsMask))];
		base64_encoded_bytes[j++] = encoding_table[(int) (bitpattern >> 12 &
														  (sixSetBitsMask))];
		base64_encoded_bytes[j++] = encoding_table[(int) (bitpattern >> 6 &
														  (sixSetBitsMask))];
		base64_encoded_bytes[j++] = '=';
	}
	
	return base64_encoded_bytes;
}

bytestream base64_decode(const char* base64) {
	size_t num_input_bytes = strlen(base64);
	size_t output_length = 3 * num_input_bytes / 4;
	
	byte *decoded_bytes = malloc(output_length);
	if (!decoded_bytes) return bs_make(NULL, 0);
	
	int i = 0, j = 0;
	int a, b, c, d;
	int eightBits = 255;
	int bitpattern;
	
	while (base64[j] != '\0') {
		a = lookup(base64[j++]) << 18;
		b = lookup(base64[j++]) << 12;
		c = lookup(base64[j++]) << 6;
		d = lookup(base64[j++]) << 0;
		
		if (d == PADDING_CHAR) {
			if ((c >> 6) == PADDING_CHAR) {
				//two padding chars
				bitpattern = a + b;
				decoded_bytes[i++] = (bitpattern >> 16) & eightBits;
				output_length -= 2;
				break; //reached end
				
			} else {
				//one padding char
				bitpattern = a + b + c;
				decoded_bytes[i++] = (bitpattern >> 16) & eightBits;
				decoded_bytes[i++] = (bitpattern >> 8) & eightBits;
				output_length -= 1;
				break;
				
			}
		} else {
			bitpattern = a + b + c + d;
			
			decoded_bytes[i++] = (bitpattern >> 16) & eightBits;
			decoded_bytes[i++] = (bitpattern >> 8) & eightBits;
			decoded_bytes[i++] = (bitpattern >> 0) & eightBits;
		}
	}
	return bs_make(decoded_bytes, output_length);
}

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'};

// ex. lookup('D') = 3
static int lookup(char c) {  // NOT VERY PRETTY
	int ret;
	if (c == '=') {
		return PADDING_CHAR;
	}
	for (ret = 0; ret <= 63; ret++) {
		if (encoding_table[ret] == c) {
			return ret;
		}
	}
	return 65;  //?
}

/************************************2*****************************************/
bytestream fixed_xor(bytestream bs1, bytestream bs2) {
	size_t input_length;
	
	if ((input_length = bs1.length) != bs2.length){
		printf("Streams not same length\n");
		exit(1);
	}
	
	byte *output_bytes = malloc(input_length);
	for (int i = 0; i < input_length; i++) {
		output_bytes[i] = bs1.bytes[i] ^ bs2.bytes[i];
	}
	
	return bs_make(output_bytes, input_length);
}

/************************************3*****************************************/

float score_of_english_text(bytestream text);
float score_of_char(char c);

bytestream single_byte_xor_crack(bytestream cipher, int *key) {
	byte start_char = 0, end_char = 255;
	int c;
	int num_candidates = end_char - start_char + 1;
	bytestream *candidates = (bytestream *)malloc(num_candidates *
												  sizeof(bytestream));
	
	// clever - c is used as loop-variable AND cipher key!
	for (c = start_char; c <= end_char; c++) {
		candidates[c] = single_byte_xor(cipher, c);
	}
	
	bytestream decrypt = find_most_english(candidates, num_candidates, key);
	return decrypt;
}

bytestream single_byte_xor(bytestream input, byte c) {
	size_t input_length = input.length;
	byte *output_bytes = malloc(input_length);
	
	for (int i = 0; i < input_length; i++) {
		output_bytes[i] = input.bytes[i] ^ c;
	}
	
	return bs_make(output_bytes, input_length);
}

bytestream find_most_english(bytestream *candidates,
							 int num_candidates, int *index) {
	float highscore = -1000.0;  //really low
	float newscore = 0.0;
	
	//go through candidates and give a score based on characters
	for (int i = 0; i < num_candidates; i++) {
		newscore = score_of_english_text(candidates[i]);
		if (newscore > highscore) {
			*index = i;
			highscore = newscore;
		}
	}
	return candidates[*index];
}

//does not take into account string length..
//ok if all strings are of equal length
float score_of_english_text(bytestream text) {
	float score = 0.0;
	
	for (int i=0; i<text.length; i++) {
		score += score_of_char(text.bytes[i]);
	}
	return score;
}

float score_of_char(char c) {
	if (!isprint(c)) {
		return -0.1;  //PUNISH!
	} else if (c == 'E' || c == 'e') {
		return .127;
	} else if (c == 'T' || c == 't') {
		return .091;
	} else if (c == 'A' || c == 'a') {
		return .082;
	} else if (c == 'O' || c == 'o') {
		return .075;
	} else if (c == 'I' || c == 'i') {
		return .07;
	} else if (c == 'N' || c == 'n') {
		return .067;
	} else if (c == 'S' || c == 's') {
		return .063;
	} else if (c == 'H' || c == 'h') {
		return .061;
	} else if (c == 'R' || c == 'r') {
		return .06;
	} else if (c == 'D' || c == 'd') {
		return .043;
	} else if (c == 'L' || c == 'l') {
		return .04;
	} else if (c == 'U' || c == 'u') {
		return .028;
	} else if (c == 'C' || c == 'c') {
		return .028;
	} else if (c == ' ') {
		return .02;
	}else {
		return 0.0;
	}
}

/************************************4*****************************************/

bytestream find_single_byte_xor(bytestream *lines, int num_lines,
								int *key) {
	
	bytestream finalists[num_lines];
	int keys[num_lines];
	
	//iterate through and crack each line
	for (int i = 0; i < num_lines; i++) {
		finalists[i] = single_byte_xor_crack(lines[i], &keys[i]);
	}
	
	//find the best candidate amongst the finalists
	int winner_key_index;
	bytestream winner = find_most_english(finalists, num_lines,
										  &winner_key_index);
	*key = keys[winner_key_index];
	
	return winner;
}

/************************************5*****************************************/

bytestream repeating_key_xor_encrypt(bytestream secret, bytestream password) {
	
	size_t secret_length = secret.length;
	size_t password_length = password.length;
	
	byte *output_bytes = malloc(secret_length);
	
	for (int i = 0; i < secret_length; i++) {
		output_bytes[i] = secret.bytes[i] ^ password.bytes[i % password_length];
	}

	return bs_make(output_bytes, secret_length);
}

/************************************6*****************************************/

int hamming_dist_byte(byte c1, byte c2);
int hamming_dist_stream(bytestream bs1, bytestream bs2);
int get_keysize(bytestream cipher);
bytestream *transpose(bytestream stream, int keysize);

bytestream break_repeating_key_xor(bytestream cipher, bytestream *password) {
	int keysize = get_keysize(cipher);
	bytestream *transposes = transpose(cipher, keysize);
	
	*password = bs_alloc(keysize);
	for (int i = 0; i < keysize; i++) {
		single_byte_xor_crack(transposes[i], (int *)&(password->bytes[i]));
	}
	
	bytestream plaintext = repeating_key_xor_encrypt(cipher, *password);
	return plaintext;
}

bytestream *transpose(bytestream stream, int keysize) {
	bytestream *transposes = malloc(keysize * sizeof(bytestream));
	
	for (int j = 0; j < keysize; j++) {
		int remainder =	stream.length % keysize;
		int transpose_length = ((int)stream.length / keysize) +
							   ((j < remainder) ? 1 : 0);
		
		transposes[j] = bs_alloc(transpose_length);
	}
	
	for (int i = 0; i < stream.length; i++) {
		transposes[i % keysize].bytes[i / keysize] = stream.bytes[i];
	}
	
	return transposes;
}

int get_keysize(bytestream cipher) {
	int keysize, best_keysize = 2, blocks = 3;
	float min = INT32_MAX, dist;
	bytestream first_chunk, second_chunk;
	
	for (keysize = 2; keysize <= 40; keysize++) {
		first_chunk = sub_stream(cipher, 0, blocks * keysize - 1);
		second_chunk = sub_stream(cipher, blocks*keysize, 2*blocks*keysize - 1);
		
		dist = (float)hamming_dist_stream(first_chunk, second_chunk) /
		(float)(keysize * blocks);
		
		if (dist < min) {
			min = dist;
			best_keysize = keysize;
		}
	}
	return best_keysize;
}

int hamming_dist_byte(byte c1, byte c2) {  //TODO: effective algorithm
	int sum = 0;
	int first, second;
	
	for (int mask = 128; mask > 0; mask >>= 1) {
		first = (mask & c1) > 0 ? 1 : 0;
		second = (mask & c2) > 0 ? 1 : 0;
		
		sum += first ^ second;
	}
	return sum;
}

int hamming_dist_stream(bytestream bs1, bytestream bs2) {
	size_t len;
	int sum = 0;
	
	if ((len = bs1.length) != bs2.length) {
		printf("Byte streams not same length\n");
		exit(1);
	}
	
	for (int i = 0; i < len; i++) {
		sum += hamming_dist_byte(bs1.bytes[i], bs2.bytes[i]);
	}
	return sum;
}

/************************************7*****************************************/

/*							IN OpenSSLFunctions.h/c							  */

/************************************8*****************************************/

int has_repeating_blocks(bytestream data) {
	const int blocksize = 16;
	size_t data_length = data.length;
	assert(data.length % blocksize == 0);
	
	for (int offset = 0; offset < data.length - blocksize; offset += 16) {
		//offset = 0, 16, 32, ... 144
		bytestream blockstream = sub_stream(data, offset, offset + blocksize - 1);
		
		bytestream remaining_data = sub_stream(data, offset+blocksize,
											   (int)data_length-1);
		
		int position = strmnstrm(remaining_data, blockstream,
								 data_length-(int)offset-blocksize);
		
		if (position != NO_SUBSTREAM) {
			int position_in_data = position + offset + blocksize;
			if ((position_in_data % 16) == 0) {
				return 1;
			}
		}
	}
	return 0;
}

/************************************9*****************************************/

int pkcs_7_pad(bytestream *bs_to_pad, size_t blocksize) {  //TODO: error handle
	
	//why wont realloc work for (*bs_to_pad).bytes ??
	
	size_t input_length = (*bs_to_pad).length;
	size_t remainder = input_length % blocksize;
	size_t num_padding_chars = blocksize - remainder;
	
	byte *new_bytes = malloc(input_length + num_padding_chars);
	memcpy(new_bytes, (*bs_to_pad).bytes, input_length);
	
	for (int i = 0; i < num_padding_chars; i++) {
		new_bytes[input_length + i] = num_padding_chars;
	}
	
	(*bs_to_pad).bytes = malloc(input_length + num_padding_chars);
	(*bs_to_pad).length += num_padding_chars;
	(*bs_to_pad).bytes = new_bytes;
	
	return 1;
}

/***********************************10*****************************************/

/*							IN OpenSSLFunctions.h/c							  */


