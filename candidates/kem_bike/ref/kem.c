/******************************************************************************
 * BIKE -- Bit Flipping Key Encapsulation
 *
 * Copyright (c) 2017 Nir Drucker, Shay Gueron, Rafael Misoczki, Tobias Oder, Tim Gueneysu
 * (drucker.nir@gmail.com, shay.gueron@gmail.com, rafael.misoczki@intel.com, tobias.oder@rub.de, tim.gueneysu@rub.de)
 *
 * Permission to use this code for BIKE is granted.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * The names of the contributors may not be used to endorse or promote
 *   products derived from this software without specific prior written
 *   permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ""AS IS"" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS CORPORATION OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <stdio.h>
#include <string.h>

#include "parallel_hash.h"
#include "ntl.h"
#include "decode.h"
#include "sampling.h"
#include "kem.h"
#include "aes_ctr_prf.h"
#include "conversions.h"

// Function G required by BIKE-1/2-CCA variants. It uses the extract-then-expand
// paradigm based on SHA384 and AES256-CTR PRNG to produce m from e:
_INLINE_ status_t functionG(
    OUT uint8_t * m,
    IN const uint8_t* e)
{
  status_t res = SUCCESS;

  // hash e to generate a seed:
  sha384_hash_t hash_seed = {0};
  parallel_hash(&hash_seed, e, N_SIZE);

  // format seed as a 32-bytes input:
  aes_ctr_prf_state_t prf_state = {0};
  seed_t seed_for_hash;
  memcpy(seed_for_hash.raw, hash_seed.raw, 32);

  // use the seed in AES-CTR PRNG to generate m:
  res = init_aes_ctr_prf_state(
      &prf_state,
      MAX_AES_INVOKATION,
      &seed_for_hash);
  CHECK_STATUS(res);
  res = aes_ctr_prf(m, &prf_state, R_SIZE); CHECK_STATUS(res);

  EXIT:
  return res;
}


// Function G required by BIKE3-CCA variant. It uses the extract-then-expand
// paradigm based on SHA384 and AES256-CTR PRNG to produce e_extra of weight
// t/2 from e:
_INLINE_ status_t functionG_BIKE3(
    OUT uint8_t * e_extra,
    IN const uint8_t* e)
{
  status_t res = SUCCESS;

  // hash e to generate a seed:
  sha384_hash_t hash_seed = {0};
  parallel_hash(&hash_seed, e, N_SIZE);

  // format seed as a 32-bytes input:
  aes_ctr_prf_state_t prf_state = {0};
  seed_t seed_for_hash;
  memcpy(seed_for_hash.raw, hash_seed.raw, 32);

  // use the seed in AES-CTR PRNG to generate m:
  res = init_aes_ctr_prf_state(
      &prf_state,
      MAX_AES_INVOKATION,
      &seed_for_hash);
  CHECK_STATUS(res);
  res = generate_sparse_rep(e_extra, T1/2, R_BITS, &prf_state); CHECK_STATUS(res);

  EXIT:
  return res;
}

_INLINE_ status_t encrypt(OUT ct_t* ct,
        IN const uint8_t* e,
        IN const uint8_t* ep,
        IN const pk_t* pk,
        IN const seed_t* seed)
{
    status_t res = SUCCESS;

    uint8_t c0[R_SIZE] = {0};
    uint8_t c1[R_SIZE] = {0};

    uint8_t e0[R_SIZE] = {0};
    uint8_t e1[R_SIZE] = {0};

    ntl_split_polynomial(e0, e1, e);

#ifdef BIKE1
    // ct = (m*pk0 + e0, m*pk1 + e1)
    uint8_t m[R_SIZE] = {0};

#ifdef INDCCA
    // m = G(e0, e1)
    functionG(m, e);
#else
    // m <- random
    sample_uniform_r_bits(m, seed, NO_RESTRICTION);
#endif

    ntl_mod_mul(c0, m, pk->val0);
    ntl_mod_mul(c1, m, pk->val1);
    ntl_add(ct->val0, c0, e0);
    ntl_add(ct->val1, c1, e1);
#else
#ifdef BIKE2
    // ct = (e1*pk1 + e0)
    ntl_mod_mul(c1, e1, pk->val1);
    ntl_add(ct->val0, c1, e0);
    for (int i = 0; i < R_SIZE; i++)
        ct->val1[i] = 0;
#else
#ifdef BIKE3
    // ct = (e1*pk0 + e_extra, e1*pk1 + e0)
    ntl_mod_mul(c0, e1, pk->val0);
    ntl_mod_mul(c1, e1, pk->val1);
    ntl_add(ct->val0, c0, ep);
    ntl_add(ct->val1, c1, e0);
#endif
#endif
#endif

    EDMSG("c0: "); print((uint64_t*)ct->val0, R_BITS);
    EDMSG("c1: "); print((uint64_t*)ct->val1, R_BITS);

EXIT:
    return res;
}

//Generate the Shared Secret for CCA variants as K(e, ciphertext)
_INLINE_ status_t get_ss_cca(OUT ss_t* out, IN uint8_t* e, IN ct_t* l_ct)
{
    status_t res = SUCCESS;

    DMSG("    Enter get_ss.\n");

    sha384_hash_t hash = {0};

    // concatenating error vector and ciphertext: tmp =[e || ct]
    uint8_t tmp[2*N_SIZE];
    memcpy(tmp, e, N_SIZE);
#ifdef BIKE2
    memcpy(tmp+N_SIZE, l_ct->raw, R_SIZE);
    parallel_hash(&hash, tmp, N_SIZE + R_SIZE);
#else
    memcpy(tmp+N_SIZE, l_ct->raw, N_SIZE);
    parallel_hash(&hash, tmp, 2*N_SIZE);
#endif

    //Truncate the final hash into K
    //by copying only the LSBs
    for(uint32_t i = 0; i < sizeof(ss_t); i++)
    {
        out->raw[i] = hash.raw[i];
    }

EXIT:
    DMSG("    Exit get_ss.\n");
    return res;
}

//Generate the Shared Secret for CPA variants as K(e)
_INLINE_ status_t get_ss_cpa(OUT ss_t* out, IN uint8_t* e)
{
    status_t res = SUCCESS;

    DMSG("    Enter get_ss.\n");

    sha384_hash_t hash = {0};

    //Calculate the hash.
    parallel_hash(&hash, e, N_SIZE);

    //Truncate the final hash into K.
    //By copying only the LSBs
    for(uint32_t i = 0; i < sizeof(ss_t); i++)
    {
        out->raw[i] = hash.raw[i];
    }

EXIT:
    DMSG("    Exit get_ss.\n");
    return res;
}

// transpose a row into a column:
_INLINE_ void transpose(uint8_t col[R_BITS], uint8_t row[R_BITS])
{
    col[0] = row[0];
    for (uint64_t i = 1; i < R_BITS ; ++i)
    {
        col[i] = row[(R_BITS) - i];
    }
}

_INLINE_ status_t compute_syndrome(OUT syndrome_t* syndrome,
        IN const ct_t* ct,
        IN const sk_t* sk)
{
    status_t res = SUCCESS;
    uint8_t s_tmp_bytes[R_BITS] = {0};
    uint8_t s0[R_SIZE] = {0};

#ifdef BIKE1
    // BIKE-1 syndrome: s = h0*c0 + h1*c1:
    ntl_mod_mul(s0, sk->val0, ct->val0);
    uint8_t s1[R_SIZE] = {0};
    ntl_mod_mul(s1, sk->val1, ct->val1);
    ntl_add(s0, s0, s1);
#else
#ifdef BIKE2
    // BIKE-2 syndrome: s = c0*h0
    ntl_mod_mul(s0, sk->val0, ct->val0);
#else
#ifdef BIKE3
    // BIKE3 syndrome: s = c0 + c1*h0
    ntl_mod_mul(s0, ct->val1, sk->val0);
    ntl_add(s0, s0, ct->val0);
#endif
#endif
#endif

    //Store the syndrome in a bit array
    convertByteToBinary(s_tmp_bytes, s0, R_BITS);
    transpose(syndrome->raw, s_tmp_bytes);

    EXIT:
    return res;
}

////////////////////////////////////////////////////////////////
//The three APIs below (keypair, enc, dec) are defined by NIST:
//In addition there are two KAT versions of this API as defined.
////////////////////////////////////////////////////////////////
int crypto_kem_keypair(OUT unsigned char *pk, OUT unsigned char *sk)
{
    //Convert to this implementation types
    sk_t* l_sk = (sk_t*)sk;
    pk_t* l_pk = (pk_t*)pk;
    status_t res = SUCCESS;

    //For NIST DRBG_CTR.
    double_seed_t seeds = {0};
    aes_ctr_prf_state_t h_prf_state = {0};

    //Get the entropy seeds.
    get_seeds(&seeds, KEYGEN_SEEDS);

    // sk = (h0, h1)
    uint8_t * h0 = l_sk->val0;
    uint8_t * h1 = l_sk->val1;

#ifdef INDCCA
    // (sigma0, sigma1)
    uint8_t * sigma0 = l_sk->sigma0;
    uint8_t * sigma1 = l_sk->sigma1;
    aes_ctr_prf_state_t h_prf_state_sigma = {0};
#endif

    DMSG("  Enter crypto_kem_keypair.\n");
    DMSG("    Calculating the secret key.\n");

#ifdef BIKE1
    uint8_t g[R_SIZE] = {0};
#endif
#ifdef BIKE2
    uint8_t inv_h0[R_SIZE] = {0};
#endif
#ifdef BIKE3
    uint8_t tmp1[R_SIZE] = {0};
	uint8_t * g = l_pk->val1;
#endif

    //Both h0 and h1 use the same PRNG context built from seed s1
    init_aes_ctr_prf_state(&h_prf_state, MAX_AES_INVOKATION, &seeds.s1);

    res = generate_sparse_rep(h0, DV, R_BITS, &h_prf_state); CHECK_STATUS(res);
    res = generate_sparse_rep(h1, DV, R_BITS, &h_prf_state); CHECK_STATUS(res);

#ifdef INDCCA
    //Both sigma0 and sigma1 use the same PRNG context built from seed s3
    init_aes_ctr_prf_state(&h_prf_state_sigma, MAX_AES_INVOKATION, &seeds.s3);
    res = sample_uniform_r_bits_with_fixed_prf_context(sigma0, &h_prf_state_sigma, NO_RESTRICTION); CHECK_STATUS(res);
    res = sample_uniform_r_bits_with_fixed_prf_context(sigma1, &h_prf_state_sigma, NO_RESTRICTION); CHECK_STATUS(res);
#endif

    DMSG("    Calculating the public key.\n");

#ifdef BIKE1
    //  pk = (g*h1, g*h0)
    res = sample_uniform_r_bits(g, &seeds.s2, MUST_BE_ODD);  CHECK_STATUS(res);

    ntl_mod_mul(l_pk->val0, g, h1); CHECK_STATUS(res);
    ntl_mod_mul(l_pk->val1, g, h0); CHECK_STATUS(res);
#else
#ifdef BIKE2
    // pk = (1, h1*h0^(-1))
    l_pk->val0[0] = 1;
    for (int i = 1; i < R_SIZE; i++)
        l_pk->val0[i] = 0;
    ntl_mod_inv(inv_h0, h0);
    ntl_mod_mul(l_pk->val1, h1, inv_h0);
#else
#ifdef BIKE3
    // pk = (h1 + g*h0, g)
    res = sample_uniform_r_bits(g, &seeds.s2, MUST_BE_ODD);  CHECK_STATUS(res);
    ntl_mod_mul(tmp1, g, h0);
    ntl_add(l_pk->val0, tmp1, h1);
#endif
#endif
#endif

    //add a copy of the public key into the private key as needed for CCA decapsulation:
#ifdef INDCCA
    memcpy(l_sk->l_pk.val0, l_pk->val0, R_SIZE);
    memcpy(l_sk->l_pk.val1, l_pk->val1, R_SIZE);
#endif

    EDMSG("h0: "); print((uint64_t*)l_sk->val0, R_BITS);
    EDMSG("h1: "); print((uint64_t*)l_sk->val1, R_BITS);
    EDMSG("g0: "); print((uint64_t*)l_pk->val0, R_BITS);
    EDMSG("g1: "); print((uint64_t*)l_pk->val1, R_BITS);
#ifdef INDCCA
    EDMSG("sigma0: "); print((uint64_t*)l_sk->sigma0, R_BITS);
    EDMSG("sigma1: "); print((uint64_t*)l_sk->sigma1, R_BITS);
#endif

EXIT:
    DMSG("  Exit crypto_kem_keypair.\n");
    return res;
}

//Encapsulate - pk is the public key,
//              ct is a key encapsulation message (ciphertext),
//              ss is the shared secret.
int crypto_kem_enc(OUT unsigned char *ct,
        OUT unsigned char *ss,
        IN  const unsigned char *pk)
{
    DMSG("  Enter crypto_kem_enc.\n");

    status_t res = SUCCESS;

    //Convert to these implementation types
    const pk_t* l_pk = (pk_t*)pk;
    ct_t* l_ct = (ct_t*)ct;
    ss_t* l_ss = (ss_t*)ss;

    //For NIST DRBG_CTR.
    double_seed_t seeds = {0};
    aes_ctr_prf_state_t e_prf_state = {0};

    //Get the entropy seeds.
    get_seeds(&seeds, ENCAPS_SEEDS);

    // error vector:
    uint8_t e[N_SIZE] = {0};
#ifdef BIKE3
    uint8_t e_extra[R_SIZE]={0};
#endif

    //random data generator;
    // Using first seed
    init_aes_ctr_prf_state(&e_prf_state, MAX_AES_INVOKATION, &seeds.s1);

    DMSG("    Generating error.\n");
    res = generate_sparse_rep(e, T1, N_BITS, &e_prf_state); CHECK_STATUS(res);

#ifdef BIKE3
#ifdef INDCCA
    res = functionG_BIKE3(e_extra, e);
#else
    res = generate_sparse_rep(e_extra, T1/2, R_BITS, &e_prf_state);
#endif
#endif

    // computing ct = enc(pk, e)
    // Using second seed
    DMSG("    Encrypting.\n");
#ifdef BIKE3
    res = encrypt(l_ct, e, e_extra, l_pk, &seeds.s2);             	CHECK_STATUS(res);
#else
    res = encrypt(l_ct, e, 0, l_pk, &seeds.s2);             	CHECK_STATUS(res);
#endif

    DMSG("    Generating shared secret.\n");
#ifdef INDCCA
    res = get_ss_cca(l_ss, e, l_ct);                            CHECK_STATUS(res);
#else
    res = get_ss_cpa(l_ss, e);                                  CHECK_STATUS(res);
#endif

    EDMSG("ss: "); print((uint64_t*)l_ss->raw, sizeof(*l_ss)*8);

EXIT:

    DMSG("  Exit crypto_kem_enc.\n");
    return res;
}

//Decapsulate - ct is a key encapsulation message (ciphertext),
//              sk is the private key,
//              ss is the shared secret
int crypto_kem_dec(OUT unsigned char *ss,
        IN const unsigned char *ct,
        IN const unsigned char *sk)
{
    DMSG("  Enter crypto_kem_dec.\n");
    status_t res = SUCCESS;

    //Convert to this implementation types
    const sk_t* l_sk = (sk_t*)sk;
    const ct_t* l_ct = (ct_t*)ct;
    ss_t* l_ss = (ss_t*)ss;

    int failed = 0;
// declaring variables related to CCA variants:
#ifdef INDCCA
    ct_t ct_recomputed;
    //For NIST DRBG_CTR.
    double_seed_t seeds = {0};
    aes_ctr_prf_state_t e_prf_state = {0};
    // using ENCAPS_SEEDS flag because CCA decapsulation needs to re-encrypt the message:
    get_seeds(&seeds, ENCAPS_SEEDS);
#ifdef BIKE3
    uint8_t e_extra[R_SIZE]={0};
#endif
#endif

    DMSG("  Converting to compact rep.\n");
    uint32_t h0_compact[DV] = {0};
    uint32_t h1_compact[DV] = {0};
    convert2compact(h0_compact, l_sk->val0);
    convert2compact(h1_compact, l_sk->val1);

    DMSG("  Computing s.\n");
    syndrome_t syndrome;
    uint8_t e[R_BITS*2] = {0};
    uint8_t eBytes[N_SIZE] = {0};
    int rc;
    uint32_t u = 0; // For BIKE-1 and BIKE-2, u = 0 (i.e. syndrome must become a zero-vector)
    res = compute_syndrome(&syndrome, l_ct, l_sk); CHECK_STATUS(res);

    DMSG("  Decoding.\n");
#ifdef BIKE3
    u = T1/2; // For BIKE-3, u = t/2
#endif

#ifdef ROUND1_DECODER
    rc = decode_1st_round(e, syndrome.raw, h0_compact, h1_compact, u);
#else
#ifdef BACKFLIP_DECODER
    //rc = qcmdpc_decode_backflip_affine(e, syndrome.raw, h0_compact, h1_compact, u);
    rc = qcmdpc_decode_backflip_ttl(e, syndrome.raw, h0_compact, h1_compact, u);
#endif
#endif

    if (rc == 0)
    {
        DMSG("    Decoding result: success\n");
    }
    else
    {
        DMSG("    Decoding result: failure!\n");
        failed = 1;
    }

    convertBinaryToByte(eBytes, e, 2*R_BITS);

    // checking if error weight is exactly t:
    if (getHammingWeight(e, 2*R_BITS) != T1)
    {
      DMSG("Error weight is not t\n");
      failed = 1;
    }

#ifdef INDCCA

    // re-encryption required by CCA variants:
#ifdef BIKE3
    res = functionG_BIKE3(e_extra, eBytes);                                  CHECK_STATUS(res);
    res = encrypt(&ct_recomputed, eBytes, e_extra, &l_sk->l_pk, &seeds.s2);            CHECK_STATUS(res);
#else
    res = encrypt(&ct_recomputed, eBytes, 0, &l_sk->l_pk, &seeds.s2);   CHECK_STATUS(res);
#endif

    // compare the reconstructed ciphertext with received ciphertext:
#ifdef BIKE2
    if (memcmp(l_ct->raw, ct_recomputed.raw, R_SIZE) ) {
#else
    if (memcmp(l_ct->raw, ct_recomputed.raw, N_SIZE) ) {
#endif
        DMSG("crypto_kem_dec recovered bad ciphertext value\n");
        failed = 1;
    }

    // check if some process failed. If so, derive a key from sigma instead of e:
    if (failed) {
      res = get_ss_cca(l_ss, (uint8_t *) l_sk->sigmaraw, &ct_recomputed);                CHECK_STATUS(res);
    } else
    {
      res = get_ss_cca(l_ss, eBytes, &ct_recomputed);                CHECK_STATUS(res);
    }
#else
    res = get_ss_cpa(l_ss, eBytes);                CHECK_STATUS(res);
#endif

EXIT:

    DMSG("  Exit crypto_kem_dec.\n");
    return res;
}
