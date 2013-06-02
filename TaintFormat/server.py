import socketserver
from datetime import datetime
import ctypes
import struct
from pyDes import *

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
    
    return out

def getRC4Message():
	enc = rc4crypt(b"show me the code", b"gossip")
	return struct.pack("i", len(enc)) + bytes(enc)
	
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
		return b"Unknown method"
		

	def handle(self):
		self.method = self.rfile.readline().strip()
		print("{} {} wrote:".format(datetime.now(), self.client_address[0]))
		print(self.method)
		self.wfile.write(self.getMessage(self.method))

if __name__ == "__main__":
	#getMegaDMessage()
	ctypes.windll.kernel32.SetConsoleTitleA(b"Server")
	HOST, PORT = "localhost", 56789
	server = socketserver.TCPServer((HOST, PORT), MyTcpHandler)
	print("Running server at {} port {}".format(HOST, PORT))
	server.serve_forever()
	#key = b"secret"
	#x = rc4crypt(b"hahahehehohohihi", key)
	#print(bytes(x))
	#y = rc4crypt(x, key)
	#print(bytes(y))
	#print(struct.pack("i", len(y)) + bytes(y))

	