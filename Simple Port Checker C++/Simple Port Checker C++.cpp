#include <iostream>
#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsaData;
    WORD wVersionRequested{ MAKEWORD(2,2) };        // MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    int err{ WSAStartup(wVersionRequested, &wsaData) };
    if (err != 0)
    {
        std::cout << "WSAStartup failed with error: " << err;
        return 1;
    }
    else
    {
        // Sock
        SOCKET listenSocket;
        struct sockaddr_in sockAddress {};

        // Getting IP
        char ip[20]; // 15
        std::cout << "IP Address: ";
        std::cin.get(ip, 20);
        std::cin.clear();

        // Getting ports
        unsigned short startingPort, endingPort;
        std::cout << "Starting port: ";
        std::cin >> startingPort;
        std::cout << "Ending port: ";
        std::cin >> endingPort;

        // Scanning
        for (unsigned short index = startingPort; index <= endingPort; ++index)
        {
            // Socket Setup
            listenSocket = socket(AF_INET, SOCK_STREAM, 0);
            sockAddress.sin_family = PF_INET;
            sockAddress.sin_addr.s_addr = inet_addr(ip);
            sockAddress.sin_port = htons(index);

            // Connect to socket
            int status{ connect(listenSocket, (struct sockaddr*)&sockAddress, sizeof(struct sockaddr)) };
            if (status == 0)
            {
                std::cout << "Port " << index << " : OPEN\n";
                closesocket(listenSocket);
            }
            else
                std::cout << "Port " << index << " : CLOSED\n";
        }
        WSACleanup();
    }
    return 0;
}