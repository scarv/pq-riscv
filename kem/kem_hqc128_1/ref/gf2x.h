/**
 * \file gf2x.h
 * \brief Header file for gf2x.cpp
 */

#ifndef GF2X_H
#define GF2X_H

#include <inttypes.h>

#include "parameters.h"

void ntl_cyclic_product(uint8_t*o, const uint8_t* v1, const uint8_t* v2);

#endif
