#include "dir.h"

int main() {
  DIR *d = opendir(".");
  if (errno == -1){
    printf("Unable to access directory!\n");
  }
  else{
    printf("Statistics for directory: \n");
    int size, second_size;
    struct dirent *entry;
    struct stat *s = malloc(sizeof(struct stat));

    // get_size(DIR *ptr, recursion depth)
    size = get_size(d, 1);

    closedir(d);
    int i = 0;
    while(size > 1000) {
      size = size / 1000;
      i++;
    }
    if(i == 0) {
      printf("Total Directory Size: %d B\n", size);
    }
    else if(i == 1) {
      printf("Total Directory Size: %d KB\n", size);
    }
    else if(i == 2) {
      printf("Total Directory Size: %d MB\n", size);
    }
    else{
      printf("Total Directory Size: %d GB\n", size);
    }
    free(s);
    d = opendir(".");
    printf("Directories:\n");
    while( (entry = readdir(d)) != NULL ) {
      if(entry->d_type == 4) {
        printf("%s\n", entry->d_name);
      }
    }
    closedir(d);
    d = opendir(".");
    printf("Regular files:\n");
    s = malloc(sizeof(struct stat));
    char entry_time [256];
    int len = 0;
    while( (entry = readdir(d)) != NULL ) {
      if(entry->d_type == 8) {
        stat(entry->d_name, s);
        strcpy(entry_time, ctime(&(s->st_atime)));
        len = strlen(entry_time);
        entry_time[len-1] = 0; // strip newline
        printf("%s %s %s\n", string_perms(s), entry_time, entry->d_name);
      }
    }
    free(s);
    closedir(d);
    //printf("\n%d\n", strcmp("f","e"));
    d = opendir(".");
    // ls(d);
    closedir(d);
  }
  return 0;
}
