/**
 * \file gf2x.cpp
 * \brief Implementation of multiplication of two polynomials
 */

#include <stdint.h>
#include <stdio.h>

/** 
 * \fn void ntl_cyclic_product(uint8_t*o, const uint8_t* v1, const uint8_t* v2)
 * \brief Multiply two vectors
 *
 * Vector multiplication is defined as polynomial multiplication performed modulo the polynomial \f$ X^n - 1\f$.
 *
 * \param[out] o Product of <b>v1</b> and <b>v2</b>
 * \param[in] v1 Pointer to the first vector
 * \param[in] v2 Pointer to the second vector
 */
void ntl_cyclic_product(uint8_t*o, const uint8_t* v1, const uint8_t* v2) {
    printf("%s:%d not implemented\n",__FILE__,__LINE__);
}
