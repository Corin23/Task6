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

long long *processinput(const char *fin, int *lines) {
  FILE *in;
  long long val, filesize = maxlines;
  int c;

  long long *arr = (long long *)malloc(filesize * sizeof(long long));
  
  if (arr == NULL) {
    printf("Memory not allocated for arr!\n");
    exit(EXIT_FAILURE);
  }

  char *line = (char *)malloc(buffersize * sizeof(char));
  
  if (line == NULL) {
    printf("Memory not allocated for line!\n");
    exit(EXIT_FAILURE);
  }

  in = fopen(fin, "r");
  
  if (in == NULL) {
    printf("Couldn't open file in.txt!\n");
    exit(EXIT_FAILURE);
  }

  while ((c = fscanf(in, "%s", line)) != EOF) {
    replacestr(line, rep, with);

    val = atoll(line);
    arr[(*lines)++] = val;

    if (*lines > maxlines) {

      filesize += maxlines;
      arr = (long long *)realloc(arr, filesize * sizeof(long long));

      if (arr == NULL) {
        printf("%s", "Couldn\'t reallocate memory for arr! Exiting...\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  fclose(in);
  return arr;
  free(arr);
}

void genoutput(const char *fout, long long *array, const int *lines) {
  FILE *out;
  
  out = fopen(fout, "w");

  if (out == NULL) {
    printf("Couldn't open file out.txt!\n");
    exit(EXIT_FAILURE);
  }
 
  qsort(array, *lines, sizeof(long long *), cmpfunc);
  for (int i = 0; i < *lines; i++) {
    fprintf(out, "%lld\n", array[i]);
  }

  fclose(out);
}

int main() {
  int lines = 0;
  long long *Arr = processinput(file_in, &lines);
  genoutput(file_out, Arr, &lines);

  return 0;
}
