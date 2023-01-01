#include "common.h"
#include <string>

bool GameMode()
{
    int game_mode;
    std::cout << "Task 1: By yourself" << std::endl;
    std::cout << "Task 2: By machine" << std::endl;
    while (game_mode < 1 || game_mode > 2 )
        std::cin >> game_mode;
    if (game_mode == 1)
        return true;
    return false;
}

int MakeAssumption(sockaddr_in dest_address, int sock_fd, bool game_mode)
{
    int message = -1;
    if (game_mode)
    {
        std::cout << "Input your assumption ";
        std::cin >> message;
    }
    else
        message = rand() % 10;
    send(sock_fd, &message, sizeof(int), MSG_WAITALL);
    return message;
}

bool Recieve(sockaddr_in dest_address, int sock_fd, int message, bool game_mode)
{
    int answer = -1;
    int size = recv(sock_fd, &answer, sizeof(int), MSG_WAITALL);
    if (size == 0 || (size < 0 && errno == ENOTCONN))
        throw std::logic_error("Size < 0");
    if (!game_mode)
        std::cout << message << std::endl;
    if (answer == -1)
    {
        std::cout << "Game over!" << std::endl;
        return true;
    }
    sleep(1);
    return false;
}


int main()
{
    bool game_mode = GameMode();
    auto dest_address = local_addr(SERVER_PORT);
    srand(getpid());
    int sock_fd = check(make_socket(SOCKET_TYPE));
    check(connect(sock_fd, (sockaddr*)&dest_address, sizeof(dest_address)));

    int message;
    while(true) {
        message = MakeAssumption(dest_address, sock_fd, game_mode);
        if (Recieve(dest_address, sock_fd, message, game_mode))
            break;
    }
    shutdown(sock_fd, SHUT_RDWR);
    close(sock_fd);
}