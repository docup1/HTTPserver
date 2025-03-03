/*
 * main.c
 * Простейший HTTP-сервер на C, который принимает подключения,
 * обрабатывает HTTP-запросы и отправляет ответы клиенту.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "http_server.h"

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_length = sizeof(client_address);

    // Создание TCP-сокета
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера: использование IPv4, любого IP-адреса (INADDR_ANY) и порта PORT
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Привязка сокета к указанному адресу и порту
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Ошибка привязки сокета");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Начало прослушивания входящих подключений (максимум 10 одновременных соединений)
    if (listen(server_socket, 10) < 0) {
        perror("Ошибка ожидания подключений");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("HTTP-сервер слушает порт %d...\n", PORT);

    // Основной цикл сервера: ожидание и обработка подключений клиентов
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_length);
        if (client_socket < 0) {
            perror("Ошибка принятия соединения");
            continue;
        }
        // Функция handle_client обрабатывает запрос клиента
        handle_client(client_socket);
    }

    // Закрытие серверного сокета (этот код в принципе не будет достигнут из-за бесконечного цикла)
    close(server_socket);
    return 0;
}
