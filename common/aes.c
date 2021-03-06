#include <stdint.h>
#include <string.h>
#include "aes.h"
#include <stdio.h>

#include "aes/tiny-aes.h"

/*!
*/
int pqriscv_aes_set_encrypt_key (
    const unsigned char *userKey,
    const int bits,
    AES_KEY *key
) {
    printf("%s:%d Not Implemented\n",__FILE__,__LINE__);
}

/*!
*/
void pqriscv_aes_256_ecb (
    unsigned char *key,     
    unsigned char *ctr, // in
    unsigned char *buffer// out
){
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);
    memcpy(buffer, ctr, AES_BLOCKLEN);
    AES_ECB_encrypt(&ctx, buffer);
}

/*!
*/
int pqriscv_stream_aes256ctr(
    unsigned char *c,
    unsigned long long clen,
    const unsigned char *n,
    const unsigned char *k
){
    fflush(stdout);
    struct AES_ctx ctx;
    AES_init_ctx(&ctx,k);
    AES_ctx_set_iv(&ctx, n); // n = nonce = IV.
    AES_CTR_xcrypt_buffer(&ctx, c, clen);
}

/*!
*/
void pqriscv_aes_encrypt(
    unsigned char *in, 
    unsigned char *out,
    AES_KEY       *key
) {
    printf("%s:%d Not Implemented\n",__FILE__,__LINE__);
}


