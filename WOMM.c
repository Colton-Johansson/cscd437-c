//TEAM: Worked on my machine...
//Colton Johansson
//Joseph Carlson
//Brandtly Strobeck

#include<stdio.h>
#include<regex.h>
#include <memory.h>

#define true (1==1)
#define false (!true)

void getName50(char *s);
int regex(char *regexStr, char *strToMatch); //Returns 0 on match
void flushStdin();

int main() {

    char fName[51];
    char lName[51];

    printf("Please enter first name (no more than 50 characters, A-Z, a-z, ', -): ");
    getName50(fName);
    printf("Please enter last name (no more than 50 characters, A-Z, a-z, ', -): ");
    getName50(lName);

    printf("\n%s %s\n", fName, lName);

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
    int match, notValid = true;


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

        match = regex("^[a-zA-Z'-]{1,50}$", word);

        if (match == 0) {

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


