#include "aes.h"


int main( int argc, char *argv[] )
{
	unsigned char in[N_BLOCK];
	unsigned char out[N_BLOCK];
	unsigned char key[N_BLOCK];
	uint_8t o_key[N_BLOCK];
	
	memset( in, 1, N_BLOCK );
	memset( out, 0, N_BLOCK );
	memset( key, 2, N_BLOCK );
	memset( o_key, 0, N_BLOCK * sizeof(uint_8t) );
	
	aes_encrypt_128( in, out, key, o_key );
	
	return 0;
}
