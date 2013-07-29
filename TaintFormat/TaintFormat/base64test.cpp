
#include "stdafx.h"
#include "common.h"
#include "base64test.h"

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'};
static char decoding_table[256];
static int mod_table[] = {0, 2, 1};


char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) 
{

    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = (char *) malloc(*output_length);
    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}


void base64_decode(const char *data, size_t input_length, byte *buf, size_t *output_length) 
{
    if (input_length % 4 != 0) return;

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;

    //unsigned char *decoded_data = (byte *) malloc(*output_length);
    //if (decoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
            + (sextet_b << 2 * 6)
            + (sextet_c << 1 * 6)
            + (sextet_d << 0 * 6);

        if (j < *output_length) buf[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) buf[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) buf[j++] = (triple >> 0 * 8) & 0xFF;
    }

    //return decoded_data;
}


void build_decoding_table() 
{
    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char) encoding_table[i]] = i;
}

void Base64Test( char *buf, int len )
{
    build_decoding_table();
    int l = reinterpret_cast<int *>(buf)[0];
    size_t decLen;
    byte decbuf[256];
    ZeroMemory(decbuf, sizeof(decbuf));
    base64_decode(buf + sizeof(int), len - 4, decbuf, &decLen);
    printf("decoded = %s\n", decbuf);
    printf("l should be %d, actual %d\n", l, decLen);
}

