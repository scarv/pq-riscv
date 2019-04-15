#ifndef SHA2_H
#define SHA2_H

int sha256(unsigned char *output, const unsigned char *input, unsigned long long inlen);
int sha384(unsigned char *output, const unsigned char *input, unsigned long long inlen);
int sha512(unsigned char *output, const unsigned char *input, unsigned long long inlen);

#endif


