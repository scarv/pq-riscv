

#include <stdio.h>
#include <stdlib.h>

// The KEM API header as specified by NIST. See the "-I" flags in the
// build string to see where this comes from: candidates/<scheme>/<var>/
#include "api.h"

// Performance measurement
#include "performance.h"

#ifndef KEM_NAME
    #error Please define KEM_NAME
#endif

#ifndef KEM_VARIANT
    #error Please define KEM_VARIANT
#endif

/*!
@brief Prints out a character array in hexadecimal.
@param bytes - the array of bytes to print as hex
@param length - the length of bytes to print.
*/
void print_hex (char * bytes, int length) {
    for(int i = 0; i < length; i ++) {
        printf("%02x",bytes[i]);
    }
}

/*!
@brief Read <length> random bytes into <to_fill>
@param to_fill - pre-allocated array of bytes to be filled with random data.
@param length - The number of random bytes to read.
*/
void read_random(unsigned char * to_fill, size_t length) {
    FILE * fh = fopen("/dev/urandom","r");
    fread(to_fill, sizeof(unsigned char), length, fh);
    fclose(fh);
}

int main(int argc, char ** argv) {

    unsigned int repeat_count = 100;

    printf("---\n");
    printf("# PQRISCV Test Harness Program\n");

    printf("- kem: "); printf(KEM_NAME); printf("\n");
    printf("  CRYPTO_SECRETKEYBYTES : %d\n", CRYPTO_SECRETKEYBYTES );
    printf("  CRYPTO_PUBLICKEYBYTES : %d\n", CRYPTO_PUBLICKEYBYTES );
    printf("  CRYPTO_CIPHERTEXTBYTES: %d\n", CRYPTO_CIPHERTEXTBYTES);
    printf("  CRYPTO_BYTES          : %d\n", CRYPTO_BYTES          );
    printf("  - var: "); printf(KEM_VARIANT); printf("\n");

    unsigned char sk [CRYPTO_SECRETKEYBYTES  ];
    unsigned char pk [CRYPTO_PUBLICKEYBYTES  ];
    unsigned char ct [CRYPTO_CIPHERTEXTBYTES ];
    unsigned char ss [CRYPTO_BYTES           ];

    read_random(ss, CRYPTO_BYTES);

    uint64_t cycles_keypair;
    uint64_t cycles_enc;
    uint64_t cycles_dec;
    uint64_t instrs_keypair;
    uint64_t instrs_enc;
    uint64_t instrs_dec;
    
    printf("      - keypair:\n");
    cycles_keypair = perf_rdcycle();
    instrs_keypair = perf_rdinstret();
    crypto_kem_keypair(pk, sk);
    cycles_keypair = perf_rdcycle()   - cycles_keypair;
    instrs_keypair = perf_rdinstret() - instrs_keypair;

    printf("          cycles: %10lu\n", cycles_keypair);
    printf("          instrs: %10lu\n", instrs_keypair);

    printf("        encrypt:\n");
    cycles_enc     = perf_rdcycle();
    instrs_enc     = perf_rdinstret();
    crypto_kem_enc(ct ,ss, pk);
    cycles_enc     = perf_rdcycle()   - cycles_enc    ;
    instrs_enc     = perf_rdinstret() - instrs_enc    ;
    
    printf("          cycles: %10lu\n", cycles_enc);
    printf("          instrs: %10lu\n", instrs_enc);

    printf("        decrypt:\n");
    cycles_dec     = perf_rdcycle();
    instrs_dec     = perf_rdinstret();
    crypto_kem_dec(ss, ct, sk);
    cycles_dec     = perf_rdcycle()   - cycles_dec    ;
    instrs_dec     = perf_rdinstret() - instrs_dec    ;
    
    printf("          cycles: %10lu\n", cycles_dec);
    printf("          instrs: %10lu\n", instrs_dec);

    printf("---\nn");

    return 0;

}

