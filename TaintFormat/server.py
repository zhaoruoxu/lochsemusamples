import socketserver
from datetime import datetime
import ctypes
import struct

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

class MyTcpHandler(socketserver.StreamRequestHandler):
	def getMessage(self):
		enc = rc4crypt(b"show me the code", b"gossip")
		r = struct.pack("i", len(enc)) + bytes(enc)
		print("Sending:", r)
		return r
		#return b'\x0e\x00\x00\x00Prophet rocks!\xf3\xf2\xf1\xf0hello world Prophet'

	def handle(self):
		self.data = self.rfile.readline().strip()
		print("{} {} wrote:".format(datetime.now(), self.client_address[0]))
		print(self.data)
		self.wfile.write(self.getMessage())

if __name__ == "__main__":
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

	