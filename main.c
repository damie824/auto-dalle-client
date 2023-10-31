#include <stdio.h>
#include <string.h>
#include <scripts/sendRequest.h>
#include <curl/curl.h>

typedef struct result {
    char prompt[100];
    char image[200];
} result;

typedef struct prompt {
    char prompt[101];
} prompt;

int main(void) {
    system("cls");

    while(1) {
        int n;
        scanf("%d", &n);
        getchar(); // scanf가 남겨둔 개행 문자를 제거합니다.

        prompt userInput[n];

        for(int i=0; i<n; i++) {
            char buffer[500];
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0; // 입력의 마지막에 붙는 개행 문자를 제거합니다.
            strcpy(userInput[i].prompt, buffer);
        }

        if(strcspn(userInput[0].prompt, "") == 101) {
            return 0;
        }

        sendReq(userInput[0].prompt);

        printf("%s", userInput[0].prompt);

        break;
    }
}
