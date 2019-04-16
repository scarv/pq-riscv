

#include <stdio.h>
#include <stdlib.h>

// The KEM API header as specified by NIST. See the "-I" flags in the
// build string to see where this comes from: candidates/<scheme>/<var>/
#include "api.h"

// Performance measurement
#include "performance.h"

void print_hex (char * bytes, int length) {
    for(int i = 0; i < length; i ++) {
        printf("%02x",bytes[i]);
    }
}

int main(int argc, char ** argv) {

    unsigned int repeat_count = 100;

    printf("PQRISCV Test Harness Program\n");

    unsigned char sk [CRYPTO_SECRETKEYBYTES  ];
    unsigned char pk [CRYPTO_PUBLICKEYBYTES  ];
    unsigned char ct [CRYPTO_CIPHERTEXTBYTES ];
    unsigned char ss [CRYPTO_BYTES           ];

    uint32_t cycles_keypair;
    uint32_t cycles_enc;
    uint32_t cycles_dec;
    uint32_t instrs_keypair;
    uint32_t instrs_enc;
    uint32_t instrs_dec;

    printf("CRYPTO_SECRETKEYBYTES : %d\n", CRYPTO_SECRETKEYBYTES );
    printf("CRYPTO_PUBLICKEYBYTES : %d\n", CRYPTO_PUBLICKEYBYTES );
    printf("CRYPTO_CIPHERTEXTBYTES: %d\n", CRYPTO_CIPHERTEXTBYTES);
    printf("CRYPTO_BYTES          : %d\n", CRYPTO_BYTES          );
    
    printf("- Generate keypair:\n");
    cycles_keypair = perf_rdcycle();
    instrs_keypair = perf_rdinstret();
    crypto_kem_keypair(pk, sk);
    cycles_keypair = perf_rdcycle()   - cycles_keypair;
    instrs_keypair = perf_rdinstret() - instrs_keypair;

    printf("cycles = %10d\n", cycles_keypair);
    printf("instrs = %10d\n", instrs_keypair);
    //printf("pk     = 0x"); print_hex(pk,CRYPTO_PUBLICKEYBYTES); printf("\n");
    //printf("sk     = 0x"); print_hex(sk,CRYPTO_SECRETKEYBYTES); printf("\n");

    //printf("ct     = 0x"); print_hex(ct,CRYPTO_CIPHERTEXTBYTES); printf("\n");
    //printf("ss     = 0x"); print_hex(ss,CRYPTO_BYTES); printf("\n");

    printf("- Encrypt:\n");
    cycles_enc     = perf_rdcycle();
    instrs_enc     = perf_rdinstret();
    crypto_kem_enc(ct ,ss, pk);
    cycles_enc     = perf_rdcycle()   - cycles_enc    ;
    instrs_enc     = perf_rdinstret() - instrs_enc    ;
    
    printf("cycles = %10d\n", cycles_enc);
    printf("instrs = %10d\n", instrs_enc);
    //printf("ct     = 0x"); print_hex(ct,CRYPTO_CIPHERTEXTBYTES); printf("\n");
    //printf("ss     = 0x"); print_hex(ss,CRYPTO_BYTES); printf("\n");

    printf("- Decrypt:\n");
    cycles_dec     = perf_rdcycle();
    instrs_dec     = perf_rdinstret();
    crypto_kem_dec(ss, ct, sk);
    cycles_dec     = perf_rdcycle()   - cycles_dec    ;
    instrs_dec     = perf_rdinstret() - instrs_dec    ;
    
    printf("cycles = %10d\n", cycles_dec);
    printf("instrs = %10d\n", instrs_dec);
    //printf("ct     = 0x"); print_hex(ct,CRYPTO_CIPHERTEXTBYTES); printf("\n");
    //printf("ss     = 0x"); print_hex(ss,CRYPTO_BYTES); printf("\n");

    printf("--- END ---\n");

    return 0;

}

