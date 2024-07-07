#include "myheader.h"

void grep(char *, char *, char *, bool);
void my_grep(char *command)
{
    char pattern[512];
    char file_path[512];
    char option[256];
    char *token[256];
    int i = 1;
    const char s[] = " \n";
    token[0] = strtok(command, s);
    while (token[i - 1] != NULL)
    {
        token[i] = strtok(NULL, s);
        i++;
    }
    if (i == 2)
    {
        printf("Command '%s' not found\n", token[0]);
    }
    else if (token[1][0] == '-' && i > 4)
    {
        bool multiple_file = false;
        strcpy(option, token[1]);
        strcpy(pattern, token[2]);
        if (i - 2 > 3)
        {
            for (int j = 3; j < i - 1; j++)
            {
                multiple_file = true;
                strcpy(file_path, token[j]);
                grep(option, pattern, file_path, multiple_file);
            }
        }
        else
        {
            strcpy(file_path, token[3]);
            grep(option, pattern, file_path, multiple_file);
        }
    }
    else if (i >= 4)
    {
        bool multiple_file = false;
        strcpy(option, "\0");
        strcpy(pattern, token[1]);

        if (i - 2 > 2)
        {
            for (int j = 2; j < i - 1; j++)
            {
                multiple_file = true;
                strcpy(file_path, token[j]);
                grep(option, pattern, file_path, multiple_file);
            }
        }
        else
        {
            strcpy(file_path, token[2]);
            grep(option, pattern, file_path, multiple_file);
        }
    }
    else
    {

        if (strcmp(token[1], "--help") == 0)
        {
            FILE *fp;
            char buffer[1000];

            fp = fopen("./help/grep.txt", "r");

            while (fgets(buffer, 1000, fp) != NULL)
            {
                printf("%s", buffer);
            }
            fclose(fp);
        }
        else
        {
            printf("Command 'grep %s' not found \n", token[1]);
            
        }
    }
}
void grep(char option[], char pattern[], char file_path[], bool multple_file)
{
    if (strcmp(option, "\0") == 0)
    {
        char line[1024];

        FILE *file = fopen(file_path, "r");

        if (!file)
        {
            printf("grep: %s: No such file or directory\n", file_path);
        }

        while (fgets(line, 1024, file))
        {
            if (strstr(line, pattern))
            {
                if (multple_file)
                {
                    printf("%s:", file_path);
                }
                printf("%s", line);
            }
        }

        fclose(file);
    }
    else if (strcmp(option, "-n") == 0)
    {
        char line[1024];

        FILE *file = fopen(file_path, "r");

        if (!file)
        {
            printf("grep: %s: No such file or directory\n", file_path);
        }
        int i = 1;
        while (fgets(line, 1024, file))
        {
            if (strstr(line, pattern))
            {
                if (multple_file)
                {
                    printf("%s:", file_path);
                }
                printf("%d:%s", i, line);
            }
            i++;
        }

        fclose(file);
    }
    else if (strcmp(option, "-v") == 0)
    {
        char line[1024];

        FILE *file = fopen(file_path, "r");

        if (!file)
        {
            printf("grep: %s: No such file or directory\n", file_path);
        }

        while (fgets(line, 1024, file))
        {
            if (strstr(line, pattern) == NULL)
            {
                if (multple_file)
                {
                    printf("%s:", file_path);
                }
                printf("%s", line);
            }
        }

        fclose(file);
    }
    else if (strcmp(option, "-c") == 0)
    {
        char line[1024];

        FILE *file = fopen(file_path, "r");

        if (!file)
        {
            printf("grep: %s: No such file or directory\n", file_path);
        }
        int i = 0;
        while (fgets(line, 1024, file))
        {
            if (strstr(line, pattern))
            {
                i++;
            }
        }
        if (multple_file)
        {
            printf("%s:", file_path);
        }
        printf("%d\n", i);

        fclose(file);
    }

    else if (strcmp(option, "-o") == 0)
    {
        char line[1024];

        FILE *file = fopen(file_path, "r");

        if (!file)
        {
            printf("grep: %s: No such file or directory\n", file_path);
        }

        while (fgets(line, 1024, file))
        {
            if (strstr(line, pattern))
            {
                if (multple_file)
                {
                    printf("%s:", file_path);
                }
                printf("%s\n", pattern);
            }
        }

        fclose(file);
    }
    else if (strcmp(option, "--help") == 0)
    {
        FILE *fp;
        char buffer[1000];

        fp = fopen("./help/grep.txt", "r");

        while (fgets(buffer, 1000, fp) != NULL)
        {
            printf("%s", buffer);
        }
        fclose(fp);
    }
    else{
        printf("command not found");
    }
    puts("");
}