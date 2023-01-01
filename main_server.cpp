#include "common.h"
#include <time.h>

int main()
{
    srand(time(nullptr));
    auto server_address = local_addr(SERVER_PORT);
    auto listening_socket = check(make_socket(SOCKET_TYPE));
    int connected_socket = 0;

    int guess = rand() % 10;
    std::cout << "YOU JUST ENTERED PIRATE GAME SERVER" << std::endl;
    std::cout << "Guess " << guess << ", boy!"<< std::endl;

    check(bind(listening_socket, (sockaddr*)&server_address, sizeof(server_address)));
    check(listen(listening_socket, 2));

    while (true)
    {
        sockaddr_in connected_address{};
        socklen_t addrlen = sizeof(connected_socket);
        connected_socket = check(accept(listening_socket, (sockaddr*)&connected_address,
                                        &addrlen));
        std::cout << "Connected from " << connected_address << std::endl;
        int buffer = -1;
        while (true)
        {
            int size = recv(connected_socket, &buffer, sizeof(int), MSG_WAITALL);
            if (size == 0 || (size < 0 && errno == ENOTCONN))
                break; //disconnected
            check(size);
            std::cout << connected_address << " send an value: " << buffer << std::endl;
            if (guess == buffer)
            {
                int answ = -1;
                std::cout << "AAARGH!!! You're goddamn right, kid!" << std::endl;
                guess = rand() % 10;
                std::cout << "Now guess " << guess << std::endl;
                send(connected_socket, &answ, sizeof(int), MSG_WAITALL);
            }
            else
                std::cout << "You are fool!" << std::endl;
                send(connected_socket, &buffer, sizeof(int), MSG_WAITALL);
        }
        std::cout << "Disconnected from " << connected_address << std::endl;
    }
}
