#include <stdio.h>
#include <string.h>
#include <scripts/sendRequest.h>
#include <scripts/parseJson.h>
#include <util/logger.h>

typedef struct prompt {
    char prompt[101];
} prompt;

int main(void) {

    initializeLog(&logger);
    logger.verbose("Program started.");

    while(1) {
        system("cls");
        printf(" ______     __  __     ______   ______        _____     ______     __         __         ______    \n"
               "/\\  __ \\   /\\ \\/\\ \\   /\\__  _\\ /\\  __ \\      /\\  __-.  /\\  __ \\   /\\ \\       /\\ \\       /\\  ___\\   \n"
               "\\ \\  __ \\  \\ \\ \\_\\ \\  \\/_/\\ \\/ \\ \\ \\/\\ \\     \\ \\ \\/\\ \\ \\ \\  __ \\  \\ \\ \\____  \\ \\ \\____  \\ \\  __\\   \n"
               " \\ \\_\\ \\_\\  \\ \\_____\\    \\ \\_\\  \\ \\_____\\     \\ \\____-  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\ \n"
               "  \\/_/\\/_/   \\/_____/     \\/_/   \\/_____/      \\/____/   \\/_/\\/_/   \\/_____/   \\/_____/   \\/_____/ \n"
               "                                                                                                   \n\n");

        printf("What are you going to do?\n\n"
               "1. Generate images\n"
               "2. Check saved images\n"
               "3. Exit\n"
               "\n"
               "Type your option here : ");

        int select;
        scanf("%d", &select);

        prompt userInput;

        system("cls");

        switch(select) {
            case 1:
                getchar();
                printf("Write your prompt : ");

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

                logger.log("Press enter to continue. (Image will save automatically");
                while( getchar() != '\n' );
                continue;
            case 2:
                logger.warn("This feature is under develop.");
                logger.log("Press enter to continue.");
                getchar();
                while( getchar() != '\n' );
                continue;

            case 3:
                exit(0);
        }
        getchar();
    }
}
