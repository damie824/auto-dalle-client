#ifndef DOWNLOADIMG_H
#define DOWNLOADIMG_H

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <scripts/parseJson.h>
#include <direct.h>

static size_t writeData(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	return fwrite(ptr, size, nmemb, stream);
}

void createDirectory(const char *path) {
	char command[256];
#ifdef _WIN32
	snprintf(command, sizeof(command), "mkdir \"%s\"", path);
#else
	snprintf(command, sizeof(command), "mkdir -p \"%s\"", path);
#endif
	system(command);
}

void downloadimg(imgres img, char *prompt) {
	logger.verbose("Download Started");

	CURL *curl;
	FILE *fp;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if(!curl) {
		logger.error("Can't download image!");
		return;
	}

	createDirectory("images");

	char fileName[256];
	snprintf(fileName, sizeof(fileName), "images/%s.png", prompt);

	fp = fopen(fileName, "wb");
	if(fp == NULL) {
		logger.error("Couldn't generate file.");
	}

	curl_easy_setopt(curl, CURLOPT_URL, img.url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

	res = curl_easy_perform(curl);
	if(res != CURLE_OK) {
		logger.error("Failed to download images");
	}

	fclose(fp);
	curl_easy_cleanup(curl);
	curl_global_cleanup();
}

#endif
