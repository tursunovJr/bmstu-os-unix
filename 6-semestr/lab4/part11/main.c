#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#define BUF_SIZE 0x200

char *outputNames[] = {
    "pid",          // ID процесса
    "filename",     // Имя файла
    "state",        // Состояние процесса
    "ppid",         // ID родительского процесса
    "gid",          // ID группы процесса
    "session",      // ID сессии процесса
    "tty_nr",       // Контролирующий терминал процесса
    "tp_gid",       // ID внешней группы процессов контролирующего терминала
    "flags",        // Флаги ядра процесса
    "minflt",       // Количество минорных ошибок процесса (Минорные ошибки не включают ошибки загрузки страниц памяти с диска)
    "cminflt",      // Количество минорных ошибок дочерних процессов (Минорные ошибки не включают ошибки загрузки страниц памяти с диска)
    "majflt",       // Количество Мажоных ошибок процесса
    "cmajflt",      // Количество Мажоных ошибок дочерних процессов процесса
    "utime",        // Количество времени, в течение которого этот процесс был запланирован в пользовательском режиме
    "stime",        // Количество времени, в течение которого этот процесс был запланирован в режиме ядра
    "cutime",       // Количество времени, в течение которого ожидаемые дети этого процесса были запланированы в пользовательском режиме
    "cstime",       // Количество времени, в течение которого ожидаемые дети этого процесса были запланированы в режиме ядра
    "priority",     // Приоритет процесса
    "nice",         // nice
    "num_threads",  // Количество потоков
    "itrealvalue",  // Время в тиках до следующего SIGALRM отправленного в процесс из-за интервального таймера.
    "start_tiime",  // Время запуска процесса 
    "vsize",        // Объем виртуальной памяти в байтах
    "rss",          // Resident Set Size: Количество страниц процесса в физической памяти.
    "rsslim",       // Текущий лимит в байтах на RSS процесса
    "startcode",    // Адрес, над которым может работать текст программы
    "endcode",      // Адрес, над которым может работать текст программы
    "startstack",   // Адрес начала (т. е. дна) стека
    "kstkesp",      // Текущее значение ESP (Stack pointer), найденное на странице стека ядра для данного процесса.
    "kstkeip",      // Текущее значение EIP (instruction pointer)
    "signal",       // Растровое изображение отложенных сигналов, отображаемое в виде десятичного числа
    "blocked",      // Растровое изображение заблокированных сигналов, отображаемое в виде десятичного числа
    "sigignore",    // Растровое изображение игнорированных сигналов, отображаемое в виде десятичного числа
    "sigcatch",     // Растровое изображение пойманных сигналов, отображаемое в виде десятичного числа.
    "wchan",        // Канал, в котором происходит ожидание процесса.
    "nswap",        // Количество страниц, поменявшихся местами
    "cnswap",       // Накопительный своп для дочерних процессов
    "exit_signal",  // Сигнал, который будет послан родителю, когда процесс будет завершен.
    "processor",    // Номер процессора, на котором было последнее выполнение.
    "rt_priority",  // Приоритет планирования в реальном времени- число в диапазоне от 1 до 99 для процессов, запланированных в соответствии с политикой реального времени
    "policy",       // Политика планирования
    "delayacct_blkio_tics", // Общие блочные задержки ввода/вывода
    "quest_time",   // Гостевое время процесса
    "cquest_time",  // Гостевое время  дочерних процессов
    "start_data",   // Адрес, над которым размещаются инициализированные и неинициализированные данные программы (BSS).
    "end_data",     // Адрес, под которым размещаются инициализированные и неинициализированные данные программы (BSS).
    "start_brk",    // Адрес, выше которого куча программ может быть расширена с помощью brk.
    "arg_start",    // Адрес, над которым размещаются аргументы командной строки программы (argv).
    "arg_end",      // Адрес, под которым размещаются аргументы командной строки программы (argv).
    "env_start",    // Адрес, над которым размещена программная среда
    "env_end",      // Адрес, под которым размещена программная среда
    "exit_code"     // Состояние выхода потока в форме, сообщаемой waitpid.

};

static int i = 0;
void statOutput(char *buf)
{
    int len = strlen(buf);
    int currentName = 0;
    char *pch = strtok(buf, " ");

    while (pch != NULL && i < 51)
    {
        printf("\n%15s:\t %s", outputNames[i], pch);
        pch = strtok(NULL, " ");
        i++;
    }
}
void simpleOutput(char *buf)
{
    printf("%s\n", buf);
}
void read_one_file(char* filename, void (*print_func)(char*))
{
    char buf[BUF_SIZE];
    int i, len;
    FILE *f = fopen(filename, "r");
    while ((len = fread(buf, 1, BUF_SIZE, f)) > 0)
    {
        for (i = 0; i < len; i++)
            if( buf[i] == 0)
                buf[i] = 10;
        buf[len - 1] = 0;
        print_func(buf);
    }
    fclose(f);
}
int main(int argc, char *argv[])
{
    printf("\n______________________________\n");
    printf("STAT \n\n");
    read_one_file("/proc/self/stat", statOutput);
    printf("\n______________________________\n");
    printf("ENVIRON\n\n");
    read_one_file("/proc/self/environ",  simpleOutput);
    printf("\n______________________________\n");
    printf("CMDLINE\n\n");
    read_one_file("/proc/self/cmdline",  simpleOutput);
    printf("\n______________________________\n");
    printf("FD\n\n");
    chdir("/proc/self/fd");
    execlp("/bin/ls","ls","-l",0);
    return 0;
}