#ifndef READFILES_H
#define READFILES_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void printFilesInDirectory(const char *directory) {

	char readingDir[200];
	snprintf(readingDir, sizeof(readingDir), "Reading : %s", directory);
	logger.verbose(readingDir);

	DIR *dir;
	struct dirent *entry;
	struct stat info;
	
	dir = opendir(directory);
	if(dir == NULL) {
		logger.error("couldn't open folder");
		return;
	}

	while((entry = readdir(dir)) != NULL) {
		char filepath[256];
		snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);

		if(stat(filepath, &info) != -1) {
			if(S_ISREG(info.st_mode)) {
				char catchedFile[200];
				snprintf(catchedFile, sizeof(catchedFile), "Catched File : %s", entry->d_name);
				logger.verbose(catchedFile);
			}
		}
	}

	closedir(dir);
}


#endif
