import socketserver
from datetime import datetime
import ctypes
import struct
from pyDes import *
import hashlib
import socket
import base64
import functools

def rc4crypt(data, key):
    x = 0
    box = list(range(256))
    for i in range(256):
        x = (x + box[i] + key[i % len(key)]) % 256
        box[i], box[x] = box[x], box[i]
    x = 0
    y = 0
    out = []
    for char in data:
        x = (x + 1) % 256
        y = (y + box[x]) % 256
        box[x], box[y] = box[y], box[x]
        out.append(char ^ box[(box[x] + box[y]) % 256])
    return bytes(out)

def zeusEncrypt(data):
    r = []
    r.append(data[0])
    for i in range(1, len(data)):
        r.append(data[i] ^ r[i-1])
    return bytes(r)
def getZeusRC4Key():
    compName = socket.gethostname().upper()
    m = hashlib.sha1()
    m.update(compName.encode("ascii"))
    return m.digest()

def getC2HttpHeader(contentLen):
    r = "POST /write HTTP/1.1\r\n"
    r += "Content-Length: %d\r\n" % (contentLen)
    r += "Accpet-Encoding:\r\nConnection: close\r\nX-ID: 96730\r\n"
    return bytes(r, "ascii")

def getZeusHeader():
    r = b"\xA6\xEB\x00\xCC"
    m = hashlib.sha1()
    m.update(b"Session #7859")
    r += m.digest()
    r += getZeusRC4Key()
    return r

def getZeusCommandField():
    r = b"ddos_url http://us.blizzard.com/en-us/"
    m = hashlib.md5()
    m.update(r)
    r = m.digest() + r
    print(r)
    return r

def getZeusHttpPayloadField():
    data = getZeusCommandField()
    r = zeusEncrypt(b'\x96' + data)
    return struct.pack("iiii", 1, 0, len(r), len(r)) + r

def getZeusHttpPayloadHeader(nFields, fields):
    r = struct.pack("iii", len(fields), 0, nFields)
    m = hashlib.md5()
    m.update(fields)
    r += m.digest()
    return r

def getZeusHttpPayload():
    field = getZeusHttpPayloadField()
    header = getZeusHttpPayloadHeader(1, field)
    return header + field

def getZeusPayload():
    payload = getZeusHttpPayload()
    r = getC2HttpHeader(len(payload))
    return r + payload

def getZeusMessage():
    header = getZeusHeader()
    payload = getZeusPayload()
    payload = rc4crypt(payload, getZeusRC4Key())
    r = zeusEncrypt(header + payload)
    return r

def getMD5Message():
    r = b"Show Me The Code! Hans Zimmer is God."
    m = hashlib.md5()
    m.update(r)
    return m.digest() + r

def getRC4Message():
    enc = rc4crypt(b"show me the code", b"gossip")
    return struct.pack("i", len(enc)) + enc

def getMegaD_INFO():
    return b"\x01\x00\x00\x01\x86\x61\xa4\xf6\xa3\x25\xdf\x11\x85\x67\xf4\x7e\x37\x7c\x00\x00\x00\x00\x00\x3c\xce\x59\x00\x00\xa8\xd0\x82\x01"
    
def getMegaDMessage():
    data = getMegaD_INFO()
    key = b"abcdefgh"
    k = des(key, ECB, pad = b'\0')
    d = k.encrypt(data)
    print("encrypted:", d)
    print("decrypted:", k.decrypt(d))
    print(len(d))
    return struct.pack(">H", len(d) // 8) + d
    
def getBase64Message():
    s = b"Prophet rocks!"
    return struct.pack("i", len(s)) + base64.b64encode(s)

def getStormMessage():
    s = b"http://us.blizzard.com/en-us/"
    b_xor, b_add = 0, 0
    for x in s:
        b_xor ^= x
        b_add = (b_add + x) % 256
    print(b_xor, b_add)
    b_cnt = 0x67
    r = stormEncrypt(struct.pack("BBB", b_xor, b_add, b_cnt) + s)
    print(r)
    return r
    #r = stormEncrypt(b'\x01\x02\x03')
    
    #print(r)
    #return r

def stormEncrypt(pt):
    padded = pt[:]
    if len(pt) % 3 == 1:
        padded += b'\0\0'
    elif len(pt) % 3 == 2:
        padded += b'\0'
    r = []
    for i in range(len(padded) // 3):
        r.append((padded[i*3] >> 2) + 0x21)
        r.append(((padded[i*3] & 0x3) << 4) + (padded[i*3+1] >> 4) + 0x21)
        r.append(((padded[i*3+1] & 0xf) << 2) + (padded[i*3+2] >> 6) + 0x21)
        r.append((padded[i*3+2] & 0x3f) + 0x21)
    print(r)
    return bytes(r)

def getZeroAccessMessage():
    return b'\xd6\xf9\xe4\x02\x08\x9a\x95\x9b\x1a\x4a\x65\x29\x4d\x9b\x39\xc1\x6b\x7d\xb6\x4c'

def getMessage(method):
    if method == b"rc4":
        return getRC4Message()
    elif method == b"mega-d":
        return getMegaDMessage()
    elif method == b"zeus":
        return getZeusMessage()
    elif method == b"md5":
        return getMD5Message()
    elif method == b"base64":
        return getBase64Message()
    elif method == b"storm":
        return getStormMessage()
    elif method == b"zeroaccess":
        return getZeroAccessMessage()
    return b"Unknown method"

def main(argv):
    ctypes.windll.kernel32.SetConsoleTitleA(b"Server")

    HOST, PORT = "localhost", 56789

    print("Running server at {} port {}".format(HOST, PORT))
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(5)
    while True:
        print("Waiting for connection...")
        sock, addr = s.accept()
        print("Connection from ", addr)
        
        #try:
        while True:
            data = sock.recv(1024)
            print("{} {} wrote:".format(datetime.now(), addr), data)
            if not data:
                break
            sock.send(getMessage(data))
        sock.close()
        #except:
        #    print("exception:", sys.exc_info()[0])
        #    sock.close()
    
    #server = socketserver.TCPServer((HOST, PORT), MyTcpHandler)
    #
    #server.serve_forever()


if __name__ == "__main__":
    #getMegaDMessage()
    #print(getZeusMessage())
    
    #print(rc4crypt(getC2HttpHeader(200), getZeusRC4Key()))
    #print(getZeusHeader())
    #

    #print(getStormMessage())
    main(sys.argv)
    
    #key = b"secret"
    #x = rc4crypt(b"hahahehehohohihi", key)
    #print(bytes(x))
    #y = rc4crypt(x, key)
    #print(bytes(y))
    #print(struct.pack("i", len(y)) + bytes(y))

    
