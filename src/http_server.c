/*
 * http_server.c
 * Реализация функций для разбора HTTP-запросов, формирования HTTP-ответов и их отправки.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "http_server.h"

// Функция разбора HTTP-запроса.
// Извлекает метод, путь и версию из входящего запроса.
void parse_request(const char *buffer, HttpRequest *request) {
    // Используется sscanf для извлечения данных из строки запроса
    sscanf(buffer, "%7s %255s %15s", request->method, request->path, request->version);
}

// Функция получения строкового представления типа контента.
// На основе перечисления ContentType возвращает соответствующую строку.
const char* get_content_type_str(ContentType type) {
    switch (type) {
        case CONTENT_TEXT_HTML: return "text/html";
        case CONTENT_APPLICATION_JSON: return "application/json";
        default: return "text/plain";
    }
}

// Функция отправки HTTP-ответа клиенту.
void send_response(int client_socket, HttpResponse *response) {
    const char *status_text;

    // Выбор текстового представления статуса ответа по его коду
    switch (response->status) {
        case HTTP_OK: status_text = "200 OK"; break;
        case HTTP_BAD_REQUEST: status_text = "400 Bad Request"; break;
        case HTTP_UNAUTHORIZED: status_text = "401 Unauthorized"; break;
        case HTTP_FORBIDDEN: status_text = "403 Forbidden"; break;
        case HTTP_NOT_FOUND: status_text = "404 Not Found"; break;
        case HTTP_METHOD_NOT_ALLOWED: status_text = "405 Method Not Allowed"; break;
        case HTTP_REQUEST_TIMEOUT: status_text = "408 Request Timeout"; break;
        case HTTP_CONFLICT: status_text = "409 Conflict"; break;
        case HTTP_PAYLOAD_TOO_LARGE: status_text = "413 Payload Too Large"; break;
        case HTTP_UNSUPPORTED_MEDIA_TYPE: status_text = "415 Unsupported Media Type"; break;
        case HTTP_INTERNAL_SERVER_ERROR: status_text = "500 Internal Server Error"; break;
        case HTTP_NOT_IMPLEMENTED: status_text = "501 Not Implemented"; break;
        case HTTP_BAD_GATEWAY: status_text = "502 Bad Gateway"; break;
        case HTTP_SERVICE_UNAVAILABLE: status_text = "503 Service Unavailable"; break;
        case HTTP_GATEWAY_TIMEOUT: status_text = "504 Gateway Timeout"; break;
        default: status_text = "500 Internal Server Error"; break;
    }

    char buffer[BUFFER_SIZE];
    // Вычисление длины содержимого ответа с учётом завершающего символа
    int content_length = strlen(response->content) + 1;

    // Формирование строки HTTP-ответа с заголовками и телом
    snprintf(buffer, BUFFER_SIZE,
             "HTTP/1.1 %s\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %d\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%s\n",
             status_text, get_content_type_str(response->content_type), content_length, response->content);

    // Отправка ответа клиенту
    send(client_socket, buffer, strlen(buffer), 0);
    // Закрытие соединения с клиентом
    close(client_socket);
}

// Функция обработки подключения клиента.
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    // Получение данных от клиента
    int received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (received < 0) {
        perror("Ошибка получения данных");
        close(client_socket);
        return;
    }
    // Завершение строки нулевым символом
    buffer[received] = '\0';

    HttpRequest request;
    // Разбор полученного запроса
    parse_request(buffer, &request);
    printf("Получен запрос: %s %s %s\n", request.method, request.path, request.version);

    HttpResponse response;
    // Если запрошен корневой путь ("/"), формируется ответ с приветствием
    if (strcmp(request.path, "/") == 0) {
        response.status = HTTP_OK;
        response.content_type = CONTENT_TEXT_HTML;
        response.content = "<h1>Hello world</h1>";
    } else {
        // Для всех остальных запросов возвращается ошибка 404 "Не найдено"
        response.status = HTTP_NOT_FOUND;
        response.content_type = CONTENT_TEXT_HTML;
        response.content = "<h1>404 Не найдено</h1>";
    }

    // Отправка сформированного ответа клиенту
    send_response(client_socket, &response);
}
