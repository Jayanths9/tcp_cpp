import socket
import time

HOST = "192.168.1.104"  # Server's address
PORT = 8080  # Port to connect to

try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))

        while True:
            message = b"Hello, jayanth"  # Your message to send
            s.sendall(message)
            data = s.recv(1024)  # Receive response
            print(f"Received {data!r}")
            time.sleep(1)  # Sleep for 1 second before sending the next message

except KeyboardInterrupt:
    print("Stopped by user.")

except Exception as e:
    print(f"An error occurred: {e}")
