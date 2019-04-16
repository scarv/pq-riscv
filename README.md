
# PQ-RISCV

*A repository for analysing NIST post quantum cryptography candidates
on the RISC-V ISA.*

---

## Schemes & Parameters:

Builds | Finished | Scheme | Deps | Notes
-------|---------|---------|------|-------
 [x] |    | `kem_bike64` | NTL, Bignum | 
 [ ] |    | `kem_bike96` |  |
 [ ] |    | `kem_bike128` |  |
 [x] |    | `kem_frodo640` |  |
 [ ] |    | `kem_frodo976` |  |
 [ ] |    | `kem_frodo1344` |  |
 [x] |    | `kem_kyber512` |  |
 [ ] |    | `kem_kyber768` |  |
 [ ] |    | `kem_kyber1024` |  |
 [x] |    | `kem_lac128` |  |
 [ ] |    | `kem_lac192` |  |
 [ ] |    | `kem_lac256` |  |
 [x] |    | `kem_ledacrypt` | | (SL=4,N0=2)
 [x] |    | `kem_mceliece348864` |  |
 [x] |    | `newhope512cca` |  |
 [ ] |    | `newhope512cpa` |  |
 [ ] |    | `newhope1014cca` |  |
 [ ] |    | `newhope1014cpa` |  |
 [x] |    | `hqc-128-1` |  |
 [ ] |    | `hqc-192-1` |  |
 [ ] |    | `hqc-192-2` |  |
 [ ] |    | `hqc-256-1` |  |
 [ ] |    | `hqc-256-2` |  |
 [ ] |    | `hqc-256-3` |  |
 [x] |    | `ntru-hps2048509` |  |
 [ ] |    | `ntru-hps2048677` |  |
 [ ] |    | `ntru-hps4096821` |  |
 [ ] |    | `ntru-hrss701` |  |
 [x] |    | `ntru-prime-ntrulpr653` |  |
 [ ] |    | `ntru-prime-ntrulpr761` |  |
 [ ] |    | `ntru-prime-ntrulpr857` |  |
 [ ] |    | `ntru-prime-sntrup653` |  |
 [ ] |    | `ntru-prime-sntrup761` |  |
 [ ] |    | `ntru-prime-sntrup857` |  |
 [x] |    | `nokats_12_64` |  |
 [ ] |    | `nokats_13_80` |  |
 [ ] |    | `nokats_13_136` |  |
 [?] |    | `rollo-i-128` | NTL |
 [ ] |    | `rollo-i-192` |  |
 [ ] |    | `rollo-i-256` |  |
 [ ] |    | `rollo-ii-128` |  |
 [ ] |    | `rollo-ii-192` |  |
 [ ] |    | `rollo-ii-256` |  |
 [ ] |    | `rollo-iii-128` |  |
 [ ] |    | `rollo-iii-192` |  |
 [ ] |    | `rollo-iii-256` |  |
 [?] |    | `round5_r5n1_1kem_0d` |  | RNG functions need unpicking 
 [ ] |    | `round5_r5n1_3kem_0d` |  |
 [ ] |    | `round5_r5n1_5kem_0d` |  |
 [ ] |    | `round5_r5nd_0kem_2iot` |  |
 [ ] |    | `round5_r5nd_1kem_0d` |  |
 [ ] |    | `round5_r5nd_1kem_4longkey` |  |
 [ ] |    | `round5_r5nd_1kem_5d` |  |
 [ ] |    | `round5_r5nd_3kem_0d` |  |
 [ ] |    | `round5_r5nd_3kem_5d` |  |
 [ ] |    | `round5_r5nd_5kem_0d` |  |
 [ ] |    | `round5_r5nd_5kem_5d` |  |
 [?] |    | `rqc-128` | NTL |
 [ ] |    | `rqc-192` | NTL |
 [ ] |    | `rqc-256` | NTL |
 [x] |    | `saber_1` |  |
 [ ] |    | `saber_2` |  |
 [ ] |    | `saber_3` |  |
 [?] |    | `sikep434` | GMP |
 [ ] |    | `sikep503` | GMP |
 [ ] |    | `sikep610` | GMP |
 [ ] |    | `sikep751` | GMP |
 [x] |    | `threebears_babybear` | | Uses custom SHAKE implementation. Removed `weak` attribute from expand function in `ring.h` as it causes linker to emit jump to `0x0`.
 [ ] |    | `threebears_babybearephem` | |
 [ ] |    | `threebears_mamabearephem` | |
 [ ] |    | `threebears_mamabear` | |
 [ ] |    | `threebears_papabearephem` | |
 [ ] |    | `threebears_papabear` | |
 [ ] |    | `zips` |  |
