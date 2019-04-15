

#include <stdio.h>
#include <stdlib.h>

// The KEM API header as specified by NIST.
#include "api.h"

int main(int argc, char ** argv) {

    unsigned int repeat_count = 100;

    printf("PQRISCV Test Harness Program\n");

    unsigned char sk [CRYPTO_SECRETKEYBYTES  ];
    unsigned char pk [CRYPTO_PUBLICKEYBYTES  ];
    unsigned char ct [CRYPTO_CIPHERTEXTBYTES ];
    unsigned char ss [CRYPTO_BYTES           ];
    
    printf("- Generate keypair:\n");
    crypto_kem_keypair(pk, sk);

    printf("- Encrypt:\n");
    crypto_kem_enc(ct ,ss, pk);

    printf("- Decrypt:\n");
    crypto_kem_dec(ss, ct, sk);

    printf("--- END ---\n");

    return 0;

}
