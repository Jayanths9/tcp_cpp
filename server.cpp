#include <iostream>
#include <string.h>
#include <unistd.h>  // for close()
#include <arpa/inet.h> // for socket functions
#include <chrono>
#include <thread>

int main() {
    const char* HOST = "192.168.1.104"; // Server's IP address
    const int PORT = 8080;               // Port to connect to

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        return -1;
    }

    // Define server address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(HOST);
    server_addr.sin_port = htons(PORT);

    // Connect to server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return -1;
    }

    std::cout << "Connected to server at " << HOST << ":" << PORT << std::endl;

    try {
        while (true) {
            const char* message = "Hello, Jayanth"; // Your message to send
            send(sock, message, strlen(message), 0); // Send the message

            char buffer[1024] = {0}; // Buffer to receive response
            ssize_t bytes_received = recv(sock, buffer, sizeof(buffer), 0); // Receive response
            if (bytes_received > 0) {
                std::cout << "Received: " << buffer << std::endl; // Print received message
            }

            std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second before sending the next message
        }
    } catch (...) {
        std::cout << "Stopped by user." << std::endl;
    }

    close(sock); // Close the socket
    return 0;
}
