#include "dir.h"

// helper for returning the permission created by the octal
char * perm_octal(int octal){
  char* string;
  if (octal == 0){
    string = "---";
  }
  else if (octal == 1){
    string = "--x";
  }
  else if (octal == 2){
    string = "-w-";
  }
  else if (octal == 3){
    string = "-wx";
  }
  else if (octal == 4){
    string = "r--";
  }
  else if (octal == 5){
    string = "r-x";
  }
  else if (octal == 6){
    string = "rw-";
  }
  else{
    string = "rwx";
  }
  return string;
}

char * string_perms(struct stat *s) {
  int perms = s->st_mode % 01000;
  //printf("Permissions: %o\n", perms);
  int digit; //store each octal digit
  int times;
  char * permissions = calloc(10, sizeof(char));
  permissions[0] = '-'; //out of specs of assignment

  //create a set of arrays that will be catted to permissions
  char * perms0 = calloc(3, sizeof(char));
  char * perms1 = calloc(3, sizeof(char));

  for(times = 0; times < 3; times++){
    digit = perms % 010;
    // printf("digit: %o\n", digit);
    if (times == 0){
      strcat(perms0, perm_octal(digit));
    }
    else if(times == 1){
      strcat(perms1, perm_octal(digit));
    }
    else{
    strcat(permissions, perm_octal(digit));
    }
    perms = (perms - (perms % 010)) / 010; //cut off last digit cuz it's whack
    //cat the two arrays into permissions
    strcat(permissions, perms1);
    strcat(permissions, perms0);
    free(perms0);
    free(perms1);
    return permissions;
  }
}
