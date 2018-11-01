//TEAM: Worked on my machine...
//Colton Johansson
//Joseph Carlson
//Brandtly Strobeck

#include<stdio.h>
#include<regex.h>
#include <memory.h>

#define true (1==1)
#define false (!true)

int getName50(char *s);

int main() {

    char fName[51];
    char lName[51];

    printf("Please enter first name (no more than 50 characters, A-Z, a-z, ', -): ");
    getName50(fName);
    printf("\nPlease enter last name (no more than 50 characters, A-Z, a-z, ', -): ");
    getName50(lName);

    printf("\n%s %s", fName, lName);

	return 0;
}

int getName50(char *s) {

    regex_t regex;
    regcomp(&regex, "^[a-zA-Z'-]{1,50}$", REG_EXTENDED);

    char word[51];
    int match, notValid = true;


    do {
        memset(word, '\0', 51);
        fgets(word, sizeof(word), stdin);
        strtok(word, "\n");

        if (strlen(word) > 50) {
            printf("Name can't be larger than 50 characters!");
            printf("\nPlease enter name: ");
        }

        match = regexec(&regex, word, 0, NULL, 0);

        if (match == 0) {

            strncpy(s, word, 50);
            s[50] = '\0';
            notValid = false;

        } else {
            printf("Not a valid match!");
            printf("\nPlease enter name: ");
        }

    } while (notValid);
    return 0;
}
