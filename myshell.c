#include "myheader.h"

#ifndef PATH_MAX
#define PATH_MAX 256
#endif
void getword(char *, char *);
void my_cp(char *);
void my_ls(char *);
void my_mv(char *);
void my_grep(char *);
void my_ps(char *);
int main()
{
    char *command;
    char hostname[512];
    char temp[512];
    char *basic_com;
    gethostname(hostname, 512);
    char *username = getlogin();
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    strcat(username, "@");
    strcat(username, hostname);
    strcat(username,":");
    strcat(username, cwd);
    strcat(username, "$ ");

    while (true)
    {
        command = readline(username);
        strcpy(temp, command);
        if (strtok(temp, " \t\n\0") == NULL)
        {
            continue;
        }
        strcpy(temp, command);
        basic_com = strtok(temp, " \t\n\0");

        if (strlen(command) > 0)
        {
            add_history(command);
        }
        if (strcmp(basic_com, "exit") == 0)
        {
            break;
        }
        else if (strcmp(basic_com, "help") == 0)
        {
            FILE *fp;
            char buffer[1000];

            fp = fopen("./help.txt", "r");

            while (fgets(buffer, 1000, fp) != NULL)
            {
                printf("%s", buffer);
            }

            fclose(fp);
        }
        else if (strcmp(basic_com, "ls") == 0)
        {
            my_ls(command);
        }
        else if (strcmp(basic_com, "cp") == 0)
        {
            my_cp(command);
        }
        else if (strcmp(basic_com, "mv") == 0)
        {
            my_mv(command);
        }
        else if (strcmp(basic_com, "ps") == 0)
        {
            my_ps(command);
        }
        else if (strcmp(basic_com, "grep") == 0)
        {
            my_grep(command);
        }
        else
        {
            printf("command '%s'not found\n", command);
        }
    }
}
