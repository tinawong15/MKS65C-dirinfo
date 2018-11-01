#include "dir.h"

int main() {
  // struct stat *s = malloc(sizeof(struct stat));
  // stat("text.txt", s);
  // printf("File Size: %lld\n", s->st_size);
  // char size[256];
  // int byte = s->st_size;
  // int kb = byte / 1000;
  // int mb = kb / 1000;
  // int gb = mb / 1000;
  // sprintf(size, "%d B\n%d KB\n%d MB\n%d GB", byte, kb, mb, gb);
  // printf("%s\n", size);
  // printf("Time of last access: %s", ctime(&(s->st_atime)));

  DIR *d = opendir(".");
  printf("Statistics for directory: . \n");
  int size;
  struct dirent *entry;
  struct stat *s = malloc(sizeof(struct stat));
  while( (entry = readdir(d)) != NULL ) {
    stat(entry->d_name, s);
    size += s->st_size;
  }
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
  while( (entry = readdir(d)) != NULL ) {
      if(entry->d_type == 8) {
        printf("%s\n", entry->d_name);
      }
  }
  return 0;
}
