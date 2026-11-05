#include <stdio.h>
#include "lib.h"

#if defined(_WIN32)
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms) * 1000)
#endif

int main(void) {
    printf("Тест\n");
#if defined(_WIN32)
    const char *cmd = "ping 127.0.0.1 -n 3 > nul";
#else
    const char *cmd = "sleep 2";
#endif

    printf("Запуск процесса в фоне: '%s'\n", cmd);
    proc_handle_t child = proc_spawn(cmd);

    if (child == INVALID_PROC_HANDLE) {
        fprintf(stderr, "Не удалось запустить процесс\n");
        return 1;
    }

    printf("Процесс создан и работает.\n");

    for (int i = 1; i <= 3; i++) {
        printf("Родитель выполняет свою задачу (шаг %d/3)\n", i);
        sleep_ms(400);
    }

    printf("Ожидание завершения работы ребенка.\n");

    int exit_code = -1;
    if (proc_wait(child, &exit_code) == 0) {
        printf("Ребенок завершил работу, код завершения: %d\n", exit_code);
    } else {
        fprintf(stderr, "Ошибка ожидания .\n");
    }

    printf("Тест завершен.\n");
    return 0;
}