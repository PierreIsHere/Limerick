from pynput import keyboard
import time
import socket

TCP_IP = ''
TCP_PORT = 7878
BUFFER_SIZE = 124       
v = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
v.connect(("8.8.8.8", 80))
ipAddr = v.getsockname()[0]
print(v.getsockname()[0])
v.close()
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((TCP_IP, TCP_PORT))  
l="Connection is Up and Running"
n = "You are connected to: "+ipAddr
name = "Computer Name : "+socket.gethostname()
client.send(l.encode())
time.sleep(0.3)
client.send(n.encode())
time.sleep(0.3) 
client.send(name.encode())
while True:
    client.send(input().encode())     
