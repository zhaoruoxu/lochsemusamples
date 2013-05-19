import sys
import socket
import time

Server = 'localhost'
Port = 56789

def main(argv):
	global Server, Port
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.connect((Server, Port))
	time.sleep(1)
	sock.send(b'\x05\x00\x00\x00hello')
	sock.send(b'\x04\x00\x00\x00quit')
	sock.close()


if __name__ == '__main__':
	main(sys.argv)
	# print((0, 1) + (2, 3))
