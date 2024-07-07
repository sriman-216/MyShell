#include "myheader.h"
struct file_data
{
  char name[256];
} myfile[256], dot_files[256];

void my_ls(char *command)
{
  bool error = true;
  char option[256];
  char *token[4];
  int i = 1;
  const char s[] = " \n";
  token[0] = strtok(command, s);
  while (token[i - 1] != NULL)
  {
    token[i] = strtok(NULL, s);
    i++;
  }
  if (i == 3 && token[1][0] == '-')
  {
    strcpy(option, token[1]);
  }
  else if (i == 2)
  {
    strcpy(option, "-");
  }
  else
  {
    printf("Command 'ls %s' not found\n", token[1]);
    error = false;
  }
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  i = 0;
  int p = 0;
  struct stat fileStat;
  struct group *grp;
  struct passwd *pwd;
  if (d != NULL)
  {
    while ((dir = readdir(d)) != 0)
    {

      if (dir->d_name[0] != '.')
      {
        strcpy(myfile[i].name, dir->d_name);
        i++;
      }
      else
      {
        strcpy(dot_files[p].name, dir->d_name);
        p++;
      }
    }
    closedir(d);
  }
  int n = i;
  if (strcmp(option, "-U") == 0)
  {
    for (int i = 0; i < n; i++)
    {
      printf("%s ", myfile[i].name);
    }
    puts("");
    error = false;
  }

  bool ls_g = false;
  if (strcmp(option, "-g") == 0)
  {
    ls_g = true;
  }
  while (i)
  {
    for (int j = 0; j < i - 1; j++)
    {

      if (strcmp(myfile[j].name, myfile[j + 1].name) > 0)
      {

        struct file_data temp = myfile[j];
        myfile[j] = myfile[j + 1];
        myfile[j + 1] = temp;
      }
    }
    i--;
  }
  long int t = 0;
  struct stat my_stat;
  for (int i = 0; i < n; i++)
  {
    stat(myfile[i].name, &my_stat);
    t += my_stat.st_blocks;
  }

  if (strcmp(option, "-") == 0)
  {
    for (int i = 0; i < n; i++)
    {
      printf("%s ", myfile[i].name);
    }
    error = false;
    puts("");
  }
  else if (strcmp(option, "-s") == 0)
  {
    printf("total %ld\n", t / 2);
    for (int i = 0; i < n; i++)
    {
      stat(myfile[i].name, &my_stat);
      printf("%ld %s ", my_stat.st_blocks / 2, myfile[i].name);
    }
    error = false;
  }

  else if (strcmp(option, "-a") == 0)
  {
    int i = p;
    while (i)
    {
      for (int j = 0; j < i - 1; j++)
      {

        if (strcmp(dot_files[j].name, dot_files[j + 1].name) > 0)
        {

          struct file_data temp = dot_files[j];
          dot_files[j] = dot_files[j + 1];
          dot_files[j + 1] = temp;
        }
      }
      i--;
    }
    for (int i = 0; i < p; i++)
    {
      printf("%s ", dot_files[i].name);
    }
    for (int i = 0; i < n; i++)
    {
      printf("%s ", myfile[i].name);
    }
    error = false;
    puts("");
  }

  else if (strcmp(option, "-l") == 0 || strcmp(option, "-g") == 0)
  {
    int i = 0;
    printf("total %ld\n", t / 2);
    while (i < n)
    {

      // stat(a[i]->d_name, &fileStat);
      stat(myfile[i].name, &fileStat);

      printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
      printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
      printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
      printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
      printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
      printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
      printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
      printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
      printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
      printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");

      printf(" %ld ", fileStat.st_nlink);

      struct passwd *pwd;
      pwd = getpwuid(fileStat.st_uid);
      printf("%s ", pwd->pw_name);
      if (ls_g == false)
      {
        struct group *grp;
        grp = getgrgid(fileStat.st_gid);
        printf("%s ", grp->gr_name);
      }

      printf("%8ld ", fileStat.st_size);
      char *c = malloc(sizeof(char) * 25);
      c = ctime(&fileStat.st_mtime);
      for (int i = 4; i < 16; i++)
      {
        printf("%c", c[i]);
      }
      printf(" %s", myfile[i].name);
      puts("");

      i++;
    }
    error = false;
    puts("");
  }
  else if (strcmp(option, "-S") == 0)
  {
    struct stat f_i, f_j;
    int i = n;
    while (i)
    {

      for (int j = 0; j < i - 1; j++)
      {
        stat(myfile[j].name, &f_i);
        stat(myfile[j + 1].name, &f_j);
        if (f_i.st_size < f_j.st_size)
        {

          struct file_data temp = myfile[j];
          myfile[j] = myfile[j + 1];
          myfile[j + 1] = temp;
        }
      }
      i--;
    }
    for (int i = 0; i < n; i++)
    {
      printf("%s ", myfile[i].name);
    }
    error = false;
    puts("");
  }
  else if (strcmp(option, "--help") == 0)
  {
    FILE *fp;
    char buffer[1000];

    fp = fopen("./help/ls.txt", "r");

    while (fgets(buffer, 1000, fp) != NULL)
    {
      printf("%s", buffer);
    }
    fclose(fp);
    error = false;
  }
  if (error)
  {
    printf("command not found\n");
  }
}
