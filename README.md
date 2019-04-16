
# PQ-RISCV

*A repository for analysing NIST post quantum cryptography candidates
on the RISC-V ISA.*

---

**Contents:**
- [Overview](#Overview)
- [Aims](#Aims)
- [Repository Organisation](#Repository-Organisation)
- [Building and Running](#building-and-running)
- [Implementation Progress](#Implemented-Schemes)
- [License Information](#License-Information)
- [Acknowledgements](#Acknowledgements)
- [Todo](./TODO.md)

---

## Overview

This project aims to create a 
[single source](https://xkcd.com/927/) repository for building,
running and analysing 
[NIST post quantum](https://csrc.nist.gov/Projects/Post-Quantum-Cryptography)
candidates on the 
[RISC-V](http://riscv.org/)
architecture.

While there are already several projects which do this or similar
(see below), there are none that focus on RISC-V, which by the standards
of most ISAs is still something of a teenager.
This means:
- There are few pre-built dependencies one to build on.
- Those dependencies which do exist are not optimised for RISC-V.
- A new and increasingly popular / hyped architecture is being missed out
  of the PQC analysis.
- Analysis of the PQC candidates is useful in and of itself. What RISC-V
  allows over other ISAs is 
  [easy extension](https://github.com/scarv/xcrypto)
  via custom instructions to accelerate complex functions.
  This project aims to identify useful candidate functions for acceleration.
- RISC-V puts the **R** in RISC. It lacks certain functions (bit rotate,
  indexed memory addressing) which may have a large impact on cryptographic
  workloads. It is important these impacts are quantified.

This project is heavily inspired by the excellent
[libpqcrypto](https://libpqcrypto.org/index.html),
[PQClean](https://github.com/pqclean/pqclean) and
[pqm4](https://github.com/mupq/pqm4).
We are keen to work with others in this area to extend
and expand `pq-riscv`.

## Aims

Currently, only KEM candiates are included in the repository.
This is purely to make the workload more managable for the time
being.

**Short/medium term:**

- [x] Have one instance of each submission included and integrated into
      the build system.
- [ ] Identify external dependencies of all submissions.
  - [ ] Acquire riscv builds for these dependencies, or...
  - [ ] Create function stubs and implement only the required functionality
        manually.
- [ ] Have one instance of each submission successfully building.
- [ ] Have one instance of each submission running inside spike.
- [ ] For each candidate, use the benchmarking features of spike to
      identify performance critical code.

**Long term:**

- Be able to run code on actual RISC-V hardware in the way 
  [pqm4](https://github.com/mupq/pqm4)
  enables.
  - Candidates include the HiFive development board or an FPGA image of
    the Rocket Chip.
- Testing of Instruction Set Extensions (ISEs) like our 
  [XCrypto](https://github.com/scarv/xcrypto)
  project.
- Include signing schemes.

## Repository organisation

We take a *flat* approach to the content of the `candidates/` directory.
Each sub-directory is named to indicate the scheme, and the standard
parameter set of that scheme.

```
.
├── build           - All build artifacts live here
│   └── kem_*
├── candidates      - source
│   └── kem_*
│       ├── opt     - Source code for optimised implementations
│       └── ref     - Source code for the reference implementation
├── common
│   └── *           - Code used across all implementations
├── harness
│   └── main.c      - Top level test harness for all candidates
├── Makefile        - Top level make file
└── README.md       - This file
```

## Building and Running

**Pre-requesits:**
- [A RISC-V toolchain](https://github.com/riscv/riscv-gnu-toolchain)
- The standard RISC-V [toolset](https://github.com/riscv/riscv-tools).
  - Specifically, you will need the SPIKE ISA simulator, and the 
    proxy kernel "`pk`".

Make sure that you set your `RISCV` environmnet variable to point at
your toolchain installation.

**Building a scheme:**

This command will select a variant of a scheme.
```sh
$> make -f Makefile.kem SCHEME=<scheme name> VARIANT=<var> <target>
```

Where:
- `<scheme name>` is a directory in `candidates/`
- `<var>` is a directory under `candidates/<scheme name>/`
- `<target>` is one of `lib`, `exe` or `run`.
  - `lib` builds a static library for the specified candiate.
  - `exe` links the test hardness with the static library to create an
          executable elf file.
  - `run` will run the built elf file through spike on top of the
          proxy kernel.

Build artifacts are placed in `build/<scheme name>/<var>/`

## Implemented Schemes

The submitted code for each candidate is included in this repository.
Currently, only the reference implementations of each candidate are
included.
This serves to "*bring up*" the repository, build system and benchmark
flow.
Some code has been modified so that common functionality 
(`rng`,`aes`,`keccak`, etc) can be centrally managed
(in the `common/` directory).

Builds | Scheme  | Deps | Notes
-------|---------|------|-------
 [x] | `kem_bike64` | NTL, OpenSSL/Bignum |  Waiting on RISC-V dependencies
 [ ] | `kem_bike96` |  |
 [ ] | `kem_bike128` |  |
 [x] | `kem_frodo640` |  |
 [ ] | `kem_frodo976` |  |
 [ ] | `kem_frodo1344` |  |
 [x] | `kem_kyber512` |  |
 [ ] | `kem_kyber768` |  |
 [ ] | `kem_kyber1024` |  |
 [x] | `kem_lac128` |  |
 [ ] | `kem_lac192` |  |
 [ ] | `kem_lac256` |  |
 [x] | `kem_ledacrypt` | | (SL=4,N0=2)
 [x] | `kem_mceliece348864` |  | Fails to terminate without AES implemented.
 [ ] | `kem_mceliece348864f` |  | 
 [ ] | `kem_mceliece460896` |  | 
 [ ] | `kem_mceliece460896f` |  | 
 [ ] | `kem_mceliece6688128` |  | 
 [ ] | `kem_mceliece6688128f` |  | 
 [ ] | `kem_mceliece6960119` |  | 
 [ ] | `kem_mceliece6960119f` |  | 
 [ ] | `kem_mceliece8192128` |  | 
 [ ] | `kem_mceliece8192128f` |  | 
 [x] | `newhope512cca` |  |
 [ ] | `newhope512cpa` |  |
 [ ] | `newhope1014cca` |  |
 [ ] | `newhope1014cpa` |  |
 [x] | `hqc-128-1` |  |
 [ ] | `hqc-192-1` |  |
 [ ] | `hqc-192-2` |  |
 [ ] | `hqc-256-1` |  |
 [ ] | `hqc-256-2` |  |
 [ ] | `hqc-256-3` |  |
 [x] | `ntru-hps2048509` |  |
 [ ] | `ntru-hps2048677` |  |
 [ ] | `ntru-hps4096821` |  |
 [ ] | `ntru-hrss701` |  |
 [x] | `ntru-prime-ntrulpr653` |  |
 [ ] | `ntru-prime-ntrulpr761` |  |
 [ ] | `ntru-prime-ntrulpr857` |  |
 [ ] | `ntru-prime-sntrup653` |  |
 [ ] | `ntru-prime-sntrup761` |  |
 [ ] | `ntru-prime-sntrup857` |  |
 [x] | `nts_12_64` |  |
 [ ] | `nts_13_80` |  |
 [ ] | `nts_13_136` |  |
 [?] | `rollo-i-128` | NTL | Waiting on RISC-V dependencies
 [ ] | `rollo-i-192` |  |
 [ ] | `rollo-i-256` |  |
 [ ] | `rollo-ii-128` |  |
 [ ] | `rollo-ii-192` |  |
 [ ] | `rollo-ii-256` |  |
 [ ] | `rollo-iii-128` |  |
 [ ] | `rollo-iii-192` |  |
 [ ] | `rollo-iii-256` |  |
 [?] | `round5_r5n1_1kem_0d` |  | RNG functions need unpicking 
 [ ] | `round5_r5n1_3kem_0d` |  |
 [ ] | `round5_r5n1_5kem_0d` |  |
 [ ] | `round5_r5nd_0kem_2iot` |  |
 [ ] | `round5_r5nd_1kem_0d` |  |
 [ ] | `round5_r5nd_1kem_4longkey` |  |
 [ ] | `round5_r5nd_1kem_5d` |  |
 [ ] | `round5_r5nd_3kem_0d` |  |
 [ ] | `round5_r5nd_3kem_5d` |  |
 [ ] | `round5_r5nd_5kem_0d` |  |
 [ ] | `round5_r5nd_5kem_5d` |  |
 [?] | `rqc-128` | NTL | Waiting on RISC-V dependencies
 [ ] | `rqc-192` | NTL |
 [ ] | `rqc-256` | NTL |
 [x] | `saber_1` |  |
 [ ] | `saber_2` |  |
 [ ] | `saber_3` |  |
 [?] | `sikep434` | GMP |
 [ ] | `sikep503` | GMP |
 [ ] | `sikep610` | GMP |
 [ ] | `sikep751` | GMP |
 [x] | `threebears_babybear` | | Uses custom SHAKE implementation. Removed `weak` attribute from expand function in `ring.h` as it causes linker to emit jump to `0x0`.
 [ ] | `threebears_babybearephem` | |
 [ ] | `threebears_mamabearephem` | |
 [ ] | `threebears_mamabear` | |
 [ ] | `threebears_papabearephem` | |
 [ ] | `threebears_papabear` | |

---

## Acknowledgements

This work has been supported in part by EPSRC via grant 
[EP/R012288/1](https://gow.epsrc.ukri.org/NGBOViewGrant.aspx?GrantRef=EP/R012288/1),
under the [RISE](http://www.ukrise.org) programme.

