#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

//gcc main.c -lws2_32

int main(int argc, char const *argv[])
{
    // Создаем структуру, которая содержит информацию о реализации сокетов
    WSADATA ws;
    if (WSAStartup(MAKEWORD(2,2), &ws))
    {
        // Сообщаем пользователю, что не нашли подходящию Winsock DLL
        printf("[ERROR]: not find Winsock DLL");
        return 0;
    }

    // Создаем сервер сокет
    SOCKET server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Определяем адресс сервера
    SOCKADDR_IN server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_family = htons(8080);

    // Привязываем сокет к нашему ip и port
    bind(server_socket, (SOCKADDR *) &server_address, sizeof(server_address));

    // Сколько соединений может слушать сокет
    listen(server_socket, 5);


    // Создание сокета клиента
    SOCKET client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // Отправка сообщения
    char server_message[] = "Success!";
    send(client_socket, server_message, sizeof(server_message), 0);

    // Отстановка сокета сервера
    closesocket(server_socket);

    return 0;
}
