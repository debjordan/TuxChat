#include <iostream>
#include <thread>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include "config.h"
#include <string.h>
#include <algorithm>

std::string username;

void receiveMessages(int sock)
{
    char buffer[1024];
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0)
            break;
        std::cout << buffer << std::endl;
    }
    close(sock);
    exit(0);
}

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "Erro ao conectar no servidor." << std::endl;
        return 1;
    }

    std::cout << "Digite seu nome de usuário: ";
    std::getline(std::cin, username);
    std::transform(username.begin(), username.end(), username.begin(), ::toupper);

    send(sock, username.c_str(), username.size(), 0);

    std::cout << "Conectado ao chat como [" << username << "]!" << std::endl;

    std::thread(receiveMessages, sock).detach();

    std::string message;
    while (true)
    {
        std::getline(std::cin, message);
        std::string fullMessage = "[" + username + "]: " + message;
        send(sock, message.c_str(), message.size(), 0);
    }

    close(sock);
    return 0;
}
