/*
* http_types.h
 * Заголовочный файл, содержащий определения перечислений HTTP-статусов и типов содержимого.
*/

#ifndef HTTP_TYPES_H
#define HTTP_TYPES_H

// Перечисление HTTP-статусов, используемых в ответах сервера
typedef enum {
    HTTP_OK = 200,
    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_FORBIDDEN = 403,
    HTTP_NOT_FOUND = 404,
    HTTP_METHOD_NOT_ALLOWED = 405,
    HTTP_REQUEST_TIMEOUT = 408,
    HTTP_CONFLICT = 409,
    HTTP_PAYLOAD_TOO_LARGE = 413,
    HTTP_UNSUPPORTED_MEDIA_TYPE = 415,
    HTTP_INTERNAL_SERVER_ERROR = 500,
    HTTP_NOT_IMPLEMENTED = 501,
    HTTP_BAD_GATEWAY = 502,
    HTTP_SERVICE_UNAVAILABLE = 503,
    HTTP_GATEWAY_TIMEOUT = 504
} HttpStatus;

// Перечисление типов содержимого, используемых в ответах сервера
typedef enum {
    CONTENT_TEXT_PLAIN,
    CONTENT_TEXT_HTML,
    CONTENT_APPLICATION_JSON
} ContentType;

#endif // HTTP_TYPES_H
