#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32)
proc_handle_t proc_spawn(const char *command) {
    if (!command) return INVALID_PROC_HANDLE;

    STARTUPINFOA si; //статус окна
    PROCESS_INFORMATION pi; //хранилище ключей
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si); //размер структуры
    ZeroMemory(&pi, sizeof(pi));

    char cmd_buffer[1024];
    snprintf(cmd_buffer, sizeof(cmd_buffer), "cmd.exe /c %s", command); //вместо пинга, гарантия выполнения как в кс

    BOOL success = CreateProcessA(
        NULL,           // Имя исполняемого модуля (передаем через командную строку)
        cmd_buffer,     // Сама командная строка
        NULL,           // Атрибуты безопасности процесса по умолчанию
        NULL,           // Атрибуты безопасности потока по умолчанию
        FALSE,          // Дескрипторы не наследуются
        0,              // Флаги создания
        NULL,           // Окружение родителя
        NULL,           // Текущий рабочий каталог
        &si,
        &pi
    );

    if (!success) {
        return INVALID_PROC_HANDLE;
    }

    CloseHandle(pi.hThread);// вместо 2 ключей(потока и процесса), оставляем ключ потока
    return pi.hProcess;
}

int proc_wait(proc_handle_t handle, int *exit_code) {
    if (handle == INVALID_PROC_HANDLE) return -1;

    WaitForSingleObject(handle, INFINITE); //ожидание завершения

    DWORD win_exit_code = 0; //код завершения
    if (GetExitCodeProcess(handle, &win_exit_code)) {
        if (exit_code) {
            *exit_code = (int)win_exit_code;
        }
    }

    CloseHandle(handle); //очистка ключа
    return 0;
}

#else

#include <unistd.h>
#include <sys/wait.h>

proc_handle_t proc_spawn(const char *command) {
    if (!command) return INVALID_PROC_HANDLE;

    pid_t pid = fork(); //клон

    if (pid < 0) {
        return INVALID_PROC_HANDLE;
    }

    if (pid == 0) { //код для ребенка
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        _exit(127);
    }

    return pid;
}

int proc_wait(proc_handle_t handle, int *exit_code) {
    if (handle == INVALID_PROC_HANDLE) return -1;

    int status = 0;
    if (waitpid(handle, &status, 0) == -1) { //завершение ребенка
        return -1;
    }

    if (exit_code) {
        if (WIFEXITED(status)) { //штатно - завершаем
            *exit_code = WEXITSTATUS(status);
        } else {
            *exit_code = -1;
        }
    }

    return 0;
}

#endif