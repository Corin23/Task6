#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUFFERSIZE 2048
#define MAXNUMBERS 1000000

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

void dataprocessing(FILE *in, FILE *out) {
  
  long long maxlines = 256;
  
  long long *arr = (long long *)malloc(maxlines * sizeof(long long));
  char *line = (char *)malloc(BUFFERSIZE * sizeof(char));

  long long val;

  const char *rep = "123";
  const char *with = "321";

  int i = 0, lines = 0;

  in = fopen(FILE_IN, "r");
  out = fopen(FILE_OUT, "w");

  while (!feof(in)) {
    if (lines > maxlines) {
      maxlines *= 2;
      arr = (long long *)realloc(arr, maxlines * sizeof(long long));
    }
    fgets(line, BUFFERSIZE, in);
    replacestr(line, rep, with);
    lines++;

    val = atoll(line);
    arr[i++] = val;
  }

  qsort(arr, lines, sizeof(long long *), cmpfunc);
  for (int i = 0; i < lines; i++)
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