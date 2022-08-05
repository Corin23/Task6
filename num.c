#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 2048
#define FILE_IN "in.txt"
#define FILE_OUT "out.txt"
#define MAXNUMBERS 1000

void replacestr(char *target, const char *what, const char *with) {
  char *pch;

  assert(strlen(what) == strlen(with));

  while ((pch = strstr(target, what)) != NULL) {
    strncpy(pch, with, strlen(with));
    pch += strlen(with);
  }
}

int cmpfunc(const void *a, const void *b) {
  return (*(long long *)a - *(long long *)b);
}

void dataprocessing(FILE *in, FILE *out) {

  char *line = (char *)malloc(BUFFERSIZE * sizeof(char));
  long long *arr = (long long *)malloc(MAXNUMBERS * sizeof(long long) + 1);
  long long val;

  const char *rep = "123";
  const char *with = "321";

  int i = 0;

  in = fopen(FILE_IN, "r");
  out = fopen(FILE_OUT, "w");

  while (!feof(in)) {

    fgets(line, BUFFERSIZE, in);
    replacestr(line, rep, with);

    val = atoll(line);
    arr[i++] = val;
  }

  qsort(arr, MAXNUMBERS, sizeof(long long *), cmpfunc);
  for (int i = 0; i < MAXNUMBERS; i++)
    fprintf(out, "%lld\n", arr[i]);

  free(line);
  free(arr);

  fclose(in);
  fclose(out);
}

int main() {
  FILE *fin, *fout;
  fin = fopen(FILE_IN, "r");
  fout = fopen(FILE_OUT, "w");

  dataprocessing(fin, fout);

  fclose(fin);
  fclose(fout);
  return 0;
}