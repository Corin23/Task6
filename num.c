#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFERSIZE 2048
#define MAXNUMBERS 100

char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

void sortfile(FILE* fp){
	char line[MAXNUMBERS][BUFFERSIZE];
	//long line[MAXNUMBERS];
	char tmp[BUFFERSIZE];
	int c,i,pass = 0;
	FILE* fpj;
	fpj = fopen("out.txt", "r");
    	fp = fopen("outsort.txt", "wr");
    
	
	if (fpj == NULL) {

      perror("Failed: ");
      exit(1);

    }

	while(fgets(line[i],BUFFERSIZE,fpj))
	{
		line[i][strlen(line[i]) - 1] = '\0';
		i++;
	}

	c = i;
	for(int i = 0; i < c; i++)
	{
    	for(int j = i+1; j < c; j++)
   		{

      	if(strlen(line[j]) < strlen(line[i])) 
		{
         strcpy(tmp, line[i]);
         strcpy(line[i], line[j]);
         strcpy(line[j], tmp);
      	}
   		}
			pass++;
	}

	for(int i=0; i <= c; i++)
	{
		fprintf(fp,"%s\n",line[i]);
	}

    	fclose(fp);
	fclose(fpj);
    
}

void wordexch(FILE* fin, FILE* fout){
char* result;
char buffer[BUFFERSIZE];
char oldword[] = "123";
char newword[] = "321";
bool reading = true;
int c;
fin = fopen("in.txt", "r");
fout = fopen("out.txt", "wr");

if (fin == NULL)
{
	printf("Couldn't open file in.txt!");
	exit(1);
}

while(!feof(fin)){
	fgets(buffer, BUFFERSIZE, fin);
	result = str_replace(buffer,oldword,newword);
	fprintf(fout,"%s", result);
}


fclose(fin);
fclose(fout);

}

int main()
{
FILE* fpi, *fpo, *fpos;
wordexch(fpi,fpo);
sortfile(fpos);
return 0;
}
