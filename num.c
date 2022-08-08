#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int buffersize = 2048;
const char *file_in = "in.txt";
const char *file_out = "out.txt";
const char *rep = "123";
const char *with = "321";
long long maxlines = 4096;

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
  long long val;

  long long *arr = (long long *)malloc(maxlines * sizeof(long long));
  char *line = (char *)malloc(buffersize * sizeof(char));

  if (arr == NULL || line == NULL) {
    printf("Memory couldn't be allocated! Exiting...\n");
    exit(2);
  }

  int i = 0, lines = 0;

  in = fopen(filei, "r");
  out = fopen(fileo, "w");

  assert(in != NULL && out != NULL);

  while (!feof(in)) {

    if (lines > maxlines) {
      maxlines *= 2;
      arr = (long long *)realloc(arr, maxlines * sizeof(long long));
      if (arr == NULL) {
        printf("Couldn't reallocate memory for arr! Exiting...\n");
        exit(3);
      }
    }

    fgets(line, buffersize, in);
    replacestr(line, rep, with);
    lines++;

    val = atoll(line);
    arr[i++] = val;
  }
  printf("%d", lines);

  qsort(arr, lines - 1, sizeof(long long *), cmpfunc);
  for (int i = 0; i < lines - 1; i++) {
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