#include "rand.h"
#include "common/rng.h"
#include "lac_param.h"
#include <string.h>
//#include <openssl/rand.h>
//#include <openssl/aes.h>
//#include <openssl/sha.h>
//#include <openssl/crypto.h>
//#include <openssl/evp.h>
//random bytes
int random_bytes(unsigned char *r, unsigned int len)
{
	//check parameter
	if(r==NULL)
	{
		return 1;
	}
	// call the random function 
//	RAND_bytes(r,len);
	randombytes(r,len);
	return 0;
}

//pseudo-random bytes
int pseudo_random_bytes(unsigned char *r, unsigned int len, const unsigned char *seed)
{

    char diversifier[16];
    memset(diversifier,0,16);

    AES_XOF_struct ctx;
    seedexpander_init(&ctx,seed,diversifier,len);
    seedexpander(&ctx,r,len);

	return 0;
}

//hash
int hash(const unsigned char *in, unsigned int len_in, unsigned char * out)
{
	//check  parameter
	if(in==NULL || out==NULL)
	{
		return 1;
	}
  
	#if defined LAC128
	sha256(out,in,len_in);
	#endif
	
	#if defined LAC192
	sha256(out,in,len_in);
	#endif

	#if defined LAC256
	sha256(out,in,len_in);
	#endif

	
	return 0;
}

//generate seed
int gen_seed(unsigned char *in, unsigned int len_in, unsigned char * out)
{
	//check  parameter
	if(in==NULL || out==NULL)
	{
		return 1;
	}
	
	sha256(out,in,len_in);
	return 0;
}

