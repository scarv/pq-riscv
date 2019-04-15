#include <stdint.h>
#include <string.h>
#include "aes.h"
#include "rijndael.h"
#include <stdio.h>

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
    unsigned char *ctr,
    unsigned char *ctxt
){
    pqriscv_aes_encrypt(ctr,ctxt,key);
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

