import socketserver
from datetime import datetime
import ctypes

class MyTcpHandler(socketserver.StreamRequestHandler):
	def getMessage(self):
		return b'\x0e\x00\x00\x00Prophet rocks!\x23\x22\x21\x20hello world Prophet'

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
