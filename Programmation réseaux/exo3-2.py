import socket
import sys

if len(sys.argv) < 2:
    sys.exit("Usage: python client.py <chemin_fichier>")

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('127.0.0.1', 8080))

with open(sys.argv[1], "rb") as f:
    sock.sendall(f.read())

sock.close()