//TEAM: Worked on my machine...
//Colton Johansson
//Joseph Carlson
//Brandtly Strobeck

#include <stdio.h>
#include <regex.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include <openssl/sha.h>

#define true (1==1)
#define false (!true)

int regex(char *regexStr, char *strToMatch); //Returns 0 on match
void flushStdin();
void getName50(char *s);
void getInt(int *i);
FILE* getInFile();
int testPassword();
void getAndStorePass();
void sha256(char *string, char outputBuffer[65]);

int main() {

    //char fName[51];
    //char lName[51];
    //int int1;
    //int int2;
    //FILE *inFile;

    /*printf("Please enter first name (no more than 50 characters, A-Z, a-z, ', -): ");
    getName50(fName);
    printf("Please enter last name (no more than 50 characters, A-Z, a-z, ', -): ");
    getName50(lName);
    printf("Please enter an integer: ");
    getInt(&int1);
    printf("Please enter another integer: ");
    getInt(&int2);
    printf("Please enter input file name (input '.txt' file must be in folder 'input_files', which must be in same directory as the C executable).\n");
    printf("File name must be less than 255 characters, and may include a-z, A-Z, 0-9, and _\n");
    printf("Filename: ");
    inFile = getInFile();
    printf("\n");
    getAndStorePass();
    if (!testPassword())
    {
        printf("Passwords match!\n");
    }
    else
    {
        printf("Passwords don't match!\n");
    }*/

    //Test vars
    char fName[] = "Billy\0";
    char lName[] = "Bob\0";
    int int1 = -2147483648;
    int int2 = -2147483648;
    FILE *inFile = fopen("input_files/testInput.txt", "r");
    //

    long lint1 = (long) int1;
    long lint2 = (long) int2;
    long ladd = lint1 + lint2;
    long lmul = lint1 * lint2;

    FILE *outFile;
    outFile = fopen("out.txt", "w");

    fprintf(outFile, "Name: %s %s\n", fName, lName);
    fprintf(outFile, "Addition: %ld\n", ladd);
    fprintf(outFile, "Multiplication: %ld\n", lmul);
    fprintf(outFile, "Contents of input file:\n\n");

    int c;

    while ((c = getc(inFile)) != EOF) { //TODO may need to look into security of getc and putc
        putc(c, outFile);
    }

    fclose(inFile);
    fclose(outFile);

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

void getInt(int *i) {
    char line[13];
    int notValid = true;
    long j;

    do {
        start:
        memset(line, '\0', 13);
        fgets(line, sizeof(line), stdin);
        strtok(line, "\n");

        if (line[0] == '\n') {
            goto end;
        }

        int len = (int) strlen(line); //CAREFUL!! Since unsigned -> signed could be extremely negative.
        printf("Len: %d", len);

        if (len > 10 || len < 1) {

            if (len == 11 && (line[0] == '-' || line[0] == '+')) {
                goto escape;
            }
            if (len == 11 && !(line[0] == '-' || line[0] == '+')) {
                printf("Not a valid int!");
                printf("\nPlease enter a valid int: ");
                goto start;
            }
            printf("Not a valid int!");
            printf("\nPlease enter a valid int: ");
            goto end;
        }
        escape:

        if (regex("^[-+]?[0-9]{1,10}$", line) == 0) {
            j = strtol(line, NULL, 10);
            if (j <= INT_MAX && j >= INT_MIN) {
                *i = (int) j;
                notValid = false;
            } else {
                printf("Integer is out of range of max or min int size!");
                printf("\nPlease enter a valid int: ");
                goto start;
            }
        } else {
            printf("Not a valid int!");
            printf("\nPlease enter a valid int: ");
            goto start;
        }
        end:
        if (notValid) {
            flushStdin();
        }
    } while (notValid);
}

FILE* getInFile() { //TODO still needs testing

    char fileName[258];
    FILE *outFile = NULL;
    int notValid = true;

    do {
        memset(fileName, '\0', 258);
        fgets(fileName, sizeof(fileName), stdin);
        strtok(fileName, "\n");

        int len = (int) strlen(fileName); //CAREFUL!! Since unsigned -> signed could be extremely negative.

        if (len > 255 || len < 1) {
            printf("Filename can't be larger than 255 characters!");
            printf("\nPlease enter filename: ");
            goto end;
        }


        if (regex("^[a-zA-Z0-9_]{1,255}\\.txt$", fileName) == 0) {

            char path[277];
            sprintf(path, "input_files/%s", fileName);

            if (fopen(path, "r")) {
                //TODO I guess we could use strlcat for bufferoverflow protection but I don't think it's possible to get a string that big here
                outFile = fopen(path, "r"); //Can put a copy of input_files in cmake-build-debug if your using CLion
                notValid = false;
            } else {
                printf("File could not be found!");
                printf("\nPlease enter filename: ");
            }
        } else {
            printf("Not a valid '.txt' filename!");
            printf("\nPlease enter filename: ");
        }

        end:
        if (notValid) {
            flushStdin();
        }
    } while (notValid);


    return outFile;
}

void getAndStorePass()
{
    char pass[51];
    char* s = pass;

    char word[52];
    int notValid = true;
    printf("\nPlease enter a Password that is between 10 and 50 characters long, may include a-z, A-Z, 0-9, and _: ");

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
            printf("Password can't be larger than 50 characters!");
            printf("\nPlease enter a valid password: ");
            goto end;
        }

        if (regex("^[a-zA-Z0-9_]{10,50}$", word) == 0) {

            strncpy(s, word, 50);
            s[50] = '\0';
            notValid = false;

        } else {
            printf("Not a valid match!");
            printf("\nPlease enter a valid password: ");
            goto start;
        }
        end:
        if (notValid) {
            flushStdin();
        }
    } while (notValid);

    char buffer[65];
    sha256(pass, buffer);

    FILE *passFile= fopen("pass.txt", "w");
    unsigned long i;
    for (i = 0; i < strlen(buffer); i++){
        putc(buffer[i], passFile);
    }
    fclose(passFile);

}

int testPassword()
{
    char passToTest[65];
    char passOrig[65];
    char word[52];
    printf("\nEnter your password again: ");
    memset(word, '\0', 52);
    fgets(word, sizeof(word), stdin);
    strtok(word, "\n");


    if (word[0] == '\n') {
        return 1;
    }

    int len = (int) strlen(word); //CAREFUL!! Since unsigned -> signed could be extremely negative.

    if (len > 50 || len < 1) {
        return 1;
    }

    sha256(word, passToTest);


    int n=0;
    FILE *passFile= fopen("pass.txt", "r");
    int c;
    while ((c = getc(passFile)) != EOF) { //TODO may need to look into security of getc and putc
        passOrig[n++]=((char) c) ;
    }
    fclose(passFile);

    return strcmp(passToTest,passOrig);
}

void sha256(char *string, char outputBuffer[65])
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}
