#include "myheader.h"
struct process_data
{
    int pid;
    int ppid;
    int sid;
    char cmd[1024];
    char status;
    unsigned long long int rss;
    long int sz;
    int uid;
    char username[512];
    int pgid;
    int psr;
    int c;
    long long int utime;
    long long int stime;
    long long int cuttime;
    long long int cstime;
    time_t STIME;
} file_data;
void my_ps(char *command)
{
    char option[16];
    char *token[8];
    int i = 1;
    const char s[] = " \n";
    token[0] = strtok(command, s);
    while (token[i - 1] != NULL)
    {
        token[i] = strtok(NULL, s);
        i++;
    }

    if (token[1] != NULL)
    {
        strcpy(option, token[1]);
    }
    else
    {
        strcpy(option, "\0");
    }

    if (strcmp(option, "\0") == 0)
    {
        char *my_tty = ttyname(STDIN_FILENO);
        char my_tty_copy[256];
        strcpy(my_tty_copy, my_tty);

        DIR *dir;
        struct dirent *ent;
        dir = opendir("/proc");
        FILE *file;
        printf("%8s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type != DT_DIR || !isdigit(*ent->d_name))
                continue;
            char path[1024];
            sprintf(path, "/proc/%s/fd/0", ent->d_name);

            char *tty = ttyname(open(path, O_RDONLY));
            if (tty == NULL)
            {
                tty = "??????";
            }
            else if (strcmp(my_tty_copy, tty) == 0)
            {

                char destination[1024];
                sprintf(destination, "/proc/%s/stat", ent->d_name);
                file = fopen(destination, "r");
                fscanf(file, "%d %s %c %d %*d %d %d %*d %*d %*u %*d %*d %*d %*d %lld %lld %lld %lld %*d %*d %*d %*d %ld %*d %llu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %d",
                       &file_data.pid, file_data.cmd, &file_data.status, &file_data.ppid, &file_data.pgid, &file_data.sid, &file_data.utime, &file_data.stime, &file_data.cuttime, &file_data.cstime, &file_data.STIME, &file_data.rss, &file_data.psr, &file_data.c);
                time_t time = (file_data.stime + file_data.utime) / sysconf(_SC_CLK_TCK);

                printf("%8d %s\t", file_data.pid, tty + 5);

                __time_t hour, minute, second;
                second = time % 60;
                minute = (time / 60) % 60;
                hour = (time / 3600) % 3600;
                int t = strlen(file_data.cmd);
                file_data.cmd[t - 1] = '\0';
                printf("%02ld:%02ld:%02ld %s\n", hour, minute, hour, file_data.cmd + 1);
            }
        }

        closedir(dir);
    }

    else if (strcmp(option, "-A") == 0)
    {

        DIR *dir;
        struct dirent *ent;
        dir = opendir("/proc");
        FILE *file;
        printf("%8s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type != DT_DIR || !isdigit(*ent->d_name))
                continue;
            char path[1024];
            sprintf(path, "/proc/%s/fd/0", ent->d_name);

            char *tty = ttyname(open(path, O_RDONLY));
            if (tty == NULL)
            {
                tty = "??????";
            }

            char destination[1024];
            sprintf(destination, "/proc/%s/stat", ent->d_name);
            file = fopen(destination, "r");
            fscanf(file, "%d %s %c %d %*d %d %*d %*d %*u %*d %*d %*d %*d %lld %lld %lld %lld %*d %*d %*d %*d %ld %*d %llu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %d",
                   &file_data.pid, file_data.cmd, &file_data.status, &file_data.ppid, &file_data.sid, &file_data.utime, &file_data.stime, &file_data.cuttime, &file_data.cstime, &file_data.STIME, &file_data.rss, &file_data.psr, &file_data.c);
            time_t time = (file_data.stime + file_data.utime) / sysconf(_SC_CLK_TCK);

            printf("%8d %s\t", file_data.pid, tty + 5);

            __time_t hour, minute, second;
            second = time % 60;
            minute = (time / 60) % 60;
            hour = (time / 3600) % 3600;
            int t = strlen(file_data.cmd);
            file_data.cmd[t - 1] = '\0';
            printf("%02ld:%02ld:%02ld %s\n", hour, minute, hour, file_data.cmd + 1);
        }

        closedir(dir);
    }
    else if (strcmp(option, "-d") == 0)
    {
        DIR *dir;
        struct dirent *ent;
        dir = opendir("/proc");
        FILE *file;
        printf("%8s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");
        while ((ent = readdir(dir)) != NULL)
        {

            if (ent->d_type != DT_DIR || !isdigit(*ent->d_name))
                continue;
            char path[1024];
            sprintf(path, "/proc/%s/fd/0", ent->d_name);

            char *tty = ttyname(open(path, O_RDONLY));
            if (tty == NULL)
            {
                tty = "??????";
            }

            char destination[1024];
            sprintf(destination, "/proc/%s/stat", ent->d_name);
            file = fopen(destination, "r");
            fscanf(file, "%d %s %c %d %*d %d %*d %*d %*u %*d %*d %*d %*d %lld %lld %lld %lld %*d %*d %*d %*d %ld %*d %llu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %d",
                   &file_data.pid, file_data.cmd, &file_data.status, &file_data.ppid, &file_data.sid, &file_data.utime, &file_data.stime, &file_data.cuttime, &file_data.cstime, &file_data.STIME, &file_data.rss, &file_data.psr, &file_data.c);
            time_t time = (file_data.stime + file_data.utime) / sysconf(_SC_CLK_TCK);

            if (file_data.pid != file_data.sid)
            {
                printf("%8d %s\t", file_data.pid, tty + 5);

                __time_t hour, minute, second;
                second = time % 60;
                minute = (time / 60) % 60;
                hour = (time / 3600) % 3600;
                int t = strlen(file_data.cmd);
                file_data.cmd[t - 1] = '\0';
                printf("%02ld:%02ld:%02ld %s\n", hour, minute, hour, file_data.cmd + 1);
            }
        }

        closedir(dir);
    }
    else if (strcmp(option, "-a") == 0)
    {
        pid_t my_pid = getpid();
        // pid_t my_sid = getsid(pid);
        DIR *dir;
        struct dirent *ent;
        dir = opendir("/proc");
        FILE *file;
        printf("%8s %s\t%8s %s\n", "PID", "TTY", "TIME", "CMD");
        while ((ent = readdir(dir)) != NULL)
        {

            if (ent->d_type != DT_DIR || !isdigit(*ent->d_name))
                continue;
            char path[1024];
            sprintf(path, "/proc/%s/fd/0", ent->d_name);

            char *tty = ttyname(open(path, O_RDONLY));
            if (tty == NULL)
            {
                tty = "??????";
                continue;
            }

            char destination[1024];
            sprintf(destination, "/proc/%s/stat", ent->d_name);
            file = fopen(destination, "r");
            fscanf(file, "%d %s %c %d %*d %d %*d %*d %*u %*d %*d %*d %*d %lld %lld %lld %lld %*d %*d %*d %*d %ld %*d %llu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %d",
                   &file_data.pid, file_data.cmd, &file_data.status, &file_data.ppid, &file_data.sid, &file_data.utime, &file_data.stime, &file_data.cuttime, &file_data.cstime, &file_data.STIME, &file_data.rss, &file_data.psr, &file_data.c);
            time_t time = (file_data.stime + file_data.utime) / sysconf(_SC_CLK_TCK);

            if (file_data.sid != file_data.pid)
            {
                printf("%8d %s\t", file_data.pid, tty + 5);

                time_t hour, minute, second;
                second = time % 60;
                minute = (time / 60) % 60;
                hour = (time / 3600) % 3600;
                int t = strlen(file_data.cmd);
                file_data.cmd[t - 1] = '\0';
                printf("%02ld:%02ld:%02ld %s\n", hour, minute, hour, file_data.cmd + 1);
            }
        }

        closedir(dir);
    }
    else if (strcmp(option, "-j") == 0)
    {
        pid_t pid = getpid();
        char *my_tty = ttyname(STDIN_FILENO);
        char my_tty_copy[256];
        strcpy(my_tty_copy, my_tty);

        DIR *dir;
        struct dirent *ent;
        dir = opendir("/proc");
        FILE *file;
        printf("%8s %6s %7s %s\t%8s %s\n", "PID", "PGID", "SID", "TTY", "TIME", "CMD");
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type != DT_DIR || !isdigit(*ent->d_name))
                continue;
            char path[1024];
            sprintf(path, "/proc/%s/fd/0", ent->d_name);

            char *tty = ttyname(open(path, O_RDONLY));
            if (tty == NULL)
            {
                tty = "??????";
            }
            else if (strcmp(my_tty_copy, tty) == 0)
            {

                char destination[1024];
                sprintf(destination, "/proc/%s/stat", ent->d_name);
                file = fopen(destination, "r");
                fscanf(file, "%d %s %c %d %d %d %*d %*d %*d %*u %*d %*d %*d %*d %lld %lld %lld %lld %*d %*d %*d %*d %ld %*d %llu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %d",
                       &file_data.pid, file_data.cmd, &file_data.status, &file_data.ppid, &file_data.pgid, &file_data.sid, &file_data.utime, &file_data.stime, &file_data.cuttime, &file_data.cstime, &file_data.STIME, &file_data.rss, &file_data.psr, &file_data.c);
                time_t time = (file_data.stime + file_data.utime) / sysconf(_SC_CLK_TCK);

                printf("%8d %6d", file_data.pid, file_data.pgid);

                time_t hour, minute, second;
                second = time % 60;
                minute = (time / 60) % 60;
                hour = (time / 3600) % 3600;
                int t = strlen(file_data.cmd);
                file_data.cmd[t - 1] = '\0';
                printf("%8d %4s   %02ld:%02ld:%02ld %s\n", file_data.sid, tty + 5, hour, minute, hour, file_data.cmd + 1);
            }
        }

        closedir(dir);
    }
    else if (strcmp(option, "--help") == 0)
    {
        FILE *fp;
        char buffer[1000];

        fp = fopen("./help/ps.txt", "r");

        while (fgets(buffer, 1000, fp) != NULL)
        {
            printf("%s", buffer);
        }
    }
    else{
         printf("Command 'ls %s' not found\n",option);
    }
}