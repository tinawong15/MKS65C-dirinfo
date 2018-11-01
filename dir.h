#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include<sys/types.h>

char * perm_octal(int octal);

char * string_perms(struct stat *s);
