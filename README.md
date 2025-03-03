# Простой HTTP-сервер на C

Этот проект представляет собой простой HTTP-сервер, написанный на языке C, который принимает входящие подключения, обрабатывает HTTP-запросы и отправляет ответы клиенту.

## Описание

Сервер реализован с использованием стандартных библиотек C. Основной функционал включает:
- Разбор HTTP-запросов (функция `parse_request`)
- Формирование HTTP-ответов (функции `send_response` и `handle_client`)
- Поддержку различных HTTP-статусов и типов содержимого

## Структура проекта

Проект организован следующим образом:

```
.
├── Makefile         # Файл для сборки проекта
├── include          # Каталог с заголовочными файлами
│   ├── http_server.h
│   └── http_types.h
├── src              # Каталог с исходными файлами
│   ├── main.c
│   └── http_server.c
├── obj              # Каталог для объектных файлов (создаётся автоматически)
└── bin              # Каталог для исполняемого файла (создаётся автоматически)
```

## Сборка проекта

Проект использует Makefile для сборки. Для компиляции выполните следующие шаги:

1. Откройте терминал в корневой директории проекта.
2. Запустите команду:
   ```bash
   make
   ```
   Эта команда скомпилирует исходные файлы, создаст объектные файлы в каталоге `obj` и соберёт исполняемый файл `http_server` в каталоге `bin`.

## Запуск сервера

После сборки запустите сервер командой:
```bash
./bin/http_server
```

Сервер будет слушать порт **5465**. Для проверки работы сервера:
- Откройте браузер и перейдите по адресу: [http://localhost:5465/](http://localhost:5465/)
- Или используйте утилиту `curl`:
  ```bash
  curl http://localhost:5465/
  ```

При обращении к корневому пути (`/`) сервер вернёт HTML-страницу с сообщением "Hello world". Для всех остальных путей возвращается ошибка **404 Not Found**.

## Очистка проекта

Чтобы удалить сгенерированные объектные файлы и исполняемый файл, выполните:
```bash
make clean
```

## Освобождение занятого порта

Если сервер аварийно завершил работу или порт **5465** остался занят, можно освободить его, убив процесс, который его использует.

### Ubuntu

1. Найдите процесс, занимающий порт 5465:
   ```bash
   sudo lsof -i :5465
   ```
2. Определите идентификатор процесса (PID) из выведенного списка.
3. Завершите процесс:
   ```bash
   sudo kill -9 <PID>
   ```

### macOS

1. Найдите процесс, занимающий порт 5465:
   ```bash
   lsof -i :5465
   ```
2. Определите идентификатор процесса (PID).
3. Завершите процесс:
   ```bash
   kill -9 <PID>
   ```
