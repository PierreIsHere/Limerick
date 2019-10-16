import socket
import sys
from _thread import *
from account import *

host = ''
port = 7878
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
try:
    s.bind((host, port))
except socket.error as e:
    print(str(e))

s.listen(5)
print('Waiting for a connection.')


def threaded_client(conn):
    # loginInit(conn)
    while True:
        data = conn.recv(124)
        data = data.decode('utf-8')
        print(data+str(conn))
        if not data:
            break

    conn.close()

while True:

    conn, addr = s.accept()
    start_new_thread(threaded_client,(conn,))
