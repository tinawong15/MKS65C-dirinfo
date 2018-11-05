#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

struct info {char *name; char * entry_string;};

char * perm_octal(int octal);

char * string_perms(struct stat *s);

int get_size(DIR *d, int size);

void ls(DIR *d);

void dir(char *path);
