/* Based on the public domain implementation in
 * crypto_hash/sha512/ref/ from http://bench.cr.yp.to/supercop.html
 * by D. J. Bernstein */

#include <stdio.h>
#include "sha2.h"


static const unsigned char iv_384[64] = {
  0xcb,0xbb,0x9d,0x5d,0xc1,0x05,0x9e,0xd8,
  0x62,0x9a,0x29,0x2a,0x36,0x7c,0xd5,0x07,
  0x91,0x59,0x01,0x5a,0x30,0x70,0xdd,0x17,
  0x15,0x2f,0xec,0xd8,0xf7,0x0e,0x59,0x39,
  0x67,0x33,0x26,0x67,0xff,0xc0,0x0b,0x31,
  0x8e,0xb4,0x4a,0x87,0x68,0x58,0x15,0x11,
  0xdb,0x0c,0x2e,0x0d,0x64,0xf9,0x8f,0xa7,
  0x47,0xb5,0x48,0x1d,0xbe,0xfa,0x4f,0xa4
};

// defined in "sha2_512_hashblocks.c"
extern int crypto_hashblocks_sha512(
    unsigned char *statebytes,
    const unsigned char *in,
    unsigned long long inlen
);

int sha384(unsigned char *out, const unsigned char *in, unsigned long long inlen)
{
  unsigned char h[64];
  unsigned char padded[256];
  unsigned int i;
  unsigned long long bytes = inlen;

  for (i = 0;i < 64;++i) h[i] = iv_384[i];

  crypto_hashblocks_sha512(h,in,inlen);
  in += inlen;
  inlen &= 127;
  in -= inlen;

  for (i = 0;i < inlen;++i) padded[i] = in[i];
  padded[inlen] = 0x80;

  if (inlen < 112) {
    for (i = inlen + 1;i < 119;++i) padded[i] = 0;
    padded[119] = bytes >> 61;
    padded[120] = bytes >> 53;
    padded[121] = bytes >> 45;
    padded[122] = bytes >> 37;
    padded[123] = bytes >> 29;
    padded[124] = bytes >> 21;
    padded[125] = bytes >> 13;
    padded[126] = bytes >> 5;
    padded[127] = bytes << 3;
    crypto_hashblocks_sha512(h,padded,128);
  } else {
    for (i = inlen + 1;i < 247;++i) padded[i] = 0;
    padded[247] = bytes >> 61;
    padded[248] = bytes >> 53;
    padded[249] = bytes >> 45;
    padded[250] = bytes >> 37;
    padded[251] = bytes >> 29;
    padded[252] = bytes >> 21;
    padded[253] = bytes >> 13;
    padded[254] = bytes >> 5;
    padded[255] = bytes << 3;
    crypto_hashblocks_sha512(h,padded,256);
  }

  for (i = 0;i < 48;++i) out[i] = h[i];

  return 0;
}
