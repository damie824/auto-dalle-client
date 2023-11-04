#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <windows.h>
#include <unistd.h>
#include <scripts/downloadImage.h>
#include <scripts/sendRequest.h>
#include <scripts/parseJson.h>
#include <util/readAllFiles.h>
#include <util/logger.h>

//프롬프트 구조체 설정 - 이후 업데이트 시 기능 추가 대비
typedef struct prompt {
	char prompt[101];
} prompt;

//유저가 사용 중인 폴더 불러오기
void getCurrentDirectory(char *buffer, size_t size) {
	GetModuleFileName(NULL, buffer, size);
	char *lastSlash = strrchr(buffer, '\\');
	if(lastSlash != NULL) {
		*lastSlash = '\0';
	}
}

int main(void) {

	initializeLog(&logger);
	logger.log("Initialized logger.");
	char currentDirectory[MAX_PATH];
	getCurrentDirectory(currentDirectory, sizeof(currentDirectory));
	char directoryLog[200];
	snprintf(directoryLog, sizeof(directoryLog), "Running on directory : %s", currentDirectory);
	logger.log(directoryLog);
	char imgDirectory[200];
	snprintf(imgDirectory, sizeof(imgDirectory), "%s\\images", currentDirectory);
	char imgDirectoryTarget[200];
	snprintf(imgDirectoryTarget, sizeof(imgDirectoryTarget), "Targeted folder to download images : %s",
	         imgDirectoryTarget);

	logger.verbose("Starting Programs..");

	sleep(3);

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

				char *res;

				res = sendReq(userInput.prompt);

				imgres response;

				response = parseJSON(res);

				downloadimg(response, userInput.prompt);

				logger.log("Press enter to continue. (Image will save automatically)");
				while(getchar() != '\n');
				continue;
			case 2:
				printFilesInDirectory(imgDirectory);
				logger.log("Press enter to continue.");
				getchar();
				while(getchar() != '\n');
				continue;
			case 3:
				exit(0);
			default:
				getchar();
				continue;
		};
	}
}
