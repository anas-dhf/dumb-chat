#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

void verifyUser();
void createUser();
void logIn();
void haveAccount();

char userName[MAX_LINE_LENGTH], userPassword[MAX_LINE_LENGTH];
int exists;
FILE *fp;
char users[] = "user.txt";
char line[MAX_LINE_LENGTH];
char *tokenUser, *tokenPassword;

FILE *fpp;
char text[] = "text.txt";
char line[MAX_LINE_LENGTH];
char *tokenTexting;

void verifyUser() {
   exists = 0;
   fp = fopen(users, "r");
   if (fp == NULL) {
      printf("---ERR: Unable to Open File: %s---\n", users);
      return;
   }
   while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
      int len = strlen(line);
      if (line[len - 1] == '\n') {
         line[len - 1] = '\0';
      }
      
      tokenUser = strtok(line, ",");
      tokenPassword = strtok(NULL, ",");
      
      if (strcmp(tokenUser, userName) == 0 && strcmp(tokenPassword, userPassword) == 0) {
         printf("---User Found. Logging in.---\n");
         exists = 1;
         break;
      }
   }
   if (exists == 0) {
      printf("---User not found.---\n");
      createUser();
   }
   fclose(fp);
}

void createUser() {
   printf("---Welcome new user!---\n");
   printf("Name: ");
   scanf("%s", userName);
   printf("Password: ");
   scanf("%s", userPassword);
   printf("---Welcome %s, we hope you enjoy your stay!---\n", userName);
   fp = fopen(users, "a");
   fprintf(fp, "%s,%s\n", userName, userPassword);
   fclose(fp);
   printf("---For security reasons, please log in again!---\n");
   logIn();
}

void logIn() {
   printf("Name: ");
   scanf("%s", userName);
   printf("Password: ");
   scanf("%s", userPassword);
   verifyUser();   
}

void haveAccount() {
   printf("===Welcome to our Chatting Platform!===\n\n");
   printf("Do you have an account (1:Yes / 0:No): ");
   scanf("%d", &exists);
   if (exists == 1) {
      logIn();
   }
   else if (exists == 0) {
      createUser();
   }
}

void writing(){
	fpp = fopen(text, "a");
    char texting[MAX_LINE_LENGTH];
	while (1) {
        printf("%s: ", userName);
        fgets(texting, MAX_LINE_LENGTH, stdin);
        tokenTexting = texting;
        tokenTexting[strcspn(texting, "\n")] = '\0'; 
        if (strcmp(texting, "EXIT") == 0) {
			printf("---Goodbye!---\n");
            break;
        }
        if (strcmp(texting, "SWITCH") == 0) {
			printf("---Disconnected. Please LogIn again!---\n");
        	logIn();
        }
        fprintf(fpp, "%s: %s\n", userName, texting);
   	}
   	fclose(fpp);
}

int main() {
   haveAccount();
   writing();
   return 0;
}
