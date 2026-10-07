import socket

# UDP server settings
UDP_IP = "0.0.0.0"   # listen on all interfaces
UDP_PORT = 2055      # port to listen on

# Create UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

print(f"Listening for UDP packets on {UDP_IP}:{UDP_PORT} ...")

while True:
    data, addr = sock.recvfrom(4096)  # buffer size 4096 bytes
    print(f"Received {len(data)} bytes from {addr}: {data.decode(errors='ignore')}")
