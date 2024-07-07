#include "myheader.h"
void copy(char *, char *, char *);
void my_cp(char *command)
{
    int i = 1;
    int t;
    int j;
    const char s[] = " \n";
    char old_path[256];
    char new_path[256];
    char option[256];
    char *token[256];

    token[0] = strtok(command, s);
    while (token[i - 1] != NULL)
    {
        token[i] = strtok(NULL, s);
        i++;
    }
    struct stat statbuf;
    if (i < 3)
    {
        printf("command '%s' not found\n", command);
    }
    else
    {
        if (token[1][0] == '-')
        {
            strcpy(option, token[1]);
            j = 2;
            stat(token[i - 2], &statbuf);
            t = i - 3;
        }
        else
        {
            j = 1;
            strcpy(option, "\0");
            stat(token[i - 2], &statbuf);
            t = i - 2;
        }

        if (S_ISDIR(statbuf.st_mode))
        {
            for (int i = j; i < t; i++)
            {
                int k = 0;
                for (int i = strlen(token[j]) - 1; i >= 0; i--)
                {
                    if (token[j][i] == '/')
                    {
                        k = j;
                        break;
                    }
                }
                strcpy(old_path, token[i] + k);
                strcpy(new_path, token[t + j - 1]);
                strcat(new_path, old_path);
                copy(option, token[i], new_path);
            }
        }
        else if (strcmp(token[1], "--help") == 0)
        {
            FILE *fp;
            char buffer[1000];

            fp = fopen("./help/cp.txt", "r");

            while (fgets(buffer, 1000, fp) != NULL)
            {
                printf("%s", buffer);
            }

            fclose(fp);
        }
        else
        {
            if (t == 2)
            {
                copy(option, token[i - 3], token[i - 2]);
            }
            else
            {
                printf("cp: target '%s' is not a directory\n", token[i - 2]);
            }
        }
    }
}
void copy(char option[], char old_path[], char new_path[])
{
    if (access(old_path, F_OK) != 0)
    {
        printf("mv: cannot stat '%s': No such file or directory\n", old_path);
    }
    else if (strcmp(option, "\0") == 0)
    {
        FILE *old_file, *new_file;
        char temp[512];
        size_t num_bytes_read;

        old_file = fopen(old_path, "rb");

        new_file = fopen(new_path, "wb");

        while ((num_bytes_read = fread(temp, 1, 512, old_file)) > 0)
        {
            fwrite(temp, 1, num_bytes_read, new_file);
        }
        fclose(old_file);
        fclose(new_file);
    }
    else if (strcmp(option, "-b") == 0)
    {
        char temp[512];
        if (access(new_path, R_OK) == 0)
        {
            int result;
            strcpy(temp, new_path);
            strcat(temp, "~");
            result = rename(new_path, temp);
        }
        FILE *old_file, *new_file;
        size_t num_bytes_read;

        old_file = fopen(old_path, "rb");

        new_file = fopen(new_path, "wb");

        while ((num_bytes_read = fread(temp, 1, 512, old_file)) > 0)
        {
            fwrite(temp, 1, num_bytes_read, new_file);
        }
        fclose(old_file);
        fclose(new_file);
    }
    else if (strcmp(option, "-i") == 0)
    {
        bool prmt = true;
        char temp[512];
        if (access(new_path, R_OK) == 0)
        {
            char prompt[128];
            printf("cp: overwrite '%s'? ", new_path);
            scanf("%s", prompt);
            if (prompt[0] != 'y' && prompt[0] != 'Y')
            {
                prmt = false;
            }
        }
        if (prmt)
        {
            FILE *old_file, *new_file;
            size_t num_bytes_read;

            old_file = fopen(old_path, "rb");

            new_file = fopen(new_path, "wb");

            while ((num_bytes_read = fread(temp, 1, 512, old_file)) > 0)
            {
                fwrite(temp, 1, num_bytes_read, new_file);
            }
            fclose(old_file);
            fclose(new_file);
        }
    }
    else if (strcmp(option, "-n") == 0)
    {
        bool prmt = true;
        char temp[512];
        if (access(new_path, R_OK) == 0)
        {
            prmt = false;
        }
        if (prmt)
        {
            FILE *old_file, *new_file;
            size_t num_bytes_read;

            old_file = fopen(old_path, "rb");

            new_file = fopen(new_path, "wb");

            while ((num_bytes_read = fread(temp, 1, 512, old_file)) > 0)
            {
                fwrite(temp, 1, num_bytes_read, new_file);
            }
            fclose(old_file);
            fclose(new_file);
        }
    }
    else if (strcmp(option, "-v") == 0)
    {
        FILE *old_file, *new_file;
        size_t num_bytes_read;
        char temp[512];
        old_file = fopen(old_path, "rb");

        new_file = fopen(new_path, "wb");

        while ((num_bytes_read = fread(temp, 1, 512, old_file)) > 0)
        {
            fwrite(temp, 1, num_bytes_read, new_file);
        }
        fclose(old_file);
        fclose(new_file);
        printf("'%s' -> '%s'\n", old_path, new_path);
    }
}
