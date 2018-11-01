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

  // free(s);

  DIR * d = opendir("test");
  struct dirent *entry;
  entry = readdir(d);
  printf("%s\n", entry->d_name);
  closedir(d);
  return 0;
}
