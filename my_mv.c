#include "myheader.h"
void move(char option[], char old_path[], char new_path[]);

void my_mv(char *command)
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
    if(i<3){
        printf("command not found\n");
    }
    else{
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
            move(option, token[i], new_path);
        }
    }
    else if(strcmp(token[1],"--help")==0)
    {
       FILE *fp;
    char buffer[1000];

    fp = fopen("./help/mv.txt", "r");

    while (fgets(buffer, 1000, fp) != NULL) {
        printf("%s", buffer);
    }
    puts("");
    fclose(fp);
    }
    else
    {
        if (t == 2)
        {
            move(option, token[i - 3], token[i - 2]);
        }
        else
        {
            printf("mv: target '%s' is not a directory\n", token[i - 2]);
        }
    }
    }
}
void move(char option[], char old_path[], char new_path[])
{
    if (access(old_path, F_OK) != 0)
    {
        printf("mv: cannot stat '%s': No such file or directory\n", old_path);
    }
    else if (strcmp(option, "\0") == 0)
    {
        rename(old_path, new_path);
    }
    else if (strcmp(option, "-n") == 0)
    {
        if (access(new_path, F_OK) != 0)
        {
            rename(old_path, new_path);
        }
    }
    else if (strcmp(option, "-i") == 0)
    {
        if (access(new_path, R_OK) == 0)
        {
            char prompt[128];
            printf("mv: overwrite '%s'? ", new_path);
            scanf("%s", prompt);
            if (prompt[0] == 'y' || prompt[0] == 'Y')
            {
                rename(old_path, new_path);
            }
        }
        else
        {
            rename(old_path, new_path);
        }
    }
    else if (strcmp(option, "-b") == 0)
    {
        if (access(new_path, R_OK) == 0)
        {
            char temp[256];
            strcpy(temp, new_path);
            strcat(temp, "~");
            rename(new_path, temp);
            rename(old_path, new_path);
        }
        else
        {
            rename(old_path, new_path);
        }
    }
    else if (strcmp(option, "-v") == 0)
    {
        rename(old_path, new_path);

        printf("renamed '%s' -> '%s'\n", old_path, new_path);
    }
}