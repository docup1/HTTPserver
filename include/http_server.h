/*
* http_server.h
 * Заголовочный файл, содержащий объявления структур и функций для работы HTTP-сервера.
 */

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "http_types.h"

#define PORT 5465           // Порт, на котором будет работать сервер
#define BUFFER_SIZE 1024    // Размер буфера для передачи данных

// Структура для представления HTTP-запроса
typedef struct {
    char method[8];   // HTTP-метод (например, GET, POST)
    char path[256];   // Запрошенный путь (например, "/")
    char version[16]; // Версия протокола (например, HTTP/1.1)
} HttpRequest;

// Структура для представления HTTP-ответа
typedef struct {
    HttpStatus status;         // Код статуса HTTP (например, 200, 404)
    ContentType content_type;  // Тип содержимого (HTML, JSON, plain text)
    const char *content;       // Тело ответа
} HttpResponse;

#ifdef __cplusplus
extern "C" {
#endif

    // Функция для разбора HTTP-запроса из входящего буфера
    void parse_request(const char *buffer, HttpRequest *request);
    // Функция для отправки HTTP-ответа клиенту
    void send_response(int client_socket, HttpResponse *response);
    // Функция для обработки подключения клиента (принимает запрос и отправляет ответ)
    void handle_client(int client_socket);
    // Функция для получения строкового представления типа содержимого
    const char* get_content_type_str(ContentType type);

#ifdef __cplusplus
}
#endif

#endif // HTTP_SERVER_H
