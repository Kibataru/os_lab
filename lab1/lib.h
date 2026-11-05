#ifndef LIB_H //предохранитель, чтобы файл не читался дважды
#define LIB_H

#if defined(_WIN32)
    #include <windows.h>
    typedef HANDLE proc_handle_t;
    #define INVALID_PROC_HANDLE NULL
#else
    #include <sys/types.h>
    typedef pid_t proc_handle_t;
    #define INVALID_PROC_HANDLE ((pid_t)-1)
#endif

proc_handle_t proc_spawn(const char *command); //передача ос команды создание процесса

int proc_wait(proc_handle_t handle, int *exit_code); // отслеживаем завершения + освобождения

#endif