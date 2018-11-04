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
    //printf("digit: %o\n", digit);
    if (times == 0){
      strcat(perms0, perm_octal(digit));
    }
    else if(times == 1){
      strcat(perms1, perm_octal(digit));
    }
    else{
    strcat(permissions, perm_octal(digit));
    }
    perms = perms / 010; //cut off last digit cuz it's whack
  }
  //cat the two arrays into permissions
  strcat(permissions, perms1);
  strcat(permissions, perms0);
  free(perms0);
  free(perms1);
  return permissions;
}

// recursively find size down to a certain depth
// assumes d has been opened, DOES NOT CLOSE d
int get_size(DIR *d, int size){
  struct stat *s = malloc(sizeof(struct stat));
  struct dirent *entry;
  int size_total = 0;

  while( (entry = readdir(d)) != NULL ) {
    // if you're a directory
    if(entry->d_type == 8 && size > 1) {
      size_total += get_size(d, size - 1);
    }
    // add BOTH dir size and file size
    stat(entry->d_name, s);
    size_total += s->st_size;
  }
  free(s);
  return size_total;
}

// helper to do the alphabetical insertion
struct info ** alphabetical_insert(struct info ** listing, struct info * info, int dir_index, int mode, int length){
  int index;
  int second_index;
  struct info * placeholder; //holds the info
  struct info * second_placeholder;
  //printf("%s\n", placeholder -> name);
  // dir case
  if (mode == 0){
    for (index = 0; index < dir_index; index++){
      // take care of first and last case
      if (listing[index] == NULL){
        listing[index] = info;
        break;
      }
      // general case, and then increment everything else by 1
      if (strcmp(info -> name, listing[index] -> name) > 0 ){
        index = second_index + 1; //one swap has already been done
        placeholder = listing[index];
        listing[index] = info;
        //printf("Listing[%d]: %s\n", index, listing[index] -> name);
        // don't want stuff spilling into files
        while (second_index < dir_index - 1 && listing[second_index] != NULL){
          printf("Listing[%d]: %s\n", second_index, second_placeholder -> name);
          second_placeholder = placeholder;
          placeholder = listing[second_index];
          listing[second_index] = second_placeholder;
          second_index++;
        }
        break;
      }
    }
  }
  // file case
  else {
    for (index = dir_index; index < length; index++){
      // take care of first and last case
      if (listing[index] == NULL){
        listing[index] = info;
        break;
      }
      // general case, and then increment everything else by 1
      if (strcmp(info -> name, listing[index] -> name) > 0 ){
        index = second_index + 1; //one swap has already been done
        placeholder = listing[index];
        listing[index] = info;
        // don't want stuff spilling into files
        while (second_index < length - 1 && listing[second_index] != NULL){
          second_placeholder = placeholder;
          placeholder = listing[second_index];
          listing[second_index] = second_placeholder;
          second_index++;
        }
      }

    }
  }
  return listing;
}

// do ls -l
void ls(DIR *d){
  struct stat *s = malloc(sizeof(struct stat));
  struct dirent *entry;
  int length = 0;
  int file_count = 0;
  int dir_count = 0;

  // find za length
  while( (entry = readdir(d)) != NULL ) {

    // keep track of the directory count
    if (entry -> d_type == 8){
      dir_count++;
    }
    length++;
  }

  closedir(d);
  d = opendir(".");

  struct info ** listing = calloc(length, sizeof(listing));
  char entry_time[256];
  char entry_string[256]; // string containing time, perms, and name of file
  int len; //track string length to snip off the \n
  struct info *info;

  while( (entry = readdir(d)) != NULL ) {
    stat(entry->d_name, s);
    strcpy(entry_time, ctime(&(s->st_atime)));
    len = strlen(entry_time);
    entry_time[len-1] = 0; // strip newline

    // add all the info into one string
    // spaces needed?
    strcpy(entry_string, string_perms(s));
    strcat(entry_string, entry_time);
    strcat(entry_string, entry -> d_name);


    info = malloc(sizeof(info));
    info -> name = entry -> d_name;
    info -> entry_string = entry_string;

    // add in the new string alphabetically
    if(entry->d_type == 4){
      alphabetical_insert(listing, info, dir_count, 1, length);
    }
    else if (entry -> d_type == 8){
      alphabetical_insert(listing, info, dir_count, 0, length);
    }
  }

  // print out the ls
  int index;
  for (index = 0; index < length; index++){
    printf("%s\n", listing[index] -> entry_string);
  }

  free(s);
  free(listing);
  // need to free info?
}
