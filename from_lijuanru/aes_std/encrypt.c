#include <stdio.h>
#include "rijndael.h"

#define KEYBITS 128

int main(int argc, char **argv)
{
	unsigned long rk[RKLENGTH(KEYBITS)];
	unsigned char key[KEYLENGTH(KEYBITS)] = {2};
	int i;
	int nrounds;
	unsigned char plaintext[16] = {1};
	unsigned char ciphertext[16] = {0};

	/*
	if (argc < 3)
	{
	fputs("Missing argument\n", stderr);
	return 1;
	}
	*/
	
	nrounds = rijndaelSetupEncrypt(rk, key, KEYBITS);
	rijndaelEncrypt(rk, nrounds, plaintext, ciphertext);
	
	return nrounds;
}
