#ifndef READFILES_H
#define READFILES_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void printFilesInDirectory(const char* directory) {
    DIR* dir;
    struct dirent* entry;

    // 폴더 열기
    dir = opendir(directory);
    if (dir == NULL) {
        printf("폴더를 열 수 없습니다.");
        return;
    }

    // 폴더 내의 파일들 출력
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name == NULL) {
            printf("%s\n", entry->d_name);
        }
    }

    // 폴더 닫기
    closedir(dir);
}

#endif
