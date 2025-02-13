#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <set>
#include <algorithm>
#include <netinet/in.h>
#include <unistd.h>
#include "config.h"
#include <string.h>

std::vector<int> clients;
std::mutex clients_mutex;
std::ofstream logFile("chat.log", std::ios::app);

void broadcastMessage(const std::string &message, int sender_fd)
{
    std::lock_guard<std::mutex> lock(clients_mutex);

    logFile << message << std::endl; // Salva no histórico
    logFile.flush();

    for (int client_fd : clients)
    {
        if (client_fd != sender_fd)
        {
            send(client_fd, message.c_str(), message.size(), 0);
        }
    }
}

void handleClient(int client_fd)
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    std::string username(buffer);

    std::string joinMessage = username + " entrou no chat.";
    broadcastMessage(joinMessage, -1);

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0)
            break;

        std::string message = std::string(buffer);
        broadcastMessage(message, client_fd);
    }

    std::string leaveMessage = username + " saiu do chat.";
    broadcastMessage(leaveMessage, -1);

    close(client_fd);
    std::lock_guard<std::mutex> lock(clients_mutex);
    clients.erase(std::remove(clients.begin(), clients.end(), client_fd), clients.end());
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 10);

    std::cout << "Servidor iniciado na porta " << PORT << std::endl;

    while (true)
    {
        new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients.push_back(new_socket);
        std::thread(handleClient, new_socket).detach();
    }

    close(server_fd);
    return 0;
}
