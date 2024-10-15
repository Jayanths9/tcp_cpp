#include <iostream>
#include <string.h>
#include <unistd.h>  // for close()
#include <arpa/inet.h> // for socket functions

int main() {
    const char* HOST = "192.168.1.104"; // Server's IP address
    const int PORT = 8080;               // Port to listen on (non-privileged ports are > 1023)

    // Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        return -1;
    }

    // Define server address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(HOST);
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return -1;
    }

    // Start listening for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        return -1;
    }

    std::cout << "Server listening on " << HOST << ":" << PORT << std::endl;

    while (true) {
        // Accept a new connection
        sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }

        std::cout << "Connected by " << inet_ntoa(client_addr.sin_addr) << std::endl;

        while (true) {
            char buffer[1024] = {0}; // Buffer to receive data
            ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
            if (bytes_received <= 0) {
                std::cout << "Connection closed by " << inet_ntoa(client_addr.sin_addr) << std::endl;
                break;
            }

            std::cout << "Received: " << buffer << " from " << inet_ntoa(client_addr.sin_addr) << std::endl;
            send(client_fd, buffer, bytes_received, 0); // Echo the received data back to the client
        }

        close(client_fd); // Close the client socket
    }

    close(server_fd); // Close the server socket
    return 0;
}
