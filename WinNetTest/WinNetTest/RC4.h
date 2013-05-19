#ifndef _RC_4
#define _RC_4

void RC4(char *key, char *plaintext, char *chipertext,int keylen,int textlen)
{ 
	char S[256];
	char T[256];
	for (int i = 0; i < 256; i++)
	{
		S[i] = i;
		T[i] = key[i % keylen];
	}

	int j = 0;
	for (int i = 0; i < 256; i++)
	{
		j = (j + S[i] + T[i]) % 256;
		int tmp = S[i];
		S[i] = S[j];
		S[j] = tmp;
	}

	int i = 0;
	j = 0;
	for (int a = 0; a < textlen; a++)
	{
		i = (i+1) % 256;
		j = (j + S[i]) %256;
		int tmp = S[i];
		S[i] = S[j];
		S[j] = tmp;
		chipertext[a] = plaintext[a]^S[(S[i] + S[j]) % 256];
	}
}


#endif