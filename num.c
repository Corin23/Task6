#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int buffersize = 2048;
const char *file_in = "in.txt";
const char *file_out = "out.txt";
const char *rep = "123";
const char *with = "321";
const long long maxlines = 100000;

void replacestr(char *target, const char *what, const char *with) {
  char *pch;

  assert(strlen(what) == strlen(with));

  while ((pch = strstr(target, what)) != NULL) {
    strncpy(pch, with, strlen(with));
    pch += strlen(with);
  }
}

int cmpfunc(const void *a, const void *b) {
  long long lla = *(long long *)a;
  long long llb = *(long long *)b;
  return (lla > llb ? 1 : lla == llb ? 0 : -1);
}

void dataprocessing(const char *filei, const char *fileo) {

  FILE *in, *out;
  long long val, filesize = maxlines;

  long long *arr = (long long *)malloc(filesize * sizeof(long long));
  char *line = (char *)malloc(buffersize * sizeof(char));

  if (arr == NULL || line == NULL) {
    printf("%s", "Memory couldn\'t be allocated! Exiting...\n");
    exit(2);
  }

  int i = 0, lines = 0, c;

  in = fopen(filei, "r");
  out = fopen(fileo, "w");

  assert(in != NULL && out != NULL);

  while ((c = fscanf(in, "%s", line)) != EOF) {

    if (lines > maxlines) {
      filesize += maxlines;
      arr = (long long *)realloc(arr, maxlines * sizeof(long long));
      if (arr == NULL) {
        printf("%s", "Couldn\'t reallocate memory for arr! Exiting...\n");
        exit(3);
      }
    }

    replacestr(line, rep, with);
    lines++;

    val = atoll(line);
    arr[i++] = val;
  }

  qsort(arr, lines, sizeof(long long *), cmpfunc);
  for (int i = 0; i < lines; i++) {
    fprintf(out, "%lld\n", arr[i]);
  }

  free(line);
  free(arr);

  fclose(in);
  fclose(out);
}

int main() {
  dataprocessing(file_in, file_out);
  return 0;
}