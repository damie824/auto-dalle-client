#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>
#include <stdlib.h>

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

//로거 타입 선언
typedef struct Logger {
    int init;
    int (*log)(char*);
    int (*verbose)(char*);
    int (*warn)(char*);
    int (*error)(char*);
} Logger;

//함수 프로토타입 선언
char* addLeadingZero(int numb);
int initializeLog(Logger*);
char* writeLogInfo();
void saveLog(char* data);
int log_func(char* message);
int verbose_func(char* message);
int warn_func(char* message);
int error_func(char* message);

char* addLeadingZero(int numb) {
    char* result = (char*)malloc(3 * sizeof(char));

    if (numb < 10) {
        sprintf(result, "0%d", numb);
    } else {
        sprintf(result, "%d", numb);
    }

    return result;
}

int initializeLog(Logger *log) {

    if(log->init != 0) {
        return 0;
    }
    FILE *file;
    if((file = fopen("log.txt", "r"))) {
        fclose(file);
    }
    else {
        file = fopen("log.txt", "w");
        if(file == NULL) {
            perror("Can't create logger file in root dir.");
        }
        else {
            fclose(file);
        }
    }
    log->init = 1;
    return 0;
}

char* writeLogInfo() {
    time_t timeNow;
    struct tm* timeInfo;

    timeNow = time(NULL);
    timeInfo = localtime(&timeNow);

    char *hour;
    char *min;
    char *sec;

    hour = addLeadingZero(timeInfo->tm_hour);
    min = addLeadingZero(timeInfo->tm_min);
    sec = addLeadingZero(timeInfo->tm_sec);

    printf(
            ANSI_COLOR_GREEN "[Auto Dall-e] - %d/%d/%d, %s:%s:%s - " ANSI_COLOR_RESET,
            timeInfo->tm_year + 1900,
            timeInfo->tm_mon + 1,
            timeInfo->tm_mday,
            hour,
            min,
            sec
    );


    char * result = (char*)malloc(600 * sizeof(char));

    sprintf( result,"[Auto Dall-e] - %d/%d/%d, %s:%s:%s - ",
             timeInfo->tm_year + 1900,
             timeInfo->tm_mon + 1,
             timeInfo->tm_mday,
             hour,
             min,
             sec);

    return result;
}


void saveLog(char *data) {
    FILE* file;
    file = fopen("log.txt", "a");
    fprintf(file, "%s", data);
    fclose(file);
}

int log_func(char *message) {
    char* date = writeLogInfo();
    printf("%s\n", message);
    char* result = (char*)malloc(600 * sizeof(char));
    sprintf(result, "%s%s\n", date, message);
    saveLog(result);
}

int verbose_func(char *message) {
    char* date = writeLogInfo();
    printf(ANSI_COLOR_CYAN "%s\n" ANSI_COLOR_RESET, message);
    char* result = (char*)malloc(600 * sizeof(char));
    sprintf(result, "%s%s\n", date, message);
    saveLog(result);
}

int warn_func(char *message) {
    char* date = writeLogInfo();
    printf(ANSI_COLOR_YELLOW "%s\n" ANSI_COLOR_RESET, message);
    char* result = (char*)malloc(600 * sizeof(char));
    sprintf(result, "%s%s\n", date, message);
    saveLog(result);
}

int error_func(char *message) {
    char* date = writeLogInfo();
    printf(ANSI_COLOR_RED "%s\n" ANSI_COLOR_RESET, message);
    char* result = (char*)malloc(600 * sizeof(char));
    sprintf(result, "%s%s\n", date, message);
    saveLog(result);
}

Logger logger = {
        .init = 0,
        .log = log_func,
        .verbose = verbose_func,
        .warn = warn_func,
        .error = error_func,
};

#endif
