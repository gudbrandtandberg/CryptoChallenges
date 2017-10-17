//
//  OpenSSLFunctions.c
//  CryptoChallenge
//
//  Created by Gudbrand Tandberg on 14/05/16.
//  Copyright (c) 2016 Duff Development. All rights reserved.
//

#include "OpenSSLFunctions.h"

//TODO: comment & clean up this file
//TODO: error handling
bytestream aes_128_ecb_encrypt_block(bytestream block, unsigned char *password) {
	
	unsigned char *plain_block = block.bytes;
	const int blocksize = 16;
	
	unsigned char encrypted_block[blocksize];
	int bytes_written;
	EVP_CIPHER_CTX *ctx;
	ctx = EVP_CIPHER_CTX_new();
	
	EVP_EncryptInit(ctx, EVP_aes_128_ecb(), password, NULL);
	
	EVP_EncryptUpdate(ctx, encrypted_block, &bytes_written, plain_block, blocksize);

	byte *encrypted_bytes = malloc(blocksize);
	memcpy(encrypted_bytes, encrypted_block, blocksize);
	
	EVP_CIPHER_CTX_free(ctx);
	
	return bs_make(encrypted_bytes, blocksize);
}

bytestream aes_128_ecb_decrypt_block(bytestream block, unsigned char *password) {
	
	unsigned char *cipher_block = block.bytes;
	const int blocksize = 16;
	
	unsigned char decrypted_block[blocksize];
	int bytes_written;
	
	EVP_CIPHER_CTX *ctx;
	ctx = EVP_CIPHER_CTX_new();
	
	EVP_DecryptInit(ctx, EVP_aes_128_ecb(), password, NULL);
	
	EVP_DecryptUpdate(ctx, decrypted_block, &bytes_written, cipher_block, blocksize);
	
	byte *decrypted_bytes = malloc(blocksize);
	memcpy(decrypted_bytes, decrypted_block, blocksize);
	
	EVP_CIPHER_CTX_free(ctx);
	
	return bs_make(decrypted_bytes, blocksize);
}

bytestream aes_128_ecb_encrypt(bytestream data, unsigned char *password) {
	const int blocksize = 16;
	unsigned char *plaintext = (unsigned char *)data.bytes;
	unsigned char encryptedtext[data.length + blocksize];  //room for padding
	int encryptedtext_len, plaintext_len = (int)data.length, bytes_written;
	EVP_CIPHER_CTX *ctx;
	
	ctx = EVP_CIPHER_CTX_new();
	
	EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, password, NULL);
	
	EVP_EncryptUpdate(ctx, encryptedtext, &bytes_written, plaintext, plaintext_len);
	encryptedtext_len = bytes_written;
	
	EVP_EncryptFinal_ex(ctx, encryptedtext + bytes_written, &bytes_written);
	encryptedtext_len += bytes_written;
	
	EVP_CIPHER_CTX_free(ctx);
	
	byte *bytes = malloc(encryptedtext_len);
	memcpy(bytes, encryptedtext, encryptedtext_len);
	
	return bs_make(bytes, encryptedtext_len);
	
}

bytestream aes_128_ecb_decrypt(bytestream cipher, unsigned char *password) {
	unsigned char *ciphertext = (unsigned char *)cipher.bytes;
	unsigned char *decryptedtext = malloc(cipher.length+1); //more than enough
	int decryptedtext_len, ciphertext_len = (int)cipher.length, bytes_written;
	
	EVP_CIPHER_CTX *ctx;
	
	ctx = EVP_CIPHER_CTX_new();
	
	EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, password, NULL);
	
	EVP_DecryptUpdate(ctx, decryptedtext, &bytes_written, ciphertext, ciphertext_len);
	decryptedtext_len = bytes_written;
	
	EVP_DecryptFinal_ex(ctx, decryptedtext + bytes_written, &bytes_written);
	decryptedtext_len += bytes_written;
	
	EVP_CIPHER_CTX_free(ctx);
	
	byte *bytes = malloc(decryptedtext_len);
	memcpy(bytes, decryptedtext, decryptedtext_len);
	
	return bs_make(bytes, decryptedtext_len);
}

//TODO: get cbc enc/decryption working for arbitrary sized input..
bytestream aes_128_cbc_encrypt(bytestream plaintext,
							   unsigned char *password,
							   unsigned char *iv) {
	const int blocksize = 16;
	bytestream plaintext_block = sub_stream(plaintext, 0, blocksize - 1);
	bytestream last_cipherblock = bs_make(iv, blocksize);
	bytestream this_cipherblock = last_cipherblock;
	bytestream xor_result;
	byte *byte_collector = malloc(plaintext.length);
	
	int i = 0, start_index, end_index;
	while (plaintext_block.length != 0) {
		
		start_index = i * blocksize;
		end_index = start_index + blocksize - 1;
		
		xor_result = fixed_xor(plaintext_block, last_cipherblock);
		this_cipherblock = aes_128_ecb_encrypt_block(xor_result, password);
		
		memcpy(byte_collector + start_index, this_cipherblock.bytes, blocksize);
		
		last_cipherblock = this_cipherblock;
		plaintext_block = sub_stream(plaintext, start_index + blocksize, start_index + 2*blocksize - 1);
		
		i++;
	}
	
	return bs_make(byte_collector, plaintext.length);
	
}

bytestream aes_128_cbc_decrypt(bytestream ciphertext,
							   unsigned char *password,
							   unsigned char *iv) {
	const int blocksize = 16;
	
	//initially iv, subsequently stores the previous cipherblock
	bytestream last_cipherblock = bs_make(iv, blocksize);
	
	//initially first block of cipher, subsequently current cipherblock
	bytestream this_cipherblock = sub_stream(ciphertext, 0, blocksize - 1);
	
	//aes decryption of current cipherblock
	bytestream decrypted_block = bs_alloc(blocksize);
	
	//current plaintext block, result of xor-ing decrypted with last cipher
	bytestream this_plaintext_block = bs_alloc(blocksize);

	byte *plaintext_collector = malloc(ciphertext.length);
	
	int i = 0, start_index, end_index;
	while (this_cipherblock.length != 0) {
		start_index = i * blocksize;
		end_index = start_index + blocksize-1;
		
		decrypted_block = aes_128_ecb_decrypt_block(this_cipherblock, password);
		this_plaintext_block = fixed_xor(decrypted_block, last_cipherblock);
		
		memcpy(plaintext_collector + start_index, this_plaintext_block.bytes, blocksize);
		
		//save current cipherblock
		last_cipherblock = this_cipherblock;
		
		//get next cipherblock
		this_cipherblock = sub_stream(ciphertext, start_index+blocksize, end_index+blocksize);
		i++;
	}
	
	return bs_make(plaintext_collector, ciphertext.length);
}

unsigned char *random_aes_key() {
	return NULL;
}

bytestream encryption_oracle(bytestream input) {
	//1) pad input with 5-10 'bytes' on either end

	
	
	//2) encrypt ecb/cbc (50-50)
	if (rand() % 2) {
		printf("ECB\n");
	} else {
		printf("CBC\n");
	}
	
	print_bs(input);
	
	return bs_alloc(0);
}

void detect_mode(bytestream (*oracle)(bytestream)) {
	
	bytestream t = bs_from_chars("It's working!\n");
	
	print_bs(oracle(t));
	
}



