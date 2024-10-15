import socket

HOST = "192.168.1.104"  # Server's IP address
PORT = 8080  # Port to listen on (non-privileged ports are > 1023)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print(f"Server listening on {HOST}:{PORT}")

    while True:
        conn, addr = s.accept()  # Accept a new connection
        with conn:
            print(f"Connected by {addr}")
            while True:
                data = conn.recv(1024)  # Receive data from the client
                if not data:
                    print(f"Connection closed by {addr}")
                    break
                print(f"Received {data!r} from {addr}")
                conn.sendall(data)  # Echo the received data back to the client
