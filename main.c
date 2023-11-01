#include <stdio.h>
#include <string.h>
#include <scripts/sendRequest.h>
#include <scripts/parseJson.h>

typedef struct prompt {
    char prompt[101];
} prompt;

int main(void) {
    system("cls");

    while(1) {
        prompt userInput;

        char buffer[500];
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(userInput.prompt, buffer);

        if(strcspn(userInput.prompt, "") == 101) {
            return 0;
        }

        char* res;

        res = sendReq(userInput.prompt);

        parseJSON(res);

        break;
    }
}
