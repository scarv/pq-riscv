#ifndef AES128_H
#define AES128_H

#include <stdint.h>


//
// Stub types for moving away from OpenSSL
//

# define AES_MAXNR 14

/*!
@brief AES Key type
@details taken from
    https://github.com/openssl/openssl/blob/master/include/openssl/aes.h#L31
*/
struct aes_key_st {
    uint32_t rd_key[4 * (AES_MAXNR + 1)];
    int rounds;
};
typedef struct aes_key_st AES_KEY;

/*!
@brief Set the key to be used for an AES context.
@note Stubbed version of AES_set_encrypt_key from openssl.
*/
int pqriscv_aes_set_encrypt_key (
    const unsigned char *userKey,
    const int bits,
    AES_KEY *key
);

/*!
@brief Perform a 256 bit ECB mode encryption of a single AES block under the
    given key.
@param in key   - The 32-byte key.
@param in plain - The 32-byte plaintext.
@param out ctxt - The output ciphertext.
*/
void pqriscv_aes_256_ecb (
    unsigned char *key, 
    unsigned char *ctr,
    unsigned char *ctxt
);

/*
@brief AES 256 ctr mode encrypt
@note Signature lifted from newhope
*/
int pqriscv_stream_aes256ctr(
    unsigned char *c,
    unsigned long long clen,
    const unsigned char *n,
    const unsigned char *k
);

/*!
@brief Encrypt a single AES block
@note Stubbed version of openssl AES_encrypt
@param in key   - The 32-byte key.
@param in plain - The 32-byte plaintext.
@param out ctxt - The output ciphertext.
*/
void pqriscv_aes_encrypt(
    unsigned char *in, 
    unsigned char *out,
    AES_KEY       *key
);

#endif
