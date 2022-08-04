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

void quicksort(long long number[], int first, int last) {
  long i, j, pivot, temp;
  if (first < last) {
    pivot = first;
    i = first;
    j = last;

    while (i < j) {
      while (number[i] <= number[pivot] && i < last)
        i++;
      while (number[j] > number[pivot])
        j--;
      if (i < j) {
        temp = number[i];
        number[i] = number[j];
        number[j] = temp;
      }
    }
    temp = number[pivot];
    number[pivot] = number[j];
    number[j] = temp;
    quicksort(number, first, j - 1);
    quicksort(number, j + 1, last);
  }
}

void sortfile(FILE *fp) {
  long long Arr[MAXNUMBERS];
  int c, i, j, pass = 0;
  FILE *fpj;
  fpj = fopen("out.txt", "r");
  fp = fopen("outsort.txt", "w");

  if (fpj == NULL) {

    perror("Failed: ");
    exit(1);
  }
  printf("%s\n", "File oppened!");

  while (!feof(fpj) && (c < MAXNUMBERS)) {
    fscanf(fpj, "%lld\n", &Arr[c++]);
  }
  printf("Size of Arr element: %ld\n", sizeof(Arr[1]));
  quicksort(Arr, 0, c - 1);
  for (int i = 0; i < c - 1; i++) {
    printf("%lld\n", Arr[i]);
    fprintf(fp, "%lld\n", Arr[i]);
  }

  // c = i;
  fclose(fp);
  fclose(fpj);
}

void replace(FILE *fin, FILE *fout) {
  char *result;
  char buffer[BUFFERSIZE];
  char oldword[] = "123";
  char newword[] = "321";

  fin = fopen("in.txt", "r");
  fout = fopen("out.txt", "wr");

  if (fin == NULL) {
    printf("Couldn't open file in.txt!");
    exit(1);
  }
  while (!feof(fin)) {
    fgets(buffer, BUFFERSIZE, fin);
    replacestr(buffer, oldword, newword);
    fprintf(fout, "%s", buffer);
  }

  fclose(fin);
  fclose(fout);
}

int main() {
  double time_spent = 0.0;
  FILE *fpi, *fpo, *fpos;
  clock_t begin = clock();
  replace(fpi, fpo);
  sortfile(fpos);
  clock_t end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time elapsed %f", time_spent);
  return 0;
}