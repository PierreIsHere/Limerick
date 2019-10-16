import socket
import sys
TCP_IP = '127.0.0.1'
TCP_PORT = 7878
BUFFER_SIZE = 124

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((TCP_IP, TCP_PORT))

while True:
    data = client.recv(124)
