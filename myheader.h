#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <dirent.h>
#include<sys/stat.h>
#include <time.h>
#include<fcntl.h>
#include<sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <ctype.h>

#define CYNB "\001\e[01;36m\002"
#define RED "\001\e[00;31m\002"
#define REDB "\001\e[01;31m\002"
#define GRN "\001\e[0;32m\002"
#define YLW "\001\e[00;33m\002"
#define YLWB "\001\e[01;33m\002"
#define reset "\001\e[0m\002"