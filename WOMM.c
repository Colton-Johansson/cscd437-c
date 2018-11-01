//TEAM: Worked on my machine...
//Colton Johansson
//Joseph Carlson
//Brandtly Strobeck

#include<stdio.h>
#include<regex.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>

#define true (1==1)
#define false (!true)

int regex(char *regexStr, char *strToMatch); //Returns 0 on match
void flushStdin();
void getName50(char *s);
void getInt(int *i);
FILE* getInFile();

int main() {

    //char fName[51];
    //char lName[51];
    //int int1;
    //int int2;
    FILE *file;

    /*printf("Please enter first name (no more than 50 characters, A-Z, a-z, ', -): ");
    getName50(fName);
    printf("Please enter last name (no more than 50 characters, A-Z, a-z, ', -): ");
    getName50(lName);
    printf("Please enter an integer: ");
    getInt(&int1);
    printf("Please enter another integer: ");
    getInt(&int2);*/
    printf("Please enter input file name (input file must be in folder: input_files, which is in same directory as C executable. File name must be less than 255 characters.): ");
    file = getInFile();

    //printf("int1: %d", int1);
    //printf("\n%s %s\n", fName, lName);

	return 0;
}

int regex(char *regexStr, char *strToMatch) { //Returns 0 on match
    regex_t regex;
    regcomp(&regex, regexStr, REG_EXTENDED);
    return regexec(&regex, strToMatch, 0, NULL, 0);
}

void flushStdin() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void getName50(char *s) {

    char word[52];
    int notValid = true;


    do {
        start:
        memset(word, '\0', 52);
        fgets(word, sizeof(word), stdin);
        strtok(word, "\n");

        if (word[0] == '\n') {
            goto end;
        }

        int len = (int) strlen(word); //CAREFUL!! Since unsigned -> signed could be extremely negative.

        if (len > 50 || len < 1) {
            printf("Name can't be larger than 50 characters!");
            printf("\nPlease enter name: ");
            goto end;
        }

        if (regex("^[a-zA-Z'-]{1,50}$", word) == 0) {

            strncpy(s, word, 50);
            s[50] = '\0';
            notValid = false;

        } else {
            printf("Not a valid match!");
            printf("\nPlease enter name: ");
            goto start;
        }
        end:
        if (notValid) {
            flushStdin();
        }
    } while (notValid);
}

void getInt(int *i) { //TODO figure out how to not press enter after flush
    char line[12];
    int notValid = true;
    long j;

    do {
        memset(line, '\0', 12);
        fgets(line, sizeof(line), stdin);
        strtok(line, "\n");


        if (regex("^[-+]?[0-9]{1,10}$", line) == 0) {
            j = strtol(line, NULL, 10);
            if (j <= INT_MAX && j >= INT_MIN) {
                *i = (int) j;
                notValid = false;
            } else {
                printf("Integer is out of range of max or min int size!");
                printf("\nPlease enter a valid int: ");
            }
        } else {
            printf("Not a valid int!");
            printf("\nPlease enter a valid int: ");
        }
        if (notValid) {
            flushStdin();
        }
    } while (notValid);
}

FILE* getInFile() {

    /*char fileName[256];


    return fopen("../input_files/a.txt", "r");*/
}
