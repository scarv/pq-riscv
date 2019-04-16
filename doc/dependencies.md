
# Scheme Dependencies

*This document lists the external dependencies of each scheme*

---

**Note:** usage of one algorithm often implies another ([C]SHAKE etc),
so the table may look incomplete. Table is only populated for currently
implemented candidates.

Scheme         | AES |  SHA      | SHAKE | CSHAKE | NTL | GMP | Bignum
---------------|-----|-----------|-------|--------|-----|-----|--------
BIKE           |  x  | 2-384     |       |        |  x  |     | x
CRYSTALS-Kyber |  x  | 3-256,512 | 128,256 |      |     |     | 
FrodoKEM       |  x  | 3         |  128  |        |     |     | 
HQC            |  x  | 2-512     |       |        |  x  |     | 
LAC            |  x  | 2-256     |       |        |     |     | 
LEDAcrypt      |  x  |           |       |        |     |     | 
Mceliece       |  x  |           | 256   |        |     |     | 
NTRU           |  x  | 3-256     |       |        |     |     | 
NTRU-Prime     |  x  | 2-512     |       |        |     |     | 
NTSKEM         |  x  |           | 256   |        |     |     | 
NewHope        |  x  |           | 128,256 |      |     |     | 
ROLLO          |  x  |           |       |        |  x  |     | 
RQC            |  x  |           |       |        |  x  |     | 
Round5         |  x  |           |       | 128,256 |    |     | 
SABER          |  x  | 3-256,512 | 128   |        |     |     | 
SIKE           |  x  |           | 256   |        |     |     | 
ThreeBears     |  x  |           |  x    |        |     |     | 
