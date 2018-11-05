#include "dir.h"

int main(int argc, char *argv[]) {
  char path[100];
  int i =0;
  if (argc == 1){
    printf("Type in valid path: ");
    //fgets(path, 100, stdin);
    scanf("%s", path);
    printf("Path: %s\n", path);
  }
  else{
    strcpy(path,argv[0]);
  }
  dir(path);
  return 0;
}
