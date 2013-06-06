#include "stdafx.h"
#include "zeus.h"
#include "common.h"
#include "rc4test.h"
#include "md5test.h"
#include <openssl/sha.h>
#include <openssl/md5.h>

void ZeusEncrypt(void *buf, int len)
{
    for (int i = 1; i < len; i++) {
        ((byte *) buf)[i] ^= ((byte *) buf)[i-1];
    }
}

__declspec(noinline) 
void ZeusDecrypt(const void *ct, void *pt, int len)
{
    ((byte *) pt)[0] = ((byte *) ct)[0];
    for (int i = len - 1; i > 0; i--) {
        ((byte *) pt)[i] = ((byte *) ct)[i-1] ^ ((byte *) ct)[i];
    }
}

void GetRC4Key(byte *key)
{
    char compName[MAX_COMPUTERNAME_LENGTH+1];
    DWORD nSize = sizeof(compName);
    GetComputerNameA(compName, &nSize);

//     SHA_CTX sha;
//     SHA_Init(&sha);
//     SHA_Update(&sha, (byte *) compName, strlen(compName));
//     SHA_Final(key, &sha);

    SHA1((byte *) compName, strlen(compName), key);
}

void ProcessPayload(char *buf, int len);
void ProcessHttpPayload(byte *buf, int len);
void ProcessHttpPayloadFields(byte *buf, int len);
void ProcessC2Message(byte *buf, int len);
void ProcessCommandField(byte *buf, int len);

byte g_sessionId[20], g_sourceId[20];

void ZeusTest( char *buf, int len )
{
    char dec[BUF_LEN];
    ZeusDecrypt(buf, dec, len);

    ZeusHeader *header = (ZeusHeader *) dec;
    memcpy(g_sessionId, header->SessionID, sizeof(g_sessionId));
    memcpy(g_sourceId, header->SourceID, sizeof(g_sourceId));

    printf("Message type: %02x\n", header->Type);

    if (header->Type == 0xcc) {
        ProcessC2Message((byte *) dec + sizeof(ZeusHeader), len - sizeof(ZeusHeader));
    } else {
        printf("Unknown message type\n");
    }
}


void ProcessC2Message( byte *buf, int len )
{
    byte rc4key[20];
    ZeroMemory(rc4key, 20);
    GetRC4Key(rc4key);

    char payload[BUF_LEN];
    ZeroMemory(payload, BUF_LEN);
    RC4Crypt(payload, (const char *) buf, len, (const char *) rc4key, 20);

    //printf("Payload:\n%s\n", payload);
    ProcessPayload(payload, len - sizeof(ZeusHeader));
}

int g_xid;
__declspec(noinline)
void ProcessXID(const char *xidField)
{
    char buf[64];
    g_xid = atoi(xidField + 6);
    printf("xid = %d\n", g_xid);
}

__declspec(noinline)
bool ProcessHttpHeaderField(const char *field)
{
    if (StrPrefix(field, "X-ID")) {
        ProcessXID(field);
        return true;
    }
    return false;
}

__declspec(noinline) 
void ProcessPayload( char *buf, int len )
{
//     char *data = buf;
// 
//     int i = 0;
//     while (i < len - 1) {
//         if (buf[i] == '\r' && buf[i+1] == '\n') {
//             buf[i] = 0;
//             if (ProcessHttpHeaderField(data)) {
//                 data = buf + i + 2;
//                 break;
//             }
//             i += 2;
//             data = buf + i;
//         } else {
//             i++;
//         }
//     }

    char *data = strtok(buf, "\r\n");
    while (data != NULL) {
        if (StrPrefix(data, "X-ID")) {
            ProcessXID(data);
            data = strtok(NULL, "\r\n");
            //ProcessHttpPayload((byte *) data, len - (data - buf));
            break;
        }
        data = strtok(NULL, "\r\n");
    }
    ProcessHttpPayload((byte *) data, len - (data - buf));
}

__declspec(noinline) 
bool CheckFieldsHash(pbyte fields, ZeusHttpPayloadHeader *header)
{
    byte md[16];
//     MD5_CTX c;
//     MD5_Init(&c);
//     MD5_Update(&c, fields, header->MsgLen);
//     MD5_Final(md, &c);
    MD5(fields, header->MsgLen, md);
    return CompareByteArray(md, header->Hash, 16) == 0;
}

__declspec(noinline) 
void ProcessHttpPayload( byte *buf, int len )
{
    ZeusHttpPayloadHeader *header = (ZeusHttpPayloadHeader *) buf;
    printf("message length: %d\n", header->MsgLen);
    printf("message has %d fields\n", header->NumFields);

    if (CheckFieldsHash(buf + sizeof(ZeusHttpPayloadHeader), header)) {
        printf("Fields hash check okay\n");
    } else {
        printf("Fields hash check failed\n");
    }

    ProcessHttpPayloadFields(buf + sizeof(ZeusHttpPayloadHeader),
        header->MsgLen);
}

__declspec(noinline) 
void ProcessHttpPayloadFields( byte *buf, int len )
{
    ZeusFieldHeader *header = (ZeusFieldHeader *) buf;
    byte *data = buf + sizeof(ZeusFieldHeader);
    byte *decData = new byte[header->Size + 1];
    ZeroMemory(decData, header->Size + 1);
    ZeusDecrypt(data, decData, header->Size);
    //printf("data: %s\n", decData + 1);
    if (header->Type == 0x1) {
        ProcessCommandField(decData + 1, header->Size - 1);
    } else {
        printf("Unknown field type: %02x\n", header->Type);
    }
}

__declspec(noinline)
void DDosUrl(const char *url)
{
    printf("DDOS URL: %s\n", url);
}

__declspec(noinline)
void ProcessCommandField( byte *buf, int len )
{
    byte *md5hash = buf;
    char *cmd = (char *) buf + 16;

    byte md[16];
    MD5((byte *) cmd, len - 16, md);

    if (CompareByteArray(md, md5hash, 16) == 0) {
        printf("hash match\n");
    }

    //printf("cmd = %s\n", cmd);

    char *p = strtok(cmd, " ");
    if (strcmp(p, "ddos_url") == 0) {
        DDosUrl(p + strlen(p) + 1);
    } else {
        printf("Unknown command\n");
    }
}
